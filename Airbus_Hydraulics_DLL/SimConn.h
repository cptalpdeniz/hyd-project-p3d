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
	DEF_GEAR_POSITION,
	DEF_BRAKE_ACTION,
	DEF_RUDDER_POSITION,
	DEF_ELEVATOR_POSITION,
	DEF_AILERON_POSITION
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
	EVENT_AXIS_ELEVATOR_SET,
	EVENT_AXIS_RUDDER_SET,
	EVENT_BRAKING_ACTION,
	EVENT_AXIS_LEFT_BRAKE_SET,
	EVENT_AXIS_RIGHT_BRAKE_SET,
	EVENT_GEAR_TOGGLE,
	EVENT_GEAR_SET,
	EVENT_DISABLE_FLIGHT_CONTROLS,
	EVENT_ENABLE_FLIGHT_CONTROLS,
};

//SimConnect notification groups
enum GROUP_ID
{
	GROUP_HIGHEST
};

//SimConnect data requests
enum DATA_REQUEST_ID
{
	REQUEST_LANDING_GEAR,
	REQUEST_RUDDER_POSITION,
	REQUEST_ELEVATOR_POSITION,
	REQUEST_AILERON_POSITION
};


//Shared external functions
void OpenSimConnect();
void CloseSimConnect();
void SendHydraulicsGaugeMode(EVENT_ID switch_event);


#endif