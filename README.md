# A simple Prepar3D v5 XML/C++ A320 Hydraulic System Gauge that uses SimConnect API 


## Features
- Green, Blue, Yellow HYD system
- A pressure regulator
- Pump failure simulation
- Fluid leak simulation
- Affected systems such as brakes, landing gear retraction/extension and flight control engagement are modeled based on SimConnect Events


## Installation
1. Download the latest release from [Releases](https://github.com/cptalpdeniz/inibuilds-task/releases)
2. Put the iniBuilds-Task-HYD to Prepar3D v5 Add-Ons folder in the documents
3. Add the following lines to the aircraft you want to add (adds the panel) and change the XX values based on the order

		WindowXX=Airbus Hydraulics


		[Window03]
		visible=1
		size_mm=400,100
		window_size=.45
		ident=AirbusHydraulics
		gauge00=Airbus-Hydraulics!Airbus-Hydraulics,0,0,400,100


## Credits
Coded by Alp Deniz Senyurt, for any issues, you can use the issues tab.