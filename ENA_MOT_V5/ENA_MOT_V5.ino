int uni[]={     //es el arreglo donde se guardaran los pines para la salidas digitales de los bipolares 
  35,36,37,38}; //pines de salida
int bip[]={     //es el arreglo donde se guardaran los pines para la salidas digitales de los unipolares
  24,25,26,27}; //pines de salida
  
int bi[]={      //aqui se guardan los datos recibidos de labview
  0,0,0,0,0,0,0,0}; //todas las variables se guardan en en 0
                //bi[0] = Sentido del bipolar, bi[1] = Sentido del unipolar,
                //bi[2] = pasos del bipolar bit mas sig,bi[3] = pasos del bipolar bit menos sig
                //bi[4] = pasos del unipolar bit mas sig, bi[5] = pasos del unipolar bit menos sig
                //bi[6] = velocidad, bi[7]= tipo de paso 
unsigned char bot; //variable para el paro de emergencia
int n=0,i,c=1,d=1,m=0,m2=0,m1=0;    // son loa contadores para los ciclos for de de los motores para los pasos
unsigned int pu1=0,pu2=0,pb1=0,pb2=0,ptu=0,ptb=0,np=0; // se guardan las variables para los numeros de pasos 

void setup()
{                     //Inicion del void setup.
  Serial.begin(9600); //Inicia el puerto.
  for(i=0;i<4;i++){   //Declara la salidas de los pines de los motores inicio del ciclo. 
                  pinMode(uni[i], OUTPUT);  //Salidas del bipolar.
                  pinMode(bip[i], OUTPUT);  //Salidas del unipolar.
                   }                           //Fin del cilo for de las salidas.
  void bu_1();        //Prende la salidas digitales para que se ponga en el paso 1 para el bipolar.  
  void bb_1();        //Prende la salidas digitales para que se ponga en el paso 1 para el unipolar.
  bu_0();             //Apaga las salidas para el motor bipolar.
  bb_0();             //apaga las salidas para el motor unipolar.  
  delay(100);         //Espera de 100 milisegundos.
  Serial.print("Comienzo");  //Dice que el motor se apago.
  delay(100);         //Espera de 100 milisegundos. 
}                     //Fin del void setup.

