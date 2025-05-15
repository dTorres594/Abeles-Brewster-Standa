<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="20008000">
	<Property Name="CCSymbols" Type="Str">DEBUG,False;</Property>
	<Property Name="Instrument Driver" Type="Str">True</Property>
	<Property Name="NI.LV.All.SaveVersion" Type="Str">20.0</Property>
	<Property Name="NI.LV.All.SourceOnly" Type="Bool">true</Property>
	<Property Name="NI.Project.Description" Type="Str">This project is used by developers to edit API and example files for LabVIEW Plug and Play instrument drivers.</Property>
	<Item Name="My Computer" Type="My Computer">
		<Property Name="CCSymbols" Type="Str">OS,Win;CPU,x86;</Property>
		<Property Name="IOScan.Faults" Type="Str"></Property>
		<Property Name="IOScan.NetVarPeriod" Type="UInt">100</Property>
		<Property Name="IOScan.NetWatchdogEnabled" Type="Bool">false</Property>
		<Property Name="IOScan.Period" Type="UInt">10000</Property>
		<Property Name="IOScan.PowerupMode" Type="UInt">0</Property>
		<Property Name="IOScan.Priority" Type="UInt">9</Property>
		<Property Name="IOScan.ReportModeConflict" Type="Bool">true</Property>
		<Property Name="IOScan.StartEngineOnDeploy" Type="Bool">false</Property>
		<Property Name="NI.SortType" Type="Int">3</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="Support" Type="Folder">
			<Item Name="Set button status.vi" Type="VI" URL="../Support/Set button status.vi"/>
			<Item Name="CCW button.ctl" Type="VI" URL="../Public/Controls/CCW button.ctl"/>
			<Item Name="CW button.ctl" Type="VI" URL="../Public/Controls/CW button.ctl"/>
			<Item Name="Save config.vi" Type="VI" URL="../Support/Save config.vi"/>
			<Item Name="Load config.vi" Type="VI" URL="../Support/Load config.vi"/>
			<Item Name="Wait for home.vi" Type="VI" URL="../Support/Wait for home.vi"/>
			<Item Name="Wait for zero.vi" Type="VI" URL="../Support/Wait for zero.vi"/>
			<Item Name="CURVA TEÓRICA RPS.vi" Type="VI" URL="../RPS Tools/CURVA TEÓRICA RPS/CURVA TEÓRICA RPS.vi"/>
			<Item Name="crea vector theta cero r.vi" Type="VI" URL="../RPS Tools/CURVA TEÓRICA RPS/crea vector theta cero r.vi"/>
			<Item Name="crea vector de resolución.vi" Type="VI" URL="../RPS Tools/CURVA TEÓRICA RPS/crea vector de resolución.vi"/>
			<Item Name="forma arreglo de números complejos.vi" Type="VI" URL="../RPS Tools/CURVA TEÓRICA RPS/forma arreglo de números complejos.vi"/>
			<Item Name="Cálculo de nsr.vi" Type="VI" URL="../RPS Tools/CURVA TEÓRICA RPS/Cálculo de nsr.vi"/>
			<Item Name="cálculo npr y dr.vi" Type="VI" URL="../RPS Tools/CURVA TEÓRICA RPS/cálculo npr y dr.vi"/>
			<Item Name="cálculo Br Cr.vi" Type="VI" URL="../RPS Tools/CURVA TEÓRICA RPS/cálculo Br Cr.vi"/>
			<Item Name="divide matriz en submatrices.vi" Type="VI" URL="../RPS Tools/CURVA TEÓRICA RPS/divide matriz en submatrices.vi"/>
			<Item Name="ABRE ARCHIVO.vi" Type="VI" URL="../RPS Tools/Support/ABRE ARCHIVO.vi"/>
			<Item Name="calcula brewster.vi" Type="VI" URL="../RPS Tools/Support/calcula brewster.vi"/>
			<Item Name="Filtra curva experimental.vi" Type="VI" URL="../RPS Tools/Support/Filtra curva experimental.vi"/>
			<Item Name="brewster error.vi" Type="VI" URL="../RPS Tools/Support/brewster error.vi"/>
			<Item Name="Calculate Home direction.vi" Type="VI" URL="../Support/Calculate Home direction.vi"/>
			<Item Name="Has time elapsed.vi" Type="VI" URL="../Support/Has time elapsed.vi"/>
		</Item>
		<Item Name="Typedef" Type="Folder">
			<Item Name="Tab names -- Type Def.ctl" Type="VI" URL="../Support/Tab names -- Type Def.ctl"/>
			<Item Name="States -- typedef.ctl" Type="VI" URL="../States -- typedef.ctl"/>
			<Item Name="Control references -- typedef.ctl" Type="VI" URL="../Control references -- typedef.ctl"/>
			<Item Name="Curve fitting data.ctl" Type="VI" URL="../RPS Tools/Support/Curve fitting data.ctl"/>
			<Item Name="Config -- cluster.ctl" Type="VI" URL="../Support/Config -- cluster.ctl"/>
		</Item>
		<Item Name="Config" Type="Folder">
			<Item Name="config.ini" Type="Document" URL="../config.ini"/>
		</Item>
		<Item Name="Control de MaP.lvlib" Type="Library" URL="../Control de MaP.lvlib"/>
		<Item Name="Main.vi" Type="VI" URL="../Main.vi"/>
		<Item Name="RPS Tools.vi" Type="VI" URL="../RPS Tools/RPS Tools.vi"/>
		<Item Name="Dependencies" Type="Dependencies"/>
		<Item Name="Build Specifications" Type="Build">
			<Item Name="My Application" Type="EXE">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{B18FFE92-33D6-4786-933C-AA28CE515662}</Property>
				<Property Name="App_INI_GUID" Type="Str">{1BD71803-FA60-40F4-85F1-F93026084FB4}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="App_serverType" Type="Int">0</Property>
				<Property Name="Bld_autoIncrement" Type="Bool">true</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{37A9F6B7-1B9A-463D-B199-F14EA5E11A8B}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">My Application</Property>
				<Property Name="Bld_excludeInlineSubVIs" Type="Bool">true</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../builds/Abeles-Brewster/My Application</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToCommon</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{9BD152B0-912F-40F1-8D9F-70372C53442B}</Property>
				<Property Name="Bld_version.build" Type="Int">14</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">Abeles-Brewster.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../builds/Abeles-Brewster/My Application/Abeles-Brewster.exe</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../builds/Abeles-Brewster/My Application/data</Property>
				<Property Name="Destination[2].destName" Type="Str">Third-party</Property>
				<Property Name="Destination[2].path" Type="Path">../builds/Abeles-Brewster/My Application/Third-party</Property>
				<Property Name="DestinationCount" Type="Int">3</Property>
				<Property Name="Source[0].itemID" Type="Str">{73D7DD87-CC58-4F3F-BB39-109B6092AD15}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/Main.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="Source[2].Container.applyDestination" Type="Bool">true</Property>
				<Property Name="Source[2].Container.applyInclusion" Type="Bool">true</Property>
				<Property Name="Source[2].Container.depDestIndex" Type="Int">0</Property>
				<Property Name="Source[2].destinationIndex" Type="Int">2</Property>
				<Property Name="Source[2].itemID" Type="Ref">/My Computer/Control de MaP.lvlib/Third-party</Property>
				<Property Name="Source[2].sourceInclusion" Type="Str">Include</Property>
				<Property Name="Source[2].type" Type="Str">Container</Property>
				<Property Name="SourceCount" Type="Int">3</Property>
				<Property Name="TgtF_companyName" Type="Str">Centro de Investigaciones en Optica</Property>
				<Property Name="TgtF_fileDescription" Type="Str">My Application</Property>
				<Property Name="TgtF_internalName" Type="Str">Abeles-Brewster analysis</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">Copyright © 2023 Centro de Investigaciones en Optica</Property>
				<Property Name="TgtF_productName" Type="Str">Abeles-Brewster analysis</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{D22438BE-61E2-4FEE-B3F3-8A5AB56FDAF3}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">Abeles-Brewster.exe</Property>
				<Property Name="TgtF_versionIndependent" Type="Bool">true</Property>
			</Item>
			<Item Name="My Installer" Type="Installer">
				<Property Name="Destination[0].name" Type="Str">Stepper with arduino</Property>
				<Property Name="Destination[0].parent" Type="Str">{3912416A-D2E5-411B-AFEE-B63654D690C0}</Property>
				<Property Name="Destination[0].tag" Type="Str">{20820A06-C45C-4881-BB37-1933A680E834}</Property>
				<Property Name="Destination[0].type" Type="Str">userFolder</Property>
				<Property Name="Destination[1].name" Type="Str">Abeles-Brewster</Property>
				<Property Name="Destination[1].parent" Type="Str">{7C5E53B9-0CC8-49B4-8873-46C4C66A2706}</Property>
				<Property Name="Destination[1].tag" Type="Str">{E97534B1-372D-4C16-97E1-587878B1EE54}</Property>
				<Property Name="Destination[1].type" Type="Str">userFolder</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="DistPart[0].flavorID" Type="Str">_full_</Property>
				<Property Name="DistPart[0].productID" Type="Str">{F12C6F92-5B1C-4EAB-9364-96026CE1920D}</Property>
				<Property Name="DistPart[0].productName" Type="Str">NI-Serial Runtime 20.0</Property>
				<Property Name="DistPart[0].upgradeCode" Type="Str">{01D82F43-B48D-46FF-8601-FC4FAAE20F41}</Property>
				<Property Name="DistPart[1].flavorID" Type="Str">_deployment_</Property>
				<Property Name="DistPart[1].productID" Type="Str">{944CC86F-BDFB-4850-878C-370B9A7FF12C}</Property>
				<Property Name="DistPart[1].productName" Type="Str">NI-VISA Runtime 20.0</Property>
				<Property Name="DistPart[1].upgradeCode" Type="Str">{8627993A-3F66-483C-A562-0D3BA3F267B1}</Property>
				<Property Name="DistPart[2].flavorID" Type="Str"></Property>
				<Property Name="DistPart[2].productID" Type="Str"></Property>
				<Property Name="DistPart[2].productName" Type="Str">NI LabVIEW Run-Time Engine 2020</Property>
				<Property Name="DistPart[2].upgradeCode" Type="Str">{D84FC73F-D1E0-4C05-A30C-DB882CD1ABD8}</Property>
				<Property Name="DistPartCount" Type="Int">3</Property>
				<Property Name="INST_author" Type="Str">Centro de Investigaciones en Optica</Property>
				<Property Name="INST_autoIncrement" Type="Bool">true</Property>
				<Property Name="INST_buildLocation" Type="Path">../builds/Abeles-Brewster/My Installer</Property>
				<Property Name="INST_buildLocation.type" Type="Str">relativeToCommon</Property>
				<Property Name="INST_buildSpecName" Type="Str">My Installer</Property>
				<Property Name="INST_defaultDir" Type="Str">{7C5E53B9-0CC8-49B4-8873-46C4C66A2706}</Property>
				<Property Name="INST_installerName" Type="Str">install.exe</Property>
				<Property Name="INST_productName" Type="Str">Abeles-Brewster</Property>
				<Property Name="INST_productVersion" Type="Str">1.0.5</Property>
				<Property Name="InstSpecBitness" Type="Str">32-bit</Property>
				<Property Name="InstSpecVersion" Type="Str">20000000</Property>
				<Property Name="MSI_arpCompany" Type="Str">Centro de Investigaciones en Optica</Property>
				<Property Name="MSI_autoselectDrivers" Type="Bool">true</Property>
				<Property Name="MSI_distID" Type="Str">{7E5F80AB-433A-4C9F-B6DE-7762A252A425}</Property>
				<Property Name="MSI_hideNonRuntimes" Type="Bool">true</Property>
				<Property Name="MSI_osCheck" Type="Int">0</Property>
				<Property Name="MSI_upgradeCode" Type="Str">{DDF083AF-4134-4ECA-A8DE-9BC64A641FC7}</Property>
				<Property Name="RegDest[0].dirName" Type="Str">Software</Property>
				<Property Name="RegDest[0].dirTag" Type="Str">{DDFAFC8B-E728-4AC8-96DE-B920EBB97A86}</Property>
				<Property Name="RegDest[0].parentTag" Type="Str">2</Property>
				<Property Name="RegDestCount" Type="Int">1</Property>
				<Property Name="Source[0].dest" Type="Str">{7C5E53B9-0CC8-49B4-8873-46C4C66A2706}</Property>
				<Property Name="Source[0].File[0].dest" Type="Str">{7C5E53B9-0CC8-49B4-8873-46C4C66A2706}</Property>
				<Property Name="Source[0].File[0].name" Type="Str">Abeles-Brewster.exe</Property>
				<Property Name="Source[0].File[0].Shortcut[0].destIndex" Type="Int">2</Property>
				<Property Name="Source[0].File[0].Shortcut[0].name" Type="Str">Abeles-Brewster</Property>
				<Property Name="Source[0].File[0].Shortcut[0].subDir" Type="Str">Abeles-Brewster</Property>
				<Property Name="Source[0].File[0].ShortcutCount" Type="Int">1</Property>
				<Property Name="Source[0].File[0].tag" Type="Str">{D22438BE-61E2-4FEE-B3F3-8A5AB56FDAF3}</Property>
				<Property Name="Source[0].File[1].dest" Type="Str">{7C5E53B9-0CC8-49B4-8873-46C4C66A2706}</Property>
				<Property Name="Source[0].File[1].name" Type="Str">CDM21228_Setup.exe</Property>
				<Property Name="Source[0].File[1].tag" Type="Ref">/</Property>
				<Property Name="Source[0].FileCount" Type="Int">1</Property>
				<Property Name="Source[0].name" Type="Str">My Application</Property>
				<Property Name="Source[0].tag" Type="Ref">/My Computer/Build Specifications/My Application</Property>
				<Property Name="Source[0].type" Type="Str">EXE</Property>
				<Property Name="SourceCount" Type="Int">1</Property>
			</Item>
			<Item Name="RPS Tools" Type="EXE">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{F0F9D621-12F5-4AAB-B552-2239A8284843}</Property>
				<Property Name="App_INI_GUID" Type="Str">{70BAF9BA-8A20-4F82-802E-A21CF9B43C4B}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="App_serverType" Type="Int">0</Property>
				<Property Name="Bld_autoIncrement" Type="Bool">true</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{2A5D1DA1-4ABB-4C76-9FDC-D86196150E9A}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">RPS Tools</Property>
				<Property Name="Bld_excludeInlineSubVIs" Type="Bool">true</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../builds/NI_AB_PROJECTNAME/RPS Tools</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToCommon</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{A6E78CD8-1A66-4455-A378-5AA7015CD811}</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">RPS.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../builds/NI_AB_PROJECTNAME/RPS Tools/RPS.exe</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../builds/NI_AB_PROJECTNAME/RPS Tools/data</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Source[0].itemID" Type="Str">{C412C4D9-2AE1-40AD-9DF4-380701E46A29}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/RPS Tools.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">2</Property>
				<Property Name="TgtF_companyName" Type="Str">Centro de Investigaciones en Optica</Property>
				<Property Name="TgtF_fileDescription" Type="Str">RPS Tools</Property>
				<Property Name="TgtF_internalName" Type="Str">RPS Tools</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">Copyright © 2024 Centro de Investigaciones en Optica</Property>
				<Property Name="TgtF_productName" Type="Str">RPS Tools</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{3B884556-901C-416E-ACED-D008364847BA}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">RPS.exe</Property>
				<Property Name="TgtF_versionIndependent" Type="Bool">true</Property>
			</Item>
		</Item>
	</Item>
</Project>
