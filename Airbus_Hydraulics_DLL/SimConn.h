#ifndef SimConn_H
#define SimConn_H

#include <windows.h> 
#include <tchar.h> 
#include <stdio.h> 
#include <strsafe.h> 
#include <iostream>
#include <string.h>
#include <string>
#include "Gauge.h"
#include "SimConnect.h" 


//SimConnect data definitions
enum DATA_DEFINE_ID
{
	DEF_GEAR_POSITION
};

//SimConnect events
enum EVENT_ID
{
	EVENT_FRAME_TIMER,
	EVENT_GREEN_HYDRAULICS_PUMP_TOGGLE,
	EVENT_BLUE_HYDRAULICS_PUMP_TOGGLE,
	EVENT_YELLOW_HYDRAULICS_PUMP_TOGGLE,
	EVENT_GREEN_HYDRAULICS_FLUID_LEAK_TOGGLE,
	EVENT_BLUE_HYDRAULICS_FLUID_LEAK_TOGGLE,
	EVENT_YELLOW_HYDRAULICS_FLUID_LEAK_TOGGLE,
	EVENT_GREEN_HYDRAULICS_PUMP_FAIL_TOGGLE,
	EVENT_BLUE_HYDRAULICS_PUMP_FAIL_TOGGLE,
	EVENT_YELLOW_HYDRAULICS_PUMP_FAIL_TOGGLE,
	EVENT_AXIS_AILERONS_SET,
	EVENT_AILERON_SET,
	EVENT_AXIS_ELEVATOR_SET,
	EVENT_ELEVATOR_SET,
	EVENT_AXIS_RUDDER_SET,
	EVENT_RUDDER_SET,
	EVENT_BRAKING_ACTION,
	EVENT_ENABLE_BRAKES,
	EVENT_DISABLE_BRAKES,
	EVENT_GEAR_TOGGLE,
	EVENT_GEAR_SET,
	EVENT_DISABLE_FLIGHT_CONTROLS,
	EVENT_ENABLE_FLIGHT_CONTROLS,
	EVENT_GEAR_DOWN,
	EVENT_GEAR_UP,
	EVENT_TOGGLE_BRAKE_FAIL
};

//SimConnect notification groups
enum GROUP_ID
{
	GROUP_HIGHEST,
	GROUP_HIGHEST_MASKABLE,
	GROUP_STANDARD
};

//SimConnect data requests
enum DATA_REQUEST_ID
{
	REQUEST_LANDING_GEAR
};


//Shared external functions
void OpenSimConnect();
void CloseSimConnect();
void SendHydraulicsGaugeMode(EVENT_ID switch_event);


#endif