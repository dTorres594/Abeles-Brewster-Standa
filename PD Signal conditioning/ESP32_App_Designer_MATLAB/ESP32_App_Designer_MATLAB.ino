#include <AccelStepper.h>
#include <Adafruit_ADS1X15.h>
#include <Wire.h>

// PINES                    // Physical pin
#define I2C_SDA 21          // 36
#define I2C_SCL 22          // 33

#define X_STEP_PIN 25       // 9
#define X_DIR_PIN 33        // 8
#define X_ENABLE_PIN 32     // 7
#define X_HOME_PIN 13       // 15

#define Y_STEP_PIN 14       // 12
#define Y_DIR_PIN 27        // 11
#define Y_ENABLE_PIN 26     // 10
#define Y_HOME_PIN 12       // 13

// ***NOT USED ANYMORE. KEPT FOR COMPATIBILITY***
#define SENSOR_1_PIN 36     // 3
#define SENSOR_2_PIN 39     // 4
// ***NOT USED ANYMORE. KEPT FOR COMPATIBILITY***

#define LASER_PIN 4         // 26
#define PWM_FREQ 5000
#define PWM_RES 8

// OBJETOS
AccelStepper stepperX(1, X_STEP_PIN, X_DIR_PIN);
AccelStepper stepperY(1, Y_STEP_PIN, Y_DIR_PIN);
Adafruit_ADS1115 ads;

// ESPECIFICACIONES
const float GRADOS_POR_PASO = 0.01;
const int INTERVALO_REPORTE = 50;

// Variables
unsigned long ultimoReporte = 0;
bool motorX_Activo = false;
bool motorY_Activo = false;
int16_t adc0, adc1;
float volts0, volts1;

// Pre-declaración
void reportarPosicion();
void leerYReportarSensores();
void rutinaHomeSimultanea();
void barridoAngular(float gradosTotales, float resolucion);

void setup() {
  Serial.begin(115200);

  // Start ADC at the default I2C address
  Wire.begin(I2C_SDA, I2C_SCL);
  ads.setGain(GAIN_TWOTHIRDS);
  ads.begin(0x48);
  
  ledcAttach(LASER_PIN, PWM_FREQ, PWM_RES);
  ledcWrite(LASER_PIN, 0);

  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);

  pinMode(X_HOME_PIN, INPUT_PULLDOWN);
  pinMode(Y_HOME_PIN, INPUT_PULLDOWN);
  pinMode(X_ENABLE_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);
  pinMode(X_STEP_PIN, OUTPUT);  // Importante para HardSync
  pinMode(Y_STEP_PIN, OUTPUT);

  digitalWrite(X_ENABLE_PIN, HIGH);
  digitalWrite(Y_ENABLE_PIN, HIGH);

  // Configuración Manual (Rápida)
  stepperX.setMinPulseWidth(20);
  stepperX.setMaxSpeed(600);
  stepperX.setAcceleration(4000);
  stepperX.setCurrentPosition(0);
  stepperY.setMinPulseWidth(20);
  stepperY.setMaxSpeed(600);
  stepperY.setAcceleration(4000);
  stepperY.setCurrentPosition(0);

  Serial.println("ESP32 READY");
  reportarPosicion();
}

void loop() {
  // GESTIÓN MANUAL
  if (stepperX.distanceToGo() != 0) {
    stepperX.run();
    motorX_Activo = true;
  } else if (motorX_Activo) {
    motorX_Activo = false;
    digitalWrite(X_ENABLE_PIN, HIGH);
    reportarPosicion();
  }

  if (stepperY.distanceToGo() != 0) {
    stepperY.run();
    motorY_Activo = true;
  } else if (motorY_Activo) {
    motorY_Activo = false;
    digitalWrite(Y_ENABLE_PIN, HIGH);
    reportarPosicion();
  }

  if ((motorX_Activo || motorY_Activo) && (millis() - ultimoReporte > INTERVALO_REPORTE)) {
    reportarPosicion();
    ultimoReporte = millis();
  }

  // COMANDOS
  if (Serial.available() > 0) {
    char cmdChar = Serial.read();

    // B: BARRIDO ANGULAR
    // Recibe: B, Grados, Resolucion
    // Ej: B,60.0,1.0
    if (cmdChar == 'B') {
      float grados = Serial.parseFloat();
      float res = Serial.parseFloat();  // Leer la resolución deseada
      if (res < 0.01) res = 0.01;       // Protección mínima
      barridoAngular(grados, res);
    } else if (cmdChar == 'L') {        // Set laser output as PWM value
      int pwm = Serial.parseInt();
      if (pwm < 0) pwm = 0;
      if (pwm > 255) pwm = 255;
      ledcWrite(LASER_PIN, pwm);
    } else if (cmdChar == 'F') {
      rutinaHomeSimultanea();
    } else if (cmdChar == 'M') {
      float gr = Serial.parseFloat();
      long p = (long)(gr / GRADOS_POR_PASO);
      if (p != 0) {
        digitalWrite(X_ENABLE_PIN, LOW);
        delay(2);
        stepperX.move(p);
      }
    } else if (cmdChar == 'N') {
      float gr = Serial.parseFloat();
      long p = (long)(gr / GRADOS_POR_PASO);
      if (p != 0) {
        digitalWrite(Y_ENABLE_PIN, LOW);
        delay(2);
        stepperY.move(p);
      }
    } else if (cmdChar == 'S') {
      stepperX.stop();
      stepperY.stop();
      Serial.println("ALERTA:PARADA");
    } else if (cmdChar == 'H') {
      stepperX.setCurrentPosition(0);
      stepperY.setCurrentPosition(0);
      Serial.println("HOME SET");
      reportarPosicion();
    } else if (cmdChar == 'R') {
      leerYReportarSensores();
    } else if (cmdChar == '?') {
      reportarPosicion();
    }

    while (Serial.available() > 0) Serial.read();
  }
}

//  BARRIDO ANGULAR DE ALTA VELOCIDAD
void barridoAngular(float gradosTotales, float resolucion) {
  // 1. Configurar Velocidades de Crucero (Rápidas pero estables)
  stepperX.setMaxSpeed(300);
  stepperX.setAcceleration(2000);

  stepperY.setMaxSpeed(600);
  stepperY.setAcceleration(4000);

  // 2. Calcular Objetivo Final
  long pasosTotalesX = (long)(gradosTotales / GRADOS_POR_PASO);
  long pasosTotalesY = pasosTotalesX * 2;

  // Activar Drivers
  digitalWrite(X_ENABLE_PIN, LOW);
  digitalWrite(Y_ENABLE_PIN, LOW);
  delay(50);

  Serial.println("START_BARRIDO");

  long posBaseX = stepperX.currentPosition();
  long posBaseY = stepperY.currentPosition();

  long targetX = posBaseX + pasosTotalesX;
  long targetY = posBaseY + pasosTotalesY;

  // Configurar movimiento
  stepperX.moveTo(targetX);
  stepperY.moveTo(targetY);

  // Variable para controlar la frecuencia de envío de datos
  // No queremos saturar, enviamos cada cierto tiempo o pasos
  unsigned long lastMicros = 0;
  const long intervaloLectura = 2000;  // Leer cada 2ms (500Hz de muestreo)

  // BUCLE DE MOVIMIENTO CONTINUO
  while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0) {

    // 1. Mover Motores (Prioridad Alta)
    stepperX.run();
    stepperY.run();

    // 2. Checar Paro (Sin bloquear)
    if (Serial.available() > 0) {
      char cmd = Serial.read();  // Leemos y sacamos el carácter del buffer

      if (cmd == 'S') {  // Si es la 'S' de Stop...
        Serial.println("STOP_BARRIDO");
        stepperX.stop();
        stepperY.stop();

        // Bucle de frenado suave (Deceleración)
        while (stepperX.run() || stepperY.run())
          ;

        // Salimos de la función inmediatamente
        return;
      }
    }

    // 3. Tomar Datos "Al Vuelo"
    if (micros() - lastMicros >= intervaloLectura) {
      float anguloReal = stepperX.currentPosition() * GRADOS_POR_PASO;

      // Lectura rápida ADC (Sin delayMicroseconds para no frenar motor)
      /*int val1 = analogRead(SENSOR_1_PIN);
      int val2 = analogRead(SENSOR_2_PIN);

      float v1 = (val1 * 3.3) / 4095.0;
      float v2 = (val2 * 3.3) / 4095.0;*/  // OBSOLETE. CONSIDER REMOVING
      float v1, v2;

      adc0 = ads.readADC_SingleEnded(0);
      adc1 = ads.readADC_SingleEnded(1);
  
      v1 = ads.computeVolts(adc0);
      v2 = ads.computeVolts(adc1);
      
      // Enviar: AnguloReal, V1, V2
      Serial.print(anguloReal, 4);
      Serial.print(",");
      Serial.print(v1, 4);
      Serial.print(",");
      Serial.println(v2, 4);

      lastMicros = micros();
    }
  }

  Serial.println("END_BARRIDO");

  // Asegurar posición final exacta
  reportarPosicion();
  digitalWrite(X_ENABLE_PIN, HIGH);
  digitalWrite(Y_ENABLE_PIN, HIGH);

  // Restaurar velocidades manuales
  stepperX.setMaxSpeed(600);
  stepperX.setAcceleration(4000);
  stepperY.setMaxSpeed(600);
  stepperY.setAcceleration(4000);
}

// Función auxiliar para leer AMBOS sensores durante el barrido
void leerYEnviarPromedio() {
  float sum1 = 0;
  float sum2 = 0;

  // Tomamos 10 lecturas rápidas para promediar
  for (int k = 0; k < 10; k++) {
    adc0 = ads.readADC_SingleEnded(0);  // Type int16_t
    adc1 = ads.readADC_SingleEnded(1);
  
    volts0 = ads.computeVolts(adc0);    // Type float
    volts1 = ads.computeVolts(adc1);
    
    sum1 += volts0;
    sum2 += volts1;  // Lectura Sensor 2
    delayMicroseconds(500);
  }

  float v1 = sum1 / 10.0;
  float v2 = sum2 / 10.0;  // Cálculo voltaje Sensor 2

  // Enviamos formato CSV: "Voltaje1,Voltaje2"
  Serial.print(v1, 4);
  Serial.print(",");
  Serial.println(v2, 4);
}

// FUNCIONES AUXILIARES

// Función auxiliar para lectura puntual manual
void leerYReportarSensores() {
  float sum1 = 0;
  float sum2 = 0;

  for (int i = 0; i < 20; i++) {
    adc0 = ads.readADC_SingleEnded(0);
    adc1 = ads.readADC_SingleEnded(1);
  
    volts0 = ads.computeVolts(adc0);
    volts1 = ads.computeVolts(adc1);
    
    sum1 += volts0;
    sum2 += volts1;  // Lectura Sensor 2
    delayMicroseconds(50);
  }

  float v1 = sum1 / 20.0;
  float v2 = sum2 / 20.0;  // Cálculo voltaje Sensor 2

  // Formato compatible con MATLAB: "SENS:Voltaje1,Voltaje2"
  Serial.print("SENS:");
  Serial.print(v1, 3);
  Serial.print(",");
  Serial.println(v2, 3);
}

// Función auxiliar para reportar posición de motores a MATLAB
void reportarPosicion() {
  float ax = stepperX.currentPosition() * GRADOS_POR_PASO;
  float ay = stepperY.currentPosition() * GRADOS_POR_PASO;
  Serial.print("POS:");
  Serial.print(ax, 3);
  Serial.print(",");
  Serial.println(ay, 3);
  Serial.print("HOME:");
  Serial.print(digitalRead(X_HOME_PIN) == LOW);  // #Diego: Revisar lógica
  Serial.print(",");
  Serial.println(digitalRead(Y_HOME_PIN) == LOW);
}

// Función para ejecutar rutina de enviar a 0° ambos motores de manera simultánea
void rutinaHomeSimultanea() {
  Serial.println("STATUS:HOMING_START");
  digitalWrite(X_ENABLE_PIN, LOW);
  digitalWrite(Y_ENABLE_PIN, LOW);
  delay(100);

  if (digitalRead(X_HOME_PIN) == LOW || digitalRead(Y_HOME_PIN) == LOW) {
    if (digitalRead(X_HOME_PIN) == LOW) stepperX.move(4000);
    if (digitalRead(Y_HOME_PIN) == LOW) stepperY.move(4000);
    while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0) {
      stepperX.run();
      stepperY.run();
    }
  }
  // FASE 1
  stepperX.setCurrentPosition(0);
  stepperY.setCurrentPosition(0);
  stepperX.move(-36000);
  stepperY.move(-36000);
  stepperX.setMaxSpeed(600);
  stepperY.setMaxSpeed(600);
  bool xF = false;
  bool yF = false;
  int cX = 0;
  int cY = 0;
  while (!xF || !yF) {
    if (Serial.available()) {
      if (Serial.read() == 'S') return;
    }  // Paro simple
    if (!xF) {
      stepperX.run();
      if (digitalRead(X_HOME_PIN) == LOW) cX++;
      else cX = 0;
      if (cX > 200) {
        stepperX.stop();
        xF = true;
      }
    }
    if (!yF) {
      stepperY.run();
      if (digitalRead(Y_HOME_PIN) == LOW) cY++;
      else cY = 0;
      if (cY > 200) {
        stepperY.stop();
        yF = true;
      }
    }
  }
  while (stepperX.run() || stepperY.run())
    ;
  delay(500);

  // FASE 2
  stepperX.setCurrentPosition(0);
  stepperX.move(4000);
  stepperX.setMaxSpeed(600);
  while (stepperX.distanceToGo() != 0) {
    stepperX.run();
    if (digitalRead(X_HOME_PIN) == LOW) {
      stepperX.stop();
      break;
    }
  }
  stepperX.move(-5000);
  while (stepperX.distanceToGo() != 0) {
    stepperX.run();
    if (digitalRead(X_HOME_PIN) == LOW) {
      stepperX.stop();
      break;
    }
  }

  stepperY.setCurrentPosition(0);
  stepperY.move(4000);
  stepperY.setMaxSpeed(600);
  while (stepperY.distanceToGo() != 0) {
    stepperY.run();
    if (digitalRead(Y_HOME_PIN) == LOW) {
      stepperY.stop();
      break;
    }
  }
  stepperY.move(-5000);
  while (stepperY.distanceToGo() != 0) {
    stepperY.run();
    if (digitalRead(Y_HOME_PIN) == LOW) {
      stepperY.stop();
      break;
    }
  }

  stepperX.setCurrentPosition(0);
  stepperY.setCurrentPosition(0);
  Serial.println("HOME:1");
  Serial.println("STATUS:HOMING_OK");
  Serial.println("IDLE");
  reportarPosicion();
  digitalWrite(X_ENABLE_PIN, HIGH);
  digitalWrite(Y_ENABLE_PIN, HIGH);
}