void loop()            
{                    //Inicio del void loop.
  m=0;               //El contador de bipolar se pone en ceros.
  m2=0;              //El contador de unipolar se pone en ceros
  float time_delay;
  
  if (Serial.available()) {  //Solo entra cuando hay una interrupcion en el puerto.
    for(i=0;i<8;i++){         //Se incia el contador para leer los datos del puerto serie.
      bi[i]=Serial.read();     //Se le el puerto serie y se almacenan cada dato en un cadena.
      delay(50);               //Se espera 50 milisegundos para estabilizar el puerto
    }                          //Fin del ciclo for para la lecctura del puerto   

    pb1=bi[2]<<8;             //Se le el byte más significativo y se convierte a numero para los pasos del bipolar.
    pb2=bi[3];                 //Se le el byte menos significartivo de los pasos bipolares.
    ptb=pb1+pb2;               //Se almacenan los pasos totales bipolar sumando los bytes.
       
    pu1=bi[4]<<8;             //Se le el byte más significativo y se convierte a numero para los pasos del unipolar.    
    pu2=bi[5];                 //Se le el byte menos significativo de los pasos del unipolar.
    ptu=pu1+pu2;               //Se almacenan los pasos totales unipolar sumando los bytes.
    int freq = bi[6];
            
    if(ptu <= ptb){np=ptb;} else{np=ptu;}// Se compara pasos totales unipolar menor o igual que pasos totales bipolar para establecer el numero de pasos totales
    time_delay = 1.0/(float)bi[6]*1000;
    /*Serial.print("Pasos totales bipolar: ");
    Serial.println(ptb);         // #DTA: print total unipolar steps to port
    Serial.print("Pasos totales unipolar: ");
    Serial.println(ptu);         // #DTA: print total unipolar steps to port
    Serial.print("Pasos totales: ");  // #DTA: Print various variables with debugging purposes
    Serial.println(np);
    Serial.print("Frecuencia: ");    
    Serial.print(bi[6]);
    Serial.print(" Hz");
    Serial.print("Retardo entre pasos :");
    Serial.println(time_delay, 3);

    Serial.print("Motor bipolar ");
    if (bi[0]){
      Serial.println("derecha");
    }
    else{
      Serial.println("izquierda");
    }   

    Serial.print("Motor unipolar ");
    if (bi[1]){
      Serial.println("derecha");
    }
    else{
      Serial.println("izquierda");
    }                             */                // End of debugging output
                                  
    for(n=0;n<np;n++){          //Inicio del ciclo for para los paso del motor                           
      if(bi[0] == 'S'){         //Si el primer byte es una S se sale del for.
        break;                  //Salir del for.
      }                         //Fin del if bi[0] == S.
        
      // Comienza rutina de movimiento de motor bipolar      
      if (m < ptb){            //Si El numero de paso en el que va es menor al numero de pasos del bipolar que se requiere, se entra. 
        //Serial.print("Paso bipolar: ");
        //Serial.println(m);
        if (bi[0] == 0){        //Byte para saber en que sentido girara
          c++;                  //Contador para saber en que bobina se encuentra.
          if(c == 5){           //Se entra cuando la bobina dice que se active la 5.
            c=1;                //Como no hay bobina 5 se regresa a a la 1.
          }                     //Fin de el if c == 5.
          /*Serial.print("Bipolar izquierda. c = ");
          Serial.println(c);          */
        }                       //Fin del if b[0] == 0. 
        
        if (bi[0] == 1){       //Bite para saber en que sentido girara
          c--;               //Contador para saber en que bobina se encuentra.
          if(c == 0){          //Se entra cuando la bobina dice que se active la 0.
            c=4;               //Como no hay bobina 0 se regresa a a la 4.
          }                    //Fin de el if c == 0.  
          /*Serial.print("Bipolar derecha. c = ");
          Serial.println(c);        */
        }                      //Fin del if b[0] == 1. 
        co_bb();              //Se manda a llamar para activar la bobinas. 
        m++;                 //Contador para saber en que paso se encuentra del motor bipolar. 
      }                        //Fin del if m <= ptu. 

      // Comienza rutina de movimiento de motor unipolar      
      if (m2 < ptu){             //Si El numero de paso en el que va es menor al numero de pasos del unipolar que se requiere se entra. 
        //Serial.print("Paso unipolar: ");
        //Serial.println(m2);
        if (bi[1] == 0){        //Bite para saber en que sentido girara
          d++;                //Contador para saber en que bobina se encuentra.
          if(d == 5){           //Se entra cuando la bobina dice que se active la 5.
            d=1;                //Como no hay bobina 5 se regresa a a la 1.
          }                     //Fin de el if d == 5. 
          /*Serial.print("Unipolar izquierda. d = ");
          Serial.println(d);         */
        }                       //Fin del if b[1] == 0.
        if (bi[1] == 1){        //Bite para saber en que sentido girara
          d--;                //Contador para saber en que bobina se encuentra.
          if(d == 0){           //Se entra cuando la bobina dice que se active la 0.
            d=4;                //Como no hay bobina 0 se regresa a a la 4.
          }                     //Fin de el if d == 0.  
          /*Serial.print("Unipolar derecha. d = ");
          Serial.println(d);      */
        }                       //Fin del if b[1] == 1.
        co_bu();              //Se manda a llamar para activar la bobinas.
        m2++;                //Contador para saber en que paso se encuentra del motor unipolar.
        
      }                         //Fin del if m2 <= ptb.

      delay((int)time_delay);   //Tiempo de espera de cada paso del bit de velocidad.
      bot=Serial.read();        //Se lee el puerto si le llega el caracter de paro.
        
      if (bot == 'S'){          //Entra si le llega el caracter S para parar los motores.
        break;                  //Se sale del ciclo for.
      }                         //Fin del if bot == p.
        
      if ( m2 >= ptu &&  m >= ptb ){       //Entra si ya los motores no se pueden mover que hallan llegadoa  home.
        /*Serial.print("Pasos unipolar = ");
        Serial.println(m2);
        Serial.print("Pasos bipolar = ");
        Serial.println(m);*/
        Serial.println("Movimiento finalizado");
        break; 
      }                          //Se sale del ciclo for.
    }                                    //Fin del ciclo for del numero de pasos.

    bu_0();                              //Se mandan apagar las bobinas del bipolar.
    bb_0();                              //Se mandan apagar las bobinas del unipolar.  
    m=0;                                 //El contador se iguala a cero para volver a empezar.
    m2=0;                                //El contador se iguala a cero para volver a empezar.
    Serial.print("fin");                 //Se manda el caracter para apagar el indicador de que los motores ya no se moveran.
    delay(10);                           //Tiempo de espera para estabilizar el puerto.50 original
  }                                      //Fin del if de la interrupcion del puerto serial.
}                                        //Fin del vood loop


void co_bu(){          //Inicio de void para hacer las comparaciones en que bobinas se encuentra.
  //Serial.print("Llamadas unipolar: ");
  //Serial.println(m2);
  if (bi[7] == 0){     //Saber si es paso con este bit.
    if ( c == 1 ){     //Si contador c es igual a 1 entra.
      bu_1();          //Manda a llamar para prender el paso 1.
    }                  //Fin del if c == 1.
    if ( c == 2 ){     //Si contador c es igual a 2 entra.
      bu_2();          //Manda a llamar para prender el paso 2.
    }                  //Fin del if c == 2.
    if ( c == 3 ){     //Si contador c es igual a 3 entra.
      bu_3();          //Manda a llamar para prender el paso 3.
    }                  //Fin del if c == 3. 
    if ( c == 4 ){     //Si contador c es igual a 4 entra.
      bu_4();          //Manda a llamar para prender el paso 4.
    }                  //Fin del if c == 4.
  }                    //Fin del if bi[9] == 0. 
  if (bi[7] == 1){     //saber si es medio paso con este bit.
    if ( c == 1 ){     //Si contador c es igual a 1 entra.
      bu_11();         //Manda a llamar para prender el medio paso 1.
    }                  //Fin del if c == 1.
    if ( c == 2 ){     //Si contador c es igual a 2 entra.
      bu_22();         //Manda a llamar para prender el medio paso 2
    }                  //Fin del if c == 2.
    if ( c == 3 ){     //Si contador c es igual a 3 entra.
      bu_33();         //Manda a llamar para prender el medio paso 3.
    }                  //Fin del if c == 3.
    if ( c == 4 ){     //Si contador c es igual a 4 entra.
      bu_44();         //Manda a llamar para prender el medio paso 4.
    }                  //Fin del if c == 4.
  }                    //Fin del if bi[9] == 1.     
}                      //Fin del void co_bu

void co_bb(){          //Inicio de void para hacer las comparaciones en que bobinas se encuentra.
  //Serial.print("Llamadas bipolar: ");
  //Serial.println(m);
  if (bi[7] == 0){     //Saber si es paso con este bit.
    if ( d == 1 ){     //Si contador d es igual a 1 entra.
      bb_1();          //Manda a llamar para prender el paso 1.
    }                  //Fin del if d == 1.
    if ( d == 2 ){     //Si contador d es igual a 2 entra.
      bb_2();          //Manda a llamar para prender el paso 2.
    }                  //Fin del if d == 2.
    if ( d == 3 ){     //Si contador d es igual a 3 entra.
      bb_3();          //Manda a llamar para prender el paso 3.
     }                 //Fin del if d == 3.
    if ( d == 4 ){     //Si contador d es igual a 4 entra. 
      bb_4();          //Manda a llamar para prender el paso 4.
    }                  //Fin del if d == 4.  
  } 
  if (bi[7] == 1){     //Saber si es medio paso con este bit.
    if ( d == 1 ){     //Si contador d es igual a 1 entra.
      bb_11();         //Manda a llamar para prender el medio paso 1.
    }                  //Fin del if d == 1.
    if ( d == 2 ){     //Si contador d es igual a 2 entra.
      bb_22();         //Manda a llamar para prender el medio paso 1.
    }                  //Fin del if d == 2.
    if ( d == 3 ){     //Si contador d es igual a 3 entra.
      bb_33();         //Manda a llamar para prender el medio paso 1. 
    }                  //Fin del if d == 3.  
    if ( d == 4 ){     //Si contador d es igual a 4 entra.
      bb_44();         //Manda a llamar para prender el medio paso 1.
    }                  //Fin del if d == 4.
  }                    //Fin del if bi[9] == 1.   
}                      //Fin del void co_bb.
void bu_0() {                 //Entra si se llamo para saber que salidas digitales prender o apagar apagar bobinas.  
  digitalWrite(uni[0],LOW);   //Se manda apagar la bobinas.
  digitalWrite(uni[1],LOW);   //Se manda apagar la bobinas.
  digitalWrite(uni[2],LOW);   //Se manda apagar la bobinas.
  digitalWrite(uni[3],LOW);   //Se manda apagar la bobinas.
}                             //fin del void.
void bu_1() {                 //Entra si se llamo para saber que salidas digitales prender o apagar medio paso.
  digitalWrite(uni[0],HIGH);  //Se manda prender la bobinas.
  digitalWrite(uni[1],LOW);   //Se manda apagar la bobinas.
  digitalWrite(uni[2],HIGH);  //Se manda prender la bobinas.
  digitalWrite(uni[3],LOW);   //Se manda apagar la bobinas.
}                             //fin del void. 
void bu_2() {                 //Entra si se llamo para saber que salidas digitales prender o apagar medio paso.
  digitalWrite(uni[0],LOW);   //Se manda apagar la bobinas.
  digitalWrite(uni[1],HIGH);  //Se manda prender la bobinas.
  digitalWrite(uni[2],HIGH);  //Se manda prender la bobinas.
  digitalWrite(uni[3],LOW);   //Se manda apagar la bobinas.
}                             //fin del void. 
void bu_3() {                 //Entra si se llamo para saber que salidas digitales prender o apagar medio paso.
  digitalWrite(uni[0],LOW);   //Se manda apagar la bobinas.
  digitalWrite(uni[1],HIGH);  //Se manda prender la bobinas.
  digitalWrite(uni[2],LOW);   //Se manda apagar la bobinas.
  digitalWrite(uni[3],HIGH);  //Se manda prender la bobinas.
}                             //fin del void.
void bu_4() {                 //Entra si se llamo para saber que salidas digitales prender o apagar medio paso.
  digitalWrite(uni[0],HIGH);  //Se manda prender la bobinas.
  digitalWrite(uni[1],LOW);   //Se manda apagar la bobinas.
  digitalWrite(uni[2],LOW);   //Se manda apagar la bobinas. 
  digitalWrite(uni[3],HIGH);  //Se manda prender la bobinas.
}                             //fin del void.
void bu_11() {                //Entra si se llamo para saber que salidas digitales prender o apagar paso completo.
  digitalWrite(uni[0],HIGH);  //Se manda prender la bobinas. 
  digitalWrite(uni[1],LOW);   //Se manda apagar la bobinas.
  digitalWrite(uni[2],LOW);   //Se manda apagar la bobinas.
  digitalWrite(uni[3],LOW);   //Se manda apagar la bobinas .
}                             //fin del void.
void bu_22() {                //Entra si se llamo para saber que salidas digitales prender o apagar paso completo.
  digitalWrite(uni[0],LOW);   //Se manda apagar la bobinas.
  digitalWrite(uni[1],LOW);   //Se manda apagar la bobinas.
  digitalWrite(uni[2],HIGH);  //Se manda prender la bobinas.
  digitalWrite(uni[3],LOW);   //Se manda apagar la bobinas.
}                             //fin del void.
void bu_33() {                //Entra si se llamo para saber que salidas digitales prender o apagar paso completo.
  digitalWrite(uni[0],LOW);   //Se manda apagar la bobinas.
  digitalWrite(uni[1],HIGH);  //Se manda prender la bobinas.
  digitalWrite(uni[2],LOW);   //Se manda apagar la bobinas.
  digitalWrite(uni[3],LOW);   //Se manda apagar la bobinas.
}                             //fin del void.
void bu_44() {                //Entra si se llamo para saber que salidas digitales prender o apagar paso completo.
  digitalWrite(uni[0],LOW);   //Se manda apagar la bobinas.
  digitalWrite(uni[1],LOW);   //Se manda apagar la bobinas.
  digitalWrite(uni[2],LOW);   //Se manda apagar la bobinas.
  digitalWrite(uni[3],HIGH);  //Se manda prender la bobinas.
}                             //fin del void. 
void bb_0() {                 //Entra si se llamo para saber que salidas digitales prender o apagar apagar bobinas.
  digitalWrite(bip[0],LOW);   //Se manda apagar la bobinas.
  digitalWrite(bip[1],LOW);   //Se manda apagar la bobinas.
  digitalWrite(bip[2],LOW);   //Se manda apagar la bobinas.
  digitalWrite(bip[3],LOW);   //Se manda apagar la bobinas.
}                             //fin del void.
void bb_1() {                 //Entra si se llamo para saber que salidas digitales prender o apagar medio paso.
  digitalWrite(bip[0],HIGH);  //Se manda prender la bobinas.
  digitalWrite(bip[1],LOW);   //Se manda apagar la bobinas.
  digitalWrite(bip[2],LOW);   //Se manda apagar la bobinas.
  digitalWrite(bip[3],LOW);   //Se manda apagar la bobinas.
}                             //fin del void.
void bb_2() {                 //Entra si se llamo para saber que salidas digitales prender o apagar medio paso.
  digitalWrite(bip[0],LOW);   //Se manda apagar la bobinas.
  digitalWrite(bip[1],LOW);   //Se manda apagar la bobinas.
  digitalWrite(bip[2],HIGH);  //Se manda prender la bobinas.
  digitalWrite(bip[3],LOW);   //Se manda apagar la bobinas.
}                             //fin del void. 
void bb_3() {                 //Entra si se llamo para saber que salidas digitales prender o apagar medio paso.
  digitalWrite(bip[0],LOW);   //Se manda apagar la bobinas.
  digitalWrite(bip[1],HIGH);  //Se manda prender la bobinas.
  digitalWrite(bip[2],LOW);   //Se manda apagar la bobinas.
  digitalWrite(bip[3],LOW);   //Se manda apagar la bobinas .
}                             //fin del void.
void bb_4() {                 //Entra si se llamo para saber que salidas digitales prender o apagar medio paso.
  digitalWrite(bip[0],LOW);   //Se manda apagar la bobinas.
  digitalWrite(bip[1],LOW);   //Se manda apagar la bobinas.
  digitalWrite(bip[2],LOW);   //Se manda apagar la bobinas.
  digitalWrite(bip[3],HIGH);  //Se manda prender la bobinas.
}                             //fin del void.   
void bb_11() {                //Entra si se llamo para saber que salidas digitales prender o apagar paso completo. 
  digitalWrite(bip[0],HIGH);  //Se manda prender la bobinas.
  digitalWrite(bip[1],LOW);   //Se manda apagar la bobinas.
  digitalWrite(bip[2],HIGH);  //Se manda prender la bobinas.
  digitalWrite(bip[3],LOW);   //Se manda apagar la bobinas.
}                             //fin del void. 
void bb_22() {                //Entra si se llamo para saber que salidas digitales prender o apagar paso completo.
  digitalWrite(bip[0],LOW);   //Se manda apagar la bobinas.
  digitalWrite(bip[1],HIGH);  //Se manda prender la bobinas.
  digitalWrite(bip[2],HIGH);  //Se manda prender la bobinas.
  digitalWrite(bip[3],LOW);   //Se manda apagar la bobinas.
}                             //fin del void.
void bb_33() {                //Entra si se llamo para saber que salidas digitales prender o apagar paso completo.
  digitalWrite(bip[0],LOW);   //Se manda apagar la bobinas.
  digitalWrite(bip[1],HIGH);  //Se manda prender la bobinas.
  digitalWrite(bip[2],LOW);   //Se manda apagar la bobinas.
  digitalWrite(bip[3],HIGH);  //Se manda prender la bobinas.
}                             //fin del void.
void bb_44() {                //Entra si se llamo para saber que salidas digitales prender o apagar paso completo. 
  digitalWrite(bip[0],HIGH);  //Se manda prender la bobinas.
  digitalWrite(bip[1],LOW);   //Se manda apagar la bobinas.
  digitalWrite(bip[2],LOW);   //Se manda apagar la bobinas.
  digitalWrite(bip[3],HIGH);  //Se manda prender la bobinas.
}                             //fin del void.
