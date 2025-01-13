/*
* This header file contains all SimConnect header declarations for the Airbus Hydraulics Gauge
*/

#ifndef GAUGE_H
#define GAUGE_H

#include "pch.h"

#include <memory>
#include "Gauges.h"
#include "SimConn.h"
#include "GreenHydraulics.h"
#include "BlueHydraulics.h"
#include "YellowHydraulics.h"


//Shared gauge globals that SimConnect needs to access
extern bool green_hyd_pump_switch;
extern bool blue_hyd_pump_switch;
extern bool yellow_hyd_pump_switch;

extern bool green_hyd_fluid_leak_switch;
extern bool blue_hyd_fluid_leak_switch;
extern bool yellow_hyd_fluid_leak_switch;

extern bool green_hyd_pump_fail_switch;
extern bool blue_hyd_pump_fail_switch;
extern bool yellow_hyd_pump_fail_switch;

extern bool landing_gear_switch;
extern bool flight_controls_switch;

extern FLOAT64 green_hyd_pressure;
extern FLOAT64 green_hyd_fluid;
extern FLOAT64 blue_hyd_pressure;
extern FLOAT64 blue_hyd_fluid;
extern FLOAT64 yellow_hyd_pressure;
extern FLOAT64 yellow_hyd_fluid;

// State of the switches
extern bool green_hyd_pump_state;
extern bool blue_hyd_pump_state;
extern bool yellow_hyd_pump_state;

extern bool green_hyd_fluid_leak_state;
extern bool blue_hyd_fluid_leak_state;
extern bool yellow_hyd_fluid_leak_state;

extern bool green_hyd_pump_fail_state;
extern bool blue_hyd_pump_fail_state;
extern bool yellow_hyd_pump_fail_state;

extern bool landing_gear_state;
extern bool flight_controls_state;

extern std::unique_ptr<GreenHydraulics> greenHydraulicSystem;
extern std::unique_ptr<BlueHydraulics> blueHydraulicSystem;
extern std::unique_ptr<YellowHydraulics> yellowHydraulicSystem;

#endif