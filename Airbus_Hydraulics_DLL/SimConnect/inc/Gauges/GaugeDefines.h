// Copyright (c) 2010-2019 Lockheed Martin Corporation. All rights reserved.
// Use of this file is bound by the PREPAR3D® SOFTWARE DEVELOPER KIT END USER LICENSE AGREEMENT

// gauges.h

#ifndef _GAUGES_DEFINES_H_
#define _GAUGES_DEFINES_H_


#pragma pack(push, 4)


//  Token list
//

typedef enum    GAUGE_TOKEN
{
    MODULE_VAR_NONE = 0,
    TICK18,                     //  inc'd at 18hz. used for general purpose timing
    GROUND_ALTITUDE,            //  ground level altitude (1/256 meter/unit)
    CLOCK_HOUR,                 //  local clock time, hours {0..23}
    CLOCK_MINUTE,               //  local clock time, minutes {0..59}
    CLOCK_SECOND,               //  local clock time, seconds {0..59}
    ZULU_HOUR,                  //  delta time from GMT
    ZULU_MINUTE,                //  delta time from GMT
    ZULU_DAY,                   //  GMT day of year (1 - 365/366)
    ZULU_YEAR,                  //  GMT year
    PANEL_LIGHTS,               //  TRUE=panel lighting on
    STROBE_LIGHTS,              //  TRUE=strobe lights on
    STROBE_FLASH,               //  TRUE=strobe flash on model & screen
    PITOT_HEAT,                 //  TRUE=pitot heat on
    LANDING_LIGHTS,             //  TRUE=landing lights on
    SMOKE_ENABLE,               //  TRUE=smoke system active
    ADF_FREQUENCY,              //  |
    ADF_500_HZ_TUNABLE,         //  |   ADF frequency
    ADF_EXTENDED_FREQUENCY,     //  |
    ADF_IDENTITY,
    ADF_SIGNAL_STRENGTH,
    ADF_MORSE_IDENT,
    ADF_CARD_RADIAL,            //  integer degrees 0-360
    COM_FREQUENCY,              //  BCD COM radio freq
    NAV1_FREQUENCY,             //  BCD NAV1 radio freq
    NAV1_VOR_RADIAL,
    NAV1_MORSE_IDENT,
    NAV2_FREQUENCY,             //  BCD NAV2 radio freq
    NAV2_VOR_RADIAL,
    NAV2_MORSE_IDENT,
    DME1_DISPLAY_TYPE,          //  FALSE=distance readout,  TRUE=speed in kts readout
    DME1_DISTANCE,              //  DME1 distance readout
    DME1_SPEED,                 //  DME1 speed readout
    DME1_MORSE_IDENT,
    DME2_DISPLAY_TYPE,          //  FALSE=distance readout,  TRUE=speed in kts readout
    DME2_DISTANCE,              //  DME2 distance readout
    DME2_SPEED,                 //  DME2 speed readout
    DME2_MORSE_IDENT,
    TRANSPONDER_CODE,           //  Octal Transponder code {0000 - 7777}
    ADF_NEEDLE,                 //  16 bit pseudodegrees
    VOR1_NEEDLE,                // +-127 correspond to +-10 if VOR or to +-2.5 if localiser.
    VOR1_GS_NEEDLE,             // +-120 correspond to +-0.7
    VOR1_BACK_COURSE_FLAGS,     //  Status of VOR1 (see BC_FLAG_ in FS6DEF.H)
    VOR1_TF_FLAG,
    VOR1_GS_FLAG,
    VOR1_OBI,
    VOR1_CODE,
    VOR1_IDENTITY,
    VOR1_MAG_VAR,
    VOR1_SIGNAL_STRENGTH,
    VOR2_NEEDLE,
    VOR2_BACK_COURSE_FLAGS,     //  Status of VOR2 (see BC_FLAG_ in FS6DEF.H)
    VOR2_TF_FLAG,
    VOR2_GS_FLAG,
    VOR2_OBI,
    VOR2_CODE,
    VOR2_IDENTITY,
    VOR2_MAG_VAR,
    VOR2_SIGNAL_STRENGTH,
    VOR2_BEARING_DEGREES,
    AIRCRAFT_ON_GROUND,         //  TRUE=aircraft is on the ground
    AIRSPEED,                   //  Airspeed - Indicated or True based on GLOBALP->indicated_aspd
    AIRSPEED_TRUE_CALIBRATE,    //  Degrees rotation of the tas calibration card
    BARBER_POLE_ASPD,           //  Movable Red-line airspeed  {1/128th knot/unit}
    MACH,                       //  mach, 64k=3.2 mach (would be better as UIF32)
    VERTICAL_SPEED,             //  Velocity Up, vertical speed {1/256th m/sec}
    MACH_MAX_OPERATE,
    STALL_WARNING,              //  TRUE=5 knots before stall
    OVERSPEED_WARNING,          //  TRUE=overspeed warning
    TURN_COORDINATOR_BALL_POS,  //  turn coordinator ball position {-127..0..127}
    DELTA_HEADING_RATE,
    PLANE_LATITUDE,             //  current position of our aircraft
    PLANE_LONGITUDE,            //  current position of our aircraft
    PLANE_ALTITUDE,             //  current position of our aircraft
    ALT_FROM_BAROMETRIC_PRESSURE,
    KOHLSMAN_SETTING_MB,        //  knob position millibars
    KOHLSMAN_SETTING_HG,        //  knob position inches of hg
    PLANE_PITCH_DEGREES,
    ATTITUDE_INDICATOR_PITCH_DEGREES,
    PLANE_BANK_DEGREES,
    ATTITUDE_INDICATOR_BANK_DEGREES,
    PLANE_HEADING_DEGREES_MAGNETIC,
    MAGNETIC_VAR,               //  magnetic north vs. true north angular error
    WHISKEY_COMPASS_DEGREES,    //  True degrees
    PLANE_HEADING_DEGREES_GYRO,
    GYRO_DRIFT_ERROR,
    PLANE_HEADING_DEGREES_TRUE,
    AIRCRAFT_AUTOPILOT_AVAILABLE,
    AIRCRAFT_FLAPS_AVAILABLE,
    AIRCRAFT_STALL_HORN_AVAILABLE,
    AIRCRAFT_ENGINE_MIXTURE_AVAILABLE,
    AIRCRAFT_CARB_HEAT_AVAILABLE,
    AIRCRAFT_SPOILER_AVAILABLE,
    AIRCRAFT_IS_TAIL_DRAGGER,
    AIRCRAFT_STROBES_AVAILABLE,
    AIRCRAFT_PROP_TYPE_AVAILABLE,   //  PROP_TYPE_FIXED, PROP_TYPE_MANUAL, PROP_TYPE_AUTOMATIC
    AIRCRAFT_TOE_BRAKES_AVAILABLE,
    AIRCRAFT_NAV1_AVAILABLE,
    AIRCRAFT_NAV2_AVAILABLE,
    AIRCRAFT_NAV1_OBS_AVAILABLE,
    AIRCRAFT_NAV2_OBS_AVAILABLE,
    AIRCRAFT_VOR2_GAUGE_AVAILABLE,
    AIRCRAFT_GYRO_DRIFT_AVAILABLE,  // fek: may not be used for bug #2131 but making other changes...build build build
    AUTOPILOT_ACTIVE,           //  autopilot master on/off
    AUTOPILOT_WING_LEVELER,     //  wing leveler on/off
    AUTOPILOT_NAV1_LOCK,        //  nav 1 lock on/off
    AUTOPILOT_HEADING_LOCK,     //  heading lock on/off
    AUTOPILOT_HEADING_LOCK_DIR, //  heading lock direction
    AUTOPILOT_ALTITUDE_LOCK,    //  altitude lock on/off
    AUTOPILOT_ALTITUDE_LOCK_VAR,//  altitude lock altitude in appropriate units
    AUTOPILOT_ATTITUDE_HOLD,    //  attitude hold
    AUTOPILOT_GLIDESLOPE_HOLD,  //  glideslope hold
    AUTOPILOT_APROACH_HOLD,     //  approach hold
    AUTOPILOT_BACKCOURSE_HOLD,  //  backcourse hold
    AUTOPILOT_YAW_DAMPER,       //  yaw damper
    AUTOPILOT_AIRSPEED_HOLD,    //  airspeed hold
    AUTOPILOT_AIRSPEED_HOLD_VAR,//  airspeed hold var
    AUTOPILOT_MACH_HOLD,        //  airspeed hold
    AUTOPILOT_MACH_HOLD_VAR,    //  airspeed hold var
    AUTOPILOT_VERTICAL_HOLD,    //  vertical hold
    AUTOPILOT_VERTICAL_HOLD_VAR,//  vertical speed hold var in appropriate units
    AUTOPILOT_ALTITUDE_MANUALLY_TUNABLE,
    AUTOPILOT_HEADING_MANUALLY_TUNABLE,
    AUTOPILOT_AUTO_THROTTLE_ARM,
    AUTOPILOT_TAKEOFF_POWER_ACTIVE,
    ENGINE_RPM_HOLD,
    ENGINE_CONTROL_SELECT,              //  which engine is being controlled
    ENGINE1,
    ENGINE1_THROTTLE_LEVER_POS, //  throttle position           (16k = 100% throttle position)
    ENGINE1_PROPELLER_LEVER_POS,    //  propeller lever position    (16k = 100% prop setting)
    ENGINE1_MIXTURE_LEVER_POS,      //  mixture position            (16k = 100% mixture position)
    ENGINE1_COMBUSTION,         //  combustion flag             (combustion = TRUE)
    ENGINE1_STARTER_SWITCH_POS, //  starter switch position
    ENGINE1_MAGNETO_LEFT,           //  left magneto status         (activated = 1)
    ENGINE1_MAGNETO_RIGHT,          //  right magneto status        (activated = 1)
    ENGINE1_N1_RPM,             //  gas producer (RPM)          (16k = 100% RPM)
    ENGINE1_N2_RPM,             //  power (RPM)                 (16k = 100% RPM)
    ENGINE1_FF_GPH,
    ENGINE1_FF_PPH,             //  fuel flow PPH
    ENGINE1_FF_PPH_SSL,         //  fuel flow (PPH)             (16k = 100%, Standard sea level conditions)
    ENGINE1_TORQUE,             //  torque produced ( FT*LBS )
    ENGINE1_ANTI_ICE_SWITCH,        //  anti ice switch
    ENGINE1_PRESSURE_RATIO,     //  engine pressure ratio       (65k = 6.4)
    ENGINE1_PRESSURE_BUG_POS,       //  epr governed engine setting (16k = 100% epr setting)
    ENGINE1_EGT,                    //  exhaust gas temp (degC)     (16k = 860 deg)
    ENGINE1_EGT_BUG_POS,            //  egt governed engine setting (16k = 100% egt setting)
    ENGINE1_CHT,                    //  cylinder head temperature
    ENGINE1_OIL_TEMPERATURE,        //  oil temperature (degC)      (16k = 140 deg)
    ENGINE1_OIL_PRESSURE,           //  oil pressure (PSI)          (16k = 55 PSI)
    ENGINE1_OIL_QUANTITY,           //  oil quantity                (16k = 100%)
    ENGINE1_HYDRAULIC_PRESSURE, //  hydraulic pressure (PSI)    (16k = 4 psi)
    ENGINE1_HYDRAULIC_QUANTITY, //  hydraulic quantity          (16k = 100%)
    ENGINE1_MANIFOLD_PRESSURE,      //  manifold pressure           (65k = 64)
    ENGINE1_ENGINE_VIBRATION,       //  oil quantity                (16k = 5)
    ENGINE1_RPM_SCALER,         //  *16384 gives actual prop rpm in dx (= 65535 for jets)
    ENGINE1_TURBINE_TEMPERATURE,    //  (DegC * 16384)
    ENGINE1_TORQUE_PERCENT,         //  (FT/LBS * 16384)
    ENGINE1_FUEL_PRESSURE,              //  (PSI * 16384)
    ENGINE1_ELECTRICAL_LOAD,            //  (Max Load * 16384)
    ENGINE1_TRANSMISSION_PRESSURE,      //  (PSI * 16384)
    ENGINE1_TRANSMISSION_TEMPERATURE,   //  (DegC * 16384)
    ENGINE1_ROTOR_RPM,                  //  (Max 8 16384)
    ENGINE2,
    ENGINE2_THROTTLE_LEVER_POS, //  throttle position (0-16384=>0-100%throttle position)
    ENGINE2_PROPELLER_LEVER_POS,//  propeller lever position (0-16384=>0-100%prop setting)
    ENGINE2_MIXTURE_LEVER_POS,  //  mixture position (0-16384=>0-100%mixture position)
    ENGINE2_COMBUSTION,         //  combustion flag (combustion = TRUE)
    ENGINE2_STARTER_SWITCH_POS, //  starter switch position
    ENGINE2_MAGNETO_LEFT,       //  left magneto status (activated = 1)
    ENGINE2_MAGNETO_RIGHT,      //  right magneto status (activated = 1)
    ENGINE2_N1_RPM,             //  gas producer RPM (0-16384=>0-100%RPM)
    ENGINE2_N2_RPM,             //  power RPM (0-16384=>0-100%RPM)
    ENGINE2_FF_GPH,
    ENGINE2_FF_PPH,             //  PPH
    ENGINE2_FF_PPH_SSL,         //  fuel flow (0-16384=>0-100%)PPH, Standard sea level conditions
    ENGINE2_TORQUE,             //  torque produced ( FT*LBS )
    ENGINE2_ANTI_ICE_SWITCH,    //  anti ice switch
    ENGINE2_PRESSURE_RATIO,     //  engine pressure ratio (0-65536=>0-6.4)
    ENGINE2_PRESSURE_BUG_POS,   //  epr governed engine setting (0-16384=>0-100%epr setting)
    ENGINE2_EGT,                //  exhaust gas temperature (degC)
    ENGINE2_EGT_BUG_POS,        //  egt governed engine setting (0-16384=>0-100%egt setting)
    ENGINE2_CHT,                //  cylinder head temperature
    ENGINE2_OIL_TEMPERATURE,    //  oil temperature (degC)
    ENGINE2_OIL_PRESSURE,       //  oil pressure (PSI)
    ENGINE2_OIL_QUANTITY,       //  oil quantity (0-16384 => 0-100%)
    ENGINE2_HYDRAULIC_PRESSURE, //  hydraulic pressure (0-16384 => 0-4 psi)
    ENGINE2_HYDRAULIC_QUANTITY, //  hydraulic quantity (0-16384 => 0-100%)
    ENGINE2_MANIFOLD_PRESSURE,  //  manifold pressure (0-65536=>0-64)
    ENGINE2_ENGINE_VIBRATION,   //  oil quantity (0-16384 => 0-5)
    ENGINE2_RPM_SCALER,         //  *16384 gives actual prop rpm in dx (= 65535 for jets)
    ENGINE2_TURBINE_TEMPERATURE,        //  (DegC * 16384)
    ENGINE2_TORQUE_PERCENT,             //  (FT/LBS * 16384)
    ENGINE2_FUEL_PRESSURE,              //  (PSI * 16384)
    ENGINE2_ELECTRICAL_LOAD,            //  (Max Load * 16384)
    ENGINE2_TRANSMISSION_PRESSURE,      //  (PSI * 16384)
    ENGINE2_TRANSMISSION_TEMPERATURE,   //  (DegC * 16384)
    ENGINE2_ROTOR_RPM,                  //  (Max 8 16384)
    ENGINE3,
    ENGINE3_THROTTLE_LEVER_POS, //  throttle position (0-16384=>0-100%throttle position)
    ENGINE3_PROPELLER_LEVER_POS,//  propeller lever position (0-16384=>0-100%prop setting)
    ENGINE3_MIXTURE_LEVER_POS,  //  mixture position (0-16384=>0-100%mixture position)
    ENGINE3_COMBUSTION,         //  combustion flag (combustion = TRUE)
    ENGINE3_STARTER_SWITCH_POS, //  starter switch position
    ENGINE3_MAGNETO_LEFT,       //  left magneto status (activated = 1)
    ENGINE3_MAGNETO_RIGHT,      //  right magneto status (activated = 1)
    ENGINE3_N1_RPM,             //  gas producer RPM (0-16384=>0-100%RPM)
    ENGINE3_N2_RPM,             //  power RPM (0-16384=>0-100%RPM)
    ENGINE3_FF_GPH,
    ENGINE3_FF_PPH,             //  fuel flow PPH
    ENGINE3_FF_PPH_SSL,         //  fuel flow (0-16384=>0-100%)PPH, Standard sea level conditions
    ENGINE3_TORQUE,             //  torque produced ( FT*LBS )
    ENGINE3_ANTI_ICE_SWITCH,    //  anti ice switch
    ENGINE3_PRESSURE_RATIO,     //  engine pressure ratio (0-65536=>0-6.4)
    ENGINE3_PRESSURE_BUG_POS,   //  epr governed engine setting (0-16384=>0-100%epr setting)
    ENGINE3_EGT,                //  exhaust gas temperature (degC)
    ENGINE3_EGT_BUG_POS,        //  egt governed engine setting (0-16384=>0-100%egt setting)
    ENGINE3_CHT,                //  cylinder head temperature
    ENGINE3_OIL_TEMPERATURE,    //  oil temperature (degC)
    ENGINE3_OIL_PRESSURE,       //  oil pressure (PSI)
    ENGINE3_OIL_QUANTITY,       //  oil quantity (0-16384 => 0-100%)
    ENGINE3_HYDRAULIC_PRESSURE, //  hydraulic pressure (0-16384 => 0-4 psi)
    ENGINE3_HYDRAULIC_QUANTITY, //  hydraulic quantity (0-16384 => 0-100%)
    ENGINE3_MANIFOLD_PRESSURE,  //  manifold pressure (0-65536=>0-64)
    ENGINE3_ENGINE_VIBRATION,   //  oil quantity (0-16384 => 0-5)
    ENGINE3_RPM_SCALER,         //  *16384 gives actual prop rpm in dx (= 65535 for jets)
    ENGINE3_TURBINE_TEMPERATURE,        //  (DegC * 16384)
    ENGINE3_TORQUE_PERCENT,             //  (FT/LBS * 16384)
    ENGINE3_FUEL_PRESSURE,              //  (PSI * 16384)
    ENGINE3_ELECTRICAL_LOAD,            //  (Max Load * 16384)
    ENGINE3_TRANSMISSION_PRESSURE,      //  (PSI * 16384)
    ENGINE3_TRANSMISSION_TEMPERATURE,   //  (DegC * 16384)
    ENGINE3_ROTOR_RPM,                  //  (Max 8 16384)
    ENGINE4,
    ENGINE4_THROTTLE_LEVER_POS, //  throttle position (0-16384=>0-100%throttle position)
    ENGINE4_PROPELLER_LEVER_POS,//  propeller lever position (0-16384=>0-100%prop setting)
    ENGINE4_MIXTURE_LEVER_POS,  //  mixture position (0-16384=>0-100%mixture position)
    ENGINE4_COMBUSTION,         //  combustion flag (combustion = TRUE)
    ENGINE4_STARTER_SWITCH_POS, //  starter switch position
    ENGINE4_MAGNETO_LEFT,       //  left magneto status (activated = 1)
    ENGINE4_MAGNETO_RIGHT,      //  right magneto status (activated = 1)
    ENGINE4_N1_RPM,             //  gas producer RPM (0-16384=>0-100%RPM)
    ENGINE4_N2_RPM,             //  power RPM (0-16384=>0-100%RPM)
    ENGINE4_FF_GPH,
    ENGINE4_FF_PPH,             //  fuel flow PPH
    ENGINE4_FF_PPH_SSL,         //  fuel flow (0-16384=>0-100%)PPH, Standard sea level conditions
    ENGINE4_TORQUE,             //  torque produced ( FT*LBS )
    ENGINE4_ANTI_ICE_SWITCH,    //  anti ice switch
    ENGINE4_PRESSURE_RATIO,     //  engine pressure ratio (0-65536=>0-6.4)
    ENGINE4_PRESSURE_BUG_POS,   //  epr governed engine setting (0-16384=>0-100%epr setting)
    ENGINE4_EGT,                //  exhaust gas temperature (degC)
    ENGINE4_EGT_BUG_POS,        //  egt governed engine setting (0-16384=>0-100%egt setting)
    ENGINE4_CHT,                //  cylinder head temperature
    ENGINE4_OIL_TEMPERATURE,    //  oil temperature (degC)
    ENGINE4_OIL_PRESSURE,       //  oil pressure (PSI)
    ENGINE4_OIL_QUANTITY,       //  oil quantity (0-16384 => 0-100%)
    ENGINE4_HYDRAULIC_PRESSURE, //  hydraulic pressure (0-16384 => 0-4 psi)
    ENGINE4_HYDRAULIC_QUANTITY, //  hydraulic quantity (0-16384 => 0-100%)
    ENGINE4_MANIFOLD_PRESSURE,  //  manifold pressure (0-65536=>0-64)
    ENGINE4_ENGINE_VIBRATION,   //  oil quantity (0-16384 => 0-5)
    ENGINE4_RPM_SCALER,         //  *16384 gives actual prop rpm in dx (= 65535 for jets)
    ENGINE4_TURBINE_TEMPERATURE,        //  (DegC * 16384)
    ENGINE4_TORQUE_PERCENT,             //  (FT/LBS * 16384)
    ENGINE4_FUEL_PRESSURE,              //  (PSI * 16384)
    ENGINE4_ELECTRICAL_LOAD,            //  (Max Load * 16384)
    ENGINE4_TRANSMISSION_PRESSURE,      //  (PSI * 16384)
    ENGINE4_TRANSMISSION_TEMPERATURE,   //  (DegC * 16384)
    ENGINE4_ROTOR_RPM,                  //  (Max 8 16384)
    NUMBER_OF_ENGINES,                  //  1=single 2=twin ...
    PROP_ADVANCE_SELECTION,             //  0=fixed 1=optimal 2=manual
    THROTTLE_LOWER_LIMIT,               //  set by sim for thrust reversers
    OIL_QUANTITY_TOTAL,                 //  0..7fff (8 qt.)
    SYSTEMS_AVAILABLE,                  //  OBSOLETE!
    INSTRUMENTS_AVAILABLE,              //  OBSOLETE
    PP_ADF,                             //  partial panel variables
    PP_AIR,
    PP_ALTIM,
    PP_ATTITUDE,
    PP_COM,
    PP_COMPASS,
    PP_ELECT,                           // there is no electricity in panels circuit
    PP_ENGINE,
    PP_FUEL_IND,
    PP_HEADING,
    PP_VERT_VEL,
    PP_XPNDR,
    PP_NAV,
    PP_PITOT,
    PP_TURN_COORD,
    PP_VACUUM,
    FUEL_TANK_CENTER_LEVEL,
    FUEL_TANK_CENTER_CAPACITY,
    FUEL_TANK_LEFT_MAIN_LEVEL,
    FUEL_TANK_LEFT_MAIN_CAPACITY,
    FUEL_TANK_LEFT_AUX_LEVEL,
    FUEL_TANK_LEFT_AUX_CAPACITY,
    FUEL_TANK_LEFT_TIP_LEVEL,
    FUEL_TANK_LEFT_TIP_CAPACITY,
    FUEL_TANK_RIGHT_MAIN_LEVEL,
    FUEL_TANK_RIGHT_MAIN_CAPACITY,
    FUEL_TANK_RIGHT_AUX_LEVEL,
    FUEL_TANK_RIGHT_AUX_CAPACITY,
    FUEL_TANK_RIGHT_TIP_LEVEL,
    FUEL_TANK_RIGHT_TIP_CAPACITY,
    FUEL_QUANTITY_RIGHT,        //  Total Gallons
    FUEL_QUANTITY_LEFT,         //  Total Gallons
    FUEL_QUANTITY_CENTER,       //  Total Gallons
    FUEL_WEGHT_PER_GALLON,      //  in pounds I.F  (6 lbs/gal = 1536)
    FUEL_TANK_SELECTOR,         //  see FUEL_TANK_SELECTOR_ enum values
    CROSS_FEED_SELECTOR,        //  OFF, LEFT_TO_RIGHT, or RIGHT_TO_LEFT
    OBSOLETE_YOKE_POS_Y,        // use ELEVATOR_DEFLECTION
    OBSOLETE_YOKE_IND_Y,        // use ELEVATOR_DEFLECTION
    OBSOLETE_YOKE_POS_X,        // use AILERON_DEFLECTION
    OBSOLETE_YOKE_IND_X,        // use AILERON_DEFLECTION
    OBSOLETE_AILERON_POS,       // use AILERON_DEFLECTION
    OBSOLETE_RUDDER_PEDAL_POS,  // use RUDDER_DEFLECTION
    OBSOLETE_RUDDER_PEDAL_IND,  // use RUDDER_DEFLECTION
    OBSOLETE_RUDDER_POS,        // use RUDDER_DEFLECTION
    OBSOLETE_ELEVATOR_POS,      // use ELEVATOR_DEFLECTION
    OBSOLETE_ELEVATOR_TRIM_POS, // use ELEVATOR_TRIM
    OBSOLETE_ELEVATOR_TRIM_IND, // use ELEVATOR_TRIM
    BRAKES_LEFT_POS,            //  0=off 32k=full brakes
    BRAKES_RIGHT_POS,           //  0=off 32k=full brakes
    BRAKE_IND,                  //  0=off 16k=full brakes
    PARKING_BRAKE_POS,          //  0=off 32k=full  parking brakes
    SPOILERS_ARMED,
    SPOILERS_HANDLE_POS,
    SPOILERS_POS_LEFT,
    SPOILERS_POS_RIGHT,
    FLAPS_HANDLE_POS,
    FLAPS_POS_LEFT,
    FLAPS_POS_RIGHT,
    GEAR_HANDLE_POS,
    GEAR_POS_NOSE,
    GEAR_POS_LEFT,
    GEAR_POS_RIGHT,
    DISPLAY_UNITS,              //  english vs. metric system
    SIM_SPEED,                  //  time dilation factor for sim equations
    ZOOM_FACTOR,                //  zoom value of current window in real units
    REALISM_SENSE,
    REALISM_SYSTEMS,
    RELIABILITY_SENSE,          //  0 = unreliable - 100 = totally reliable
    AMBIENT_TEMP_DEGREES_C,     //
    AMBIENT_PRES_MBAR,          //  Millibars * 16
    AMBIENT_WIND_VEL,           //
    AMBIENT_WIND_DIR,           //
    AMBIENT_WINDE,              //  MPS x(east) wind component
    AMBIENT_WINDN,              //  MPS z(up) wind component
    AMBIENT_WINDA,              //  MPS y(north) wind component
    BAROMETRIC_PRESSURE,        //  barometric pressure experienced
    ANGLE_OF_ATTACK_INDICATOR,
    TOTAL_AIR_TEMP,
    G_FORCE,
    CHARGING_AMPS,              //  charging system amps - 1 amp=65535
    SUCTION_PRESSURE,           //  in hg
    MARKER_BEACON_STATE,        //  0=no beacon, 1=outer, 2=middle, 3=inner
    CURRENT_DME,                //  DMECUR_DME1 or DMECUR_DME2
    PANEL_STATE_FLAGS,
    GET_GUN_AMMO,               //  OBSOLETE
    GET_CANNON_AMMO,            //  OBSOLETE
    GET_ROCKET_AMMO,            //  OBSOLETE
    GET_BOMB_AMMO,              //  OBSOLETE
    ENGINE_PRIMER,              // 0.0 -> 1.0 == in -> out
    COWL_FLAPS,                 // 0.0 -> 1.0 == closed -> open
    MASTER_ALTERNATOR,          // 0.0 -> 1.0 == off -> on
    MASTER_BATTERY,             // 0.0 -> 1.0 == off -> on
    CARB_HEAT,                  // 0.0 -> 1.0 == off -> on
    FLIGHT_TIME,                // in 1/10 of hours
    FUEL_PUMP,                  // 0.0 -> 1.0 == off -> on
    BEACON_LIGHTS,              // 0.0 -> 1.0 == off -> on
    TAXI_LIGHTS,                // 0.0 -> 1.0 == off -> on
    RADIO_STACK_VISIBLE,        // 0.0 -> 1.0 == off -> on
    HORIZON_BAR_OFFSET,         // -10 deg to + 10 deg
    CURRENT_DME_DISTANCE,
    CURRENT_DME_SPEED,
    CURRENT_DME_MIN,
    WARNING_FUEL,
    WARNING_FUEL_L,
    WARNING_FUEL_R,
    WARNING_VACUUM,
    WARNING_VACUUM_L,
    WARNING_VACUUM_R,
    WARNING_OIL_PSI,
    WARNING_VOLTAGE,
    FUEL_TANK_CENTER2_LEVEL,
    FUEL_TANK_CENTER2_CAPACITY,
    FUEL_QUANTITY_CENTER2,                       // Total Gallons
    TOTAL_FUEL_QUANTITY_GALLONS,
    SELECTED_FUEL_QUANTITY_GALLONS,
    SELECTED_FUEL_QUANTITY_LITERS,
    SELECTED_FUEL_QUANTITY_PERCENT,
    RECIP_ENGINE1_ENGINE_RPM,
    RECIP_ENGINE1_MANIFOLD_PRESSURE,
    RECIP_ENGINE1_THROTTLE_LEVER_POS,
    RECIP_ENGINE1_MIXTURE_LEVER_POS,
    RECIP_ENGINE1_PROP_LEVER_POS,
    RECIP_ENGINE1_COWL_FLAP_POS,                //0 = closed, 1 = open
    RECIP_ENGINE1_CARB_HEAT_POS,                //0 = off, 1 = on
    RECIP_ENGINE1_ALTERNATE_AIR_POS,            //0 = closed, 1 = off
    RECIP_ENGINE1_COOLANT_RESERVOIR_PCT,
    RECIP_ENGINE1_LEFT_MAG,
    RECIP_ENGINE1_RIGHT_MAG,
    RECIP_ENGINE1_STARTER,
    RECIP_ENGINE1_BRAKE_POWER,                  //power delivered to the shaft
    RECIP_ENGINE1_SHAFT_TORQUE,                 //torque delivered to the shaft
    RECIP_ENGINE1_PROP_TORQUE,                  //torque required by prop
    RECIP_ENGINE1_STARTER_TORQUE,               //torque applied by starter
    RECIP_ENGINE1_COMBUSTION,                   //combustion flag
    RECIP_ENGINE1_TURBOCHARGER_FAILED,
    RECIP_ENGINE1_EMERGENCY_BOOST_ACTIVE,       //like WEP in the P51
    RECIP_ENGINE1_EMERGENCY_BOOST_ELAPSED_TIME, //how long emergency has been active
    RECIP_ENGINE1_WASTEGATE_POS,                //position of wastegate controller 1=closed (full boost), 0=open (no boost)
    RECIP_ENGINE1_PROP_BETA,                    //blade angle (relative to plane of rotation)
    RECIP_ENGINE1_THRUST,                       //lbs
    RECIP_ENGINE1_EGT_DEGR,                     //EGT degrees Rankine
    RECIP_ENGINE1_TIT_DEGR,                     //Turbine Inlet Temperature degrees Rankine
    RECIP_ENGINE1_CHT_DEGR,                     //CHT degrees Rankine
    RECIP_ENGINE1_OIL_TEMP_DEGR,                //Oil Temperature degrees Rankine
    RECIP_ENGINE1_RADIATOR_DEGR,                //Radiator temperature
    RECIP_ENGINE1_OIL_PRESS_PSF,                //Oil Pressure lbs/sqft
    RECIP_ENGINE1_OIL_LEAK_PCT,                 //Percent Oil leaked
    RECIP_ENGINE1_FUEL_AVAILABLE,               //Fuel available to engine?
    RECIP_ENGINE1_FUELFLOW_PPH,                 //Fuel flow in lbs/hr
    RECIP_ENGINE1_TANK_SELECTOR,                //Fuel tank selector
    RECIP_ENGINE1_TANKS_USED,                   //Fuel tanks used
    RECIP_ENGINE1_NUMBER_OF_TANKS_USED,         //Number of fuel tanks used
    RECIP_ENGINE1_FUEL_PRESSURE_PSF,            //Fuel pressure in lbs/sqft
    RECIP_ENGINE1_COMBUSTION_SOUND_PCT,         //Percent of Sound (0 - 1)
    RECIP_ENGINE1_INDUCED_VELOCITY,             //fps, velocity induced by prop
    RECIP_ENGINE1_DAMAGE_PERCENT,               //0-100%
    RECIP_ENGINE2_ENGINE_RPM,
    RECIP_ENGINE2_MANIFOLD_PRESSURE,
    RECIP_ENGINE2_THROTTLE_LEVER_POS,
    RECIP_ENGINE2_MIXTURE_LEVER_POS,
    RECIP_ENGINE2_PROP_LEVER_POS,
    RECIP_ENGINE2_COWL_FLAP_POS,                //0 = closed, 1 = open
    RECIP_ENGINE2_CARB_HEAT_POS,                //0 = off, 1 = on
    RECIP_ENGINE2_ALTERNATE_AIR_POS,            //0 = closed, 1 = off
    RECIP_ENGINE2_COOLANT_RESERVOIR_PCT,
    RECIP_ENGINE2_LEFT_MAG,
    RECIP_ENGINE2_RIGHT_MAG,
    RECIP_ENGINE2_STARTER,
    RECIP_ENGINE2_BRAKE_POWER,                  //power delivered to the shaft
    RECIP_ENGINE2_SHAFT_TORQUE,                 //torque delivered to the shaft
    RECIP_ENGINE2_PROP_TORQUE,                  //torque required by prop
    RECIP_ENGINE2_STARTER_TORQUE,               //torque applied by starter
    RECIP_ENGINE2_COMBUSTION,                   //combustion flag
    RECIP_ENGINE2_TURBOCHARGER_FAILED,
    RECIP_ENGINE2_EMERGENCY_BOOST_ACTIVE,       //like WEP in the P51
    RECIP_ENGINE2_EMERGENCY_BOOST_ELAPSED_TIME, //how long emergency has been active
    RECIP_ENGINE2_WASTEGATE_POS,                //position of wastegate controller 1=closed (full boost), 0=open (no boost)
    RECIP_ENGINE2_PROP_BETA,                    //blade angle (relative to plane of rotation)
    RECIP_ENGINE2_THRUST,                       //lbs
    RECIP_ENGINE2_EGT_DEGR,                     //EGT degrees Rankine
    RECIP_ENGINE2_TIT_DEGR,                     //Turbine Inlet Temperature degrees Rankine
    RECIP_ENGINE2_CHT_DEGR,                     //CHT degrees Rankine
    RECIP_ENGINE2_OIL_TEMP_DEGR,                //Oil Temperature degrees Rankine
    RECIP_ENGINE2_RADIATOR_DEGR,                //Radiator temperature
    RECIP_ENGINE2_OIL_PRESS_PSF,                //Oil Pressure lbs/sqft
    RECIP_ENGINE2_OIL_LEAK_PCT,                 //Percent Oil leaked
    RECIP_ENGINE2_FUEL_AVAILABLE,               //Fuel available to engine?
    RECIP_ENGINE2_FUELFLOW_PPH,                 //Fuel flow in lbs/hr
    RECIP_ENGINE2_TANK_SELECTOR,                //Fuel tank selector
    RECIP_ENGINE2_TANKS_USED,                   //Fuel tanks used
    RECIP_ENGINE2_NUMBER_OF_TANKS_USED,         //Number of fuel tanks used
    RECIP_ENGINE2_FUEL_PRESSURE_PSF,            //Fuel pressure in lbs/sqft
    RECIP_ENGINE2_COMBUSTION_SOUND_PCT,         //Percent of Sound (0 - 1)
    RECIP_ENGINE2_INDUCED_VELOCITY,             //fps, velocity induced by prop
    RECIP_ENGINE2_DAMAGE_PERCENT,               //0-100%
    RECIP_ENGINE3_ENGINE_RPM,
    RECIP_ENGINE3_MANIFOLD_PRESSURE,
    RECIP_ENGINE3_THROTTLE_LEVER_POS,
    RECIP_ENGINE3_MIXTURE_LEVER_POS,
    RECIP_ENGINE3_PROP_LEVER_POS,
    RECIP_ENGINE3_COWL_FLAP_POS,                //0 = closed, 1 = open
    RECIP_ENGINE3_CARB_HEAT_POS,                //0 = off, 1 = on
    RECIP_ENGINE3_ALTERNATE_AIR_POS,            //0 = closed, 1 = off
    RECIP_ENGINE3_COOLANT_RESERVOIR_PCT,
    RECIP_ENGINE3_LEFT_MAG,
    RECIP_ENGINE3_RIGHT_MAG,
    RECIP_ENGINE3_STARTER,
    RECIP_ENGINE3_BRAKE_POWER,                  //power delivered to the shaft
    RECIP_ENGINE3_SHAFT_TORQUE,                 //torque delivered to the shaft
    RECIP_ENGINE3_PROP_TORQUE,                  //torque required by prop
    RECIP_ENGINE3_STARTER_TORQUE,               //torque applied by starter
    RECIP_ENGINE3_COMBUSTION,                   //combustion flag
    RECIP_ENGINE3_TURBOCHARGER_FAILED,
    RECIP_ENGINE3_EMERGENCY_BOOST_ACTIVE,       //like WEP in the P51
    RECIP_ENGINE3_EMERGENCY_BOOST_ELAPSED_TIME, //how long emergency has been active
    RECIP_ENGINE3_WASTEGATE_POS,                //position of wastegate controller 1=closed (full boost), 0=open (no boost)
    RECIP_ENGINE3_PROP_BETA,                    //blade angle (relative to plane of rotation)
    RECIP_ENGINE3_THRUST,                       //lbs
    RECIP_ENGINE3_EGT_DEGR,                     //EGT degrees Rankine
    RECIP_ENGINE3_TIT_DEGR,                     //Turbine Inlet Temperature degrees Rankine
    RECIP_ENGINE3_CHT_DEGR,                     //CHT degrees Rankine
    RECIP_ENGINE3_OIL_TEMP_DEGR,                //Oil Temperature degrees Rankine
    RECIP_ENGINE3_RADIATOR_DEGR,                //Radiator temperature
    RECIP_ENGINE3_OIL_PRESS_PSF,                //Oil Pressure lbs/sqft
    RECIP_ENGINE3_OIL_LEAK_PCT,                 //Percent Oil leaked
    RECIP_ENGINE3_FUEL_AVAILABLE,               //Fuel available to engine?
    RECIP_ENGINE3_FUELFLOW_PPH,                 //Fuel flow in lbs/hr
    RECIP_ENGINE3_TANK_SELECTOR,                //Fuel tank selector
    RECIP_ENGINE3_TANKS_USED,                   //Fuel tanks used
    RECIP_ENGINE3_NUMBER_OF_TANKS_USED,         //Number of fuel tanks used
    RECIP_ENGINE3_FUEL_PRESSURE_PSF,            //Fuel pressure in lbs/sqft
    RECIP_ENGINE3_COMBUSTION_SOUND_PCT,         //Percent of Sound (0 - 1)
    RECIP_ENGINE3_INDUCED_VELOCITY,             //fps, velocity induced by prop
    RECIP_ENGINE3_DAMAGE_PERCENT,               //0-100%
    RECIP_ENGINE4_ENGINE_RPM,
    RECIP_ENGINE4_MANIFOLD_PRESSURE,
    RECIP_ENGINE4_THROTTLE_LEVER_POS,
    RECIP_ENGINE4_MIXTURE_LEVER_POS,
    RECIP_ENGINE4_PROP_LEVER_POS,
    RECIP_ENGINE4_COWL_FLAP_POS,                //0 = closed, 1 = open
    RECIP_ENGINE4_CARB_HEAT_POS,                //0 = off, 1 = on
    RECIP_ENGINE4_ALTERNATE_AIR_POS,            //0 = closed, 1 = off
    RECIP_ENGINE4_COOLANT_RESERVOIR_PCT,
    RECIP_ENGINE4_LEFT_MAG,
    RECIP_ENGINE4_RIGHT_MAG,
    RECIP_ENGINE4_STARTER,
    RECIP_ENGINE4_BRAKE_POWER,                  //power delivered to the shaft
    RECIP_ENGINE4_SHAFT_TORQUE,                 //torque delivered to the shaft
    RECIP_ENGINE4_PROP_TORQUE,                  //torque required by prop
    RECIP_ENGINE4_STARTER_TORQUE,               //torque applied by starter
    RECIP_ENGINE4_COMBUSTION,                   //combustion flag
    RECIP_ENGINE4_TURBOCHARGER_FAILED,
    RECIP_ENGINE4_EMERGENCY_BOOST_ACTIVE,       //like WEP in the P51
    RECIP_ENGINE4_EMERGENCY_BOOST_ELAPSED_TIME, //how long emergency has been active
    RECIP_ENGINE4_WASTEGATE_POS,                //position of wastegate controller 1=closed (full boost), 0=open (no boost)
    RECIP_ENGINE4_PROP_BETA,                    //blade angle (relative to plane of rotation)
    RECIP_ENGINE4_THRUST,                       //lbs
    RECIP_ENGINE4_EGT_DEGR,                     //EGT degrees Rankine
    RECIP_ENGINE4_TIT_DEGR,                     //Turbine Inlet Temperature degrees Rankine
    RECIP_ENGINE4_CHT_DEGR,                     //CHT degrees Rankine
    RECIP_ENGINE4_OIL_TEMP_DEGR,                //Oil Temperature degrees Rankine
    RECIP_ENGINE4_RADIATOR_DEGR,                //Radiator temperature
    RECIP_ENGINE4_OIL_PRESS_PSF,                //Oil Pressure lbs/sqft
    RECIP_ENGINE4_OIL_LEAK_PCT,                 //Percent Oil leaked
    RECIP_ENGINE4_FUEL_AVAILABLE,               //Fuel available to engine?
    RECIP_ENGINE4_FUELFLOW_PPH,                 //Fuel flow in lbs/hr
    RECIP_ENGINE4_TANK_SELECTOR,                //Fuel tank selector
    RECIP_ENGINE4_TANKS_USED,                   //Fuel tanks used
    RECIP_ENGINE4_NUMBER_OF_TANKS_USED,         //Number of fuel tanks used
    RECIP_ENGINE4_FUEL_PRESSURE_PSF,            //Fuel pressure in lbs/sqft
    RECIP_ENGINE4_COMBUSTION_SOUND_PCT,         //Percent of Sound (0 - 1)
    RECIP_ENGINE4_INDUCED_VELOCITY,             //fps, velocity induced by prop
    RECIP_ENGINE4_DAMAGE_PERCENT,               //0-100%
    FUEL_QUANTITY_CENTER3,                      //Total Gallons
    SCORE_STRING_QUICK_COMBAT,
    SCORE_STRING_MULTIPLAYER,
    IS_MULTIPLAYER_TEAM_COMBAT,
    VOR1_BEARING_DEGREES,
    FORWARD_GROUND_VELOCITY,                    // in ft/sec
    SIDE_GROUND_VELOCITY,                       // in ft/sec
    VERTICAL_GROUND_VELOCITY,                   // in ft/sec
    NORTH_VELOCITY,                             // in ft/sec
    EAST_VELOCITY,                              // in ft/sec
    VERTICAL_VELOCITY,                          // in ft/sec
    CLOCK_TOTAL_SECONDS,                //  local clock time, seconds since midnight
    GENERAL_ENGINE1_THROTTLE_LEVER_POS,
    GENERAL_ENGINE1_PROPELLER_LEVER_POS,
    GENERAL_ENGINE1_MIXTURE_LEVER_POS,
    GENERAL_ENGINE1_OIL_TEMP,
    GENERAL_ENGINE1_OIL_PRES,
    GENERAL_ENGINE1_STARTER,
    GENERAL_ENGINE1_FAILURE,
    GENERAL_ENGINE1_GENERATOR_SWITCH,
    GENERAL_ENGINE1_GENERATOR_ACTIVE,
    GENERAL_ENGINE1_EGT,
    GENERAL_ENGINE2_THROTTLE_LEVER_POS,
    GENERAL_ENGINE2_PROPELLER_LEVER_POS,
    GENERAL_ENGINE2_MIXTURE_LEVER_POS,
    GENERAL_ENGINE2_OIL_TEMP,
    GENERAL_ENGINE2_OIL_PRES,
    GENERAL_ENGINE2_STARTER,
    GENERAL_ENGINE2_FAILURE,
    GENERAL_ENGINE2_GENERATOR_SWITCH,
    GENERAL_ENGINE2_GENERATOR_ACTIVE,
    GENERAL_ENGINE2_EGT,
    GENERAL_ENGINE3_THROTTLE_LEVER_POS,
    GENERAL_ENGINE3_PROPELLER_LEVER_POS,
    GENERAL_ENGINE3_MIXTURE_LEVER_POS,
    GENERAL_ENGINE3_OIL_TEMP,
    GENERAL_ENGINE3_OIL_PRES,
    GENERAL_ENGINE3_STARTER,
    GENERAL_ENGINE3_FAILURE,
    GENERAL_ENGINE3_GENERATOR_SWITCH,
    GENERAL_ENGINE3_GENERATOR_ACTIVE,
    GENERAL_ENGINE3_EGT,
    GENERAL_ENGINE4_THROTTLE_LEVER_POS,
    GENERAL_ENGINE4_PROPELLER_LEVER_POS,
    GENERAL_ENGINE4_MIXTURE_LEVER_POS,
    GENERAL_ENGINE4_OIL_TEMP,
    GENERAL_ENGINE4_OIL_PRES,
    GENERAL_ENGINE4_STARTER,
    GENERAL_ENGINE4_FAILURE,
    GENERAL_ENGINE4_GENERATOR_SWITCH,
    GENERAL_ENGINE4_GENERATOR_ACTIVE,
    GENERAL_ENGINE4_EGT,
    NAV1_COMMNAV_TEST,
    NAV2_COMMNAV_TEST,
    COM1_AUTOSWITCH_ON,
    NAV1_AUTOSWITCH_ON,
    COM2_AUTOSWITCH_ON,
    NAV2_AUTOSWITCH_ON,
    ELAPSED_SECONDS,
    G_FORCE_MAXIMUM,
    G_FORCE_MINIMUM,
    ENGINE_WORKING_TIME,
    ENGINE1_MAX_RPM,
    ENGINE2_MAX_RPM,
    ENGINE3_MAX_RPM,
    ENGINE4_MAX_RPM,
    ATTITUDE_BARS_POSITION,
    RAD_INS_SWITCH,     // used in concorde only
    RADIO_HEIGHT,           // meters
    DECISION_HEIGHT,        // meters
    LOW_HEIGHT_WARNING,     // boolean
    COM_STBY_FREQUENCY,     // BCD; same as COM_FREQUENCY
    COM_RADIO_25_KHZ_TUNABLE, // Boolean
    NAV_LIGHTS,
    LOGO_LIGHTS,
    WING_LIGHTS,
    RECOGNITION_LIGHTS,
    RADIO_MORSE_IDENT_STATES,
    TURB_ENGINE_1_N1,
    TURB_ENGINE_1_N2,
    TURB_ENGINE_1_CORRECTED_N1,
    TURB_ENGINE_1_CORRECTED_N2,
    TURB_ENGINE_1_CORRECTED_FF,
    TURB_ENGINE_1_PCT_MAX_TORQUE,
    TURB_ENGINE_1_EPR,
    TURB_ENGINE_1_ITT,
    TURB_ENGINE_1_AFTERBURNER,
    TURB_ENGINE_1_JET_THRUST,
    TURB_ENGINE_1_BLEEDAIRPSI,
    TURB_ENGINE_1_TANK_SELECTOR,
    TURB_ENGINE_1_TANKS_USED,
    TURB_ENGINE_1_NUMBER_TANKS,
    TURB_ENGINE_1_FUELFLOW_PPH,
    TURB_ENGINE_1_FUEL_AVAILABLE,
    TURB_ENGINE_1_PCT_AREA,
    TURB_ENGINE_1_PCT_REVERSER,
    TURB_ENGINE_1_VIBRATION,
    TURB_ENGINE_2_N1,
    TURB_ENGINE_2_N2,
    TURB_ENGINE_2_CORRECTED_N1,
    TURB_ENGINE_2_CORRECTED_N2,
    TURB_ENGINE_2_CORRECTED_FF,
    TURB_ENGINE_2_PCT_MAX_TORQUE,
    TURB_ENGINE_2_EPR,
    TURB_ENGINE_2_ITT,
    TURB_ENGINE_2_AFTERBURNER,
    TURB_ENGINE_2_JET_THRUST,
    TURB_ENGINE_2_BLEEDAIRPSI,
    TURB_ENGINE_2_TANK_SELECTOR,
    TURB_ENGINE_2_TANKS_USED,
    TURB_ENGINE_2_NUMBER_TANKS,
    TURB_ENGINE_2_FUELFLOW_PPH,
    TURB_ENGINE_2_FUEL_AVAILABLE,
    TURB_ENGINE_2_PCT_AREA,
    TURB_ENGINE_2_PCT_REVERSER,
    TURB_ENGINE_2_VIBRATION,
    TURB_ENGINE_3_N1,
    TURB_ENGINE_3_N2,
    TURB_ENGINE_3_CORRECTED_N1,
    TURB_ENGINE_3_CORRECTED_N2,
    TURB_ENGINE_3_CORRECTED_FF,
    TURB_ENGINE_3_PCT_MAX_TORQUE,
    TURB_ENGINE_3_EPR,
    TURB_ENGINE_3_ITT,
    TURB_ENGINE_3_AFTERBURNER,
    TURB_ENGINE_3_JET_THRUST,
    TURB_ENGINE_3_BLEEDAIRPSI,
    TURB_ENGINE_3_TANK_SELECTOR,
    TURB_ENGINE_3_TANKS_USED,
    TURB_ENGINE_3_NUMBER_TANKS,
    TURB_ENGINE_3_FUELFLOW_PPH,
    TURB_ENGINE_3_FUEL_AVAILABLE,
    TURB_ENGINE_3_PCT_AREA,
    TURB_ENGINE_3_PCT_REVERSER,
    TURB_ENGINE_3_VIBRATION,
    TURB_ENGINE_4_N1,
    TURB_ENGINE_4_N2,
    TURB_ENGINE_4_CORRECTED_N1,
    TURB_ENGINE_4_CORRECTED_N2,
    TURB_ENGINE_4_CORRECTED_FF,
    TURB_ENGINE_4_PCT_MAX_TORQUE,
    TURB_ENGINE_4_EPR,
    TURB_ENGINE_4_ITT,
    TURB_ENGINE_4_AFTERBURNER,
    TURB_ENGINE_4_JET_THRUST,
    TURB_ENGINE_4_BLEEDAIRPSI,
    TURB_ENGINE_4_TANK_SELECTOR,
    TURB_ENGINE_4_TANKS_USED,
    TURB_ENGINE_4_NUMBER_TANKS,
    TURB_ENGINE_4_FUELFLOW_PPH,
    TURB_ENGINE_4_FUEL_AVAILABLE,
    TURB_ENGINE_4_PCT_AREA,
    TURB_ENGINE_4_PCT_REVERSER,
    TURB_ENGINE_4_VIBRATION,
    PROPELLER_1_RPM,                        // Propeller 1
    PROPELLER_1_PCT_MAX_RPM,
    PROPELLER_1_THRUST,
    PROPELLER_1_BETA,
    PROPELLER_1_FEATHERING_INHIBIT,
    PROPELLER_1_FEATHERED,
    PROPELLER_1_SYNC_DELTA_LEVER,
    PROPELLER_1_AUTOFEATHER_ARMED,
    PROPELLER_2_RPM,                        // Propeller 2
    PROPELLER_2_PCT_MAX_RPM,
    PROPELLER_2_THRUST,
    PROPELLER_2_BETA,
    PROPELLER_2_FEATHERING_INHIBIT,
    PROPELLER_2_FEATHERED,
    PROPELLER_2_SYNC_DELTA_LEVER,
    PROPELLER_2_AUTOFEATHER_ARMED,
    PROPELLER_3_RPM,                        // Propeller 3
    PROPELLER_3_PCT_MAX_RPM,
    PROPELLER_3_THRUST,
    PROPELLER_3_BETA,
    PROPELLER_3_FEATHERING_INHIBIT,
    PROPELLER_3_FEATHERED,
    PROPELLER_3_SYNC_DELTA_LEVER,
    PROPELLER_3_AUTOFEATHER_ARMED,
    PROPELLER_4_RPM,                        // Propeller 4
    PROPELLER_4_PCT_MAX_RPM,
    PROPELLER_4_THRUST,
    PROPELLER_4_BETA,
    PROPELLER_4_FEATHERING_INHIBIT,
    PROPELLER_4_FEATHERED,
    PROPELLER_4_SYNC_DELTA_LEVER,
    PROPELLER_4_AUTOFEATHER_ARMED,
    HYDRAULICS1_PRESSURE_PSF,
    HYDRAULICS1_RESERVOIR_PCT,
    HYDRAULICS2_PRESSURE_PSF,
    HYDRAULICS2_RESERVOIR_PCT,
    HYDRAULICS3_PRESSURE_PSF,
    HYDRAULICS3_RESERVOIR_PCT,
    HYDRAULICS4_PRESSURE_PSF,
    HYDRAULICS4_RESERVOIR_PCT,
    AVIONICS_MASTER_SWITCH,
    PANEL_AUTOFEATHER_SWITCH,               // Panel States
    PANEL_ANTIICE_SWITCH,
    PANEL_AUTOBRAKE_SWITCH,
    DAY_OF_WEEK,            // 0-6
    DAY_OF_MONTH,           // 1-31
    CURRENT_MONTH,          // 1-12
    CURRENT_YEAR,           // 1-????
    TIME_ZONE_OFFSET,       // in minutes, positive west of GMT
    DAYLIGHT_SAVING_ACTIVE, // 0 or 1
    TOTAL_LOAD_AMPS,
    BATTERY_LOAD,
    BATTERY_VOLTAGE,
    MAIN_BUS_VOLTAGE,
    MAIN_BUS_AMPS,
    AVIONICS_BUS_VOLTAGE,
    AVIONICS_BUS_AMPS,
    HOT_BATTERY_BUS_VOLTAGE,
    HOT_BATTERY_BUS_AMPS,
    BATTERY_BUS_VOLTAGE,
    BATTERY_BUS_AMPS,
    GENERATOR_ALTERNATOR_1_BUS_VOLTAGE,
    GENERATOR_ALTERNATOR_1_BUS_AMPS,
    GENERATOR_ALTERNATOR_2_BUS_VOLTAGE,
    GENERATOR_ALTERNATOR_2_BUS_AMPS,
    GENERATOR_ALTERNATOR_3_BUS_VOLTAGE,
    GENERATOR_ALTERNATOR_3_BUS_AMPS,
    GENERATOR_ALTERNATOR_4_BUS_VOLTAGE,
    GENERATOR_ALTERNATOR_4_BUS_AMPS,
    GENERAL_PANEL_CIRCUIT_ON,
    FLAP_MOTOR_CIRCUIT_ON,
    GEAR_MOTOR_CIRCUIT_ON,
    AUTOPILOT_CIRCUIT_ON,
    AVIONICS_CIRCUIT_ON,
    PITOT_HEAT_CIRCUIT_ON,
    PROP_SYNC_CIRCUIT_ON,
    AUTO_FEATHER_CIRCUIT_ON,
    AUTO_BRAKES_CIRCUIT_ON,
    STANDBY_VACUUM_CIRCUIT_ON,
    MARKER_BEACON_CIRCUIT_ON,
    GEAR_WARNING_CIRCUIT_ON,
    HYDRAULIC_PUMP_CIRCUIT_ON,
    ELEVATOR_DEFLECTION,    //  radians
    ELEVATOR_TRIM,          //  radians
    AILERON_DEFLECTION,     //  radians
    AILERON_TRIM,           //  radians
    RUDDER_DEFLECTION,      //  radians
    RUDDER_TRIM,            //  radians
    PROPSYNC_ACTIVE,
    INCIDENCE_ALPHA,
    INCIDENCE_BETA,
    TOTAL_FUEL_QUANTITY_LBS,
    FLIGHT_DIRECTOR_ACTIVE,
    FLIGHT_DIRECTOR_PITCH,      // degrees
    FLIGHT_DIRECTOR_BANK,       // degrees
    CG_PERCENT,
    CG_AFT_LIMIT,
    CG_FWD_LIMIT,
    CG_MAX_MACH,
    CG_MIN_MACH,
    STANDARD_ATM_TEMPERATURE,   // standard atmosphere temperature at aircraft's altitude; celsius
    ENGINE_1_FUELFLOW_BUG_POSITION,     // lbs per hour
    ENGINE_2_FUELFLOW_BUG_POSITION,
    ENGINE_3_FUELFLOW_BUG_POSITION,
    ENGINE_4_FUELFLOW_BUG_POSITION,
    CONCORDE_VISOR_NOSE_HANDLE, // 0 - Visor Up, Nose Up, 1 - Visor Dn, Nose Up, 2 - Visor Dn, Nose 5 deg, 3 - Visor Dn, Nose 12.5 deg
    CONCORDE_VISOR_POS_PCT,     // 0=Up, 1.0 Extended/Down
    CONCORDE_NOSE_ANGLE,        // degrees; 0 - up
    GEAR_POS_TAIL,
    ELEVON_1_DEFLECTION,        // The elevon indices start at 1 at the far left and increase to the right.
    ELEVON_2_DEFLECTION,        // radians
    ELEVON_3_DEFLECTION,
    ELEVON_4_DEFLECTION,
    ELEVON_5_DEFLECTION,
    ELEVON_6_DEFLECTION,
    ELEVON_7_DEFLECTION,
    ELEVON_8_DEFLECTION,
    PANEL_AUTOPILOT_SPEED_SETTING,      // Knots
    AUTOPILOT_AIRSPEED_ACQUISITION,     // boolean
    AUTOPILOT_AIRSPEED_HOLD_CURRENT,    // boolean
    AUTOPILOT_MAX_SPEED,                // boolean
    AUTOPILOT_CRUISE_SPEED,             // boolean
    BARBER_POLE_MACH,                   // real mach
    SELECTED_FUEL_TRANSFER_MODE,        // -1 off, 0 auto, 1 forward, 2 aft
    HYDRAULIC_SYSTEM_INTEGRITY,         // 0.0 - complete failure; 1.0 - everything is ok
    ATTITUDE_CAGE_BUTTON,
    VOR1_NEEDLE_RADIO,                  // +-127 correspond to +-10 if VOR or to +-2.5 if localiser. Driven always by VOR
    GPS_POSITION_LAT,
    GPS_POSITION_LON,
    GPS_POSITION_ALT,
    GPS_MAGVAR,                         // magnetic deviation (radians)
    GPS_FLAGS,                          // GPS_FLAG_ACTIVE_FLIGHT_PLAN = 0x00002    there is an active flight plan
                                        // GPS_FLAG_ACTIVE_WAY_POINT   = 0x00004    there is an active way point
                                        // GPS_FLAG_ARRIVED            = 0x00008    last waypoint reached
                                        // GPS_FLAG_DIRECTTO_FLIGHTPLAN= 0x00020    manual flight plan
    GPS_GROUND_SPEED,                   // meters per second
    GPS_GROUND_HEADING,                 // radians (0 - 2PI); true heading, yaw
    GPS_GROUND_TRACK,                   // radians (0 - 2PI); heading + magvar, magnetic yaw
    GPS_WP_DISTANCE,                    // meters to next wp
    GPS_WP_BEARING,                     // heading (radians) to next wp + magvar
    GPS_WP_CROSS_TRK,                   // cross_trk (meters)
    GPS_WP_REQ_HDG,                     // required heading, magnetic, radians (0 - 2PI), from prev wp to next wp
    GPS_WP_STRING,                      // name of next waypoint
    GPS_WP_NEXT_LAT,
    GPS_WP_NEXT_LON,
    GPS_WP_NEXT_ALT,
    GPS_WP_PREV_LAT,
    GPS_WP_PREV_LON,
    GPS_WP_PREV_ALT,
    GPS_WP_TRUE_BEARING,                // true bearing, degrees
    GPS_WP_TRUE_REQ_HDG,                // true required heading, degrees
    GPS_DRIVES_NAV1,
    HSI_VERTICAL_NEEDLE,                // -1.0 .. 1.0 corresponds to -10deg .. 10deg if VOR or to -2.5deg .. +2.5deg if localiser +5NM .. -5NM  if GPS
    HSI_HORIZONTAL_NEEDLE,              // -1.0 .. 1.0 corresponds to -0.7deg .. +0.7deg
    HSI_VERTICAL_VALID,                 // 0 - Nav flag on
    HSI_HORIZONTAL_VALID,               // 0 - GS flag on
    HSI_TF_FLAG,                        // -1.0 - from. 0.0 - none, 1.0 - to
    HSI_OBI_NEEDLE,                     // 0 .. 360
    HSI_DESIRED_HEADING_NEEDLE,         // 0 .. 360
    HSI_BEARING,                        // 0 .. 360
    HSI_BEARING_VALID,                  // 1 - true
    HSI_SIGNAL_LOCALISER,               // 1 - true
    HSI_SPEED,                          // knots
    HSI_DISTANCE,                       // NM
    HSI_STATION_NAME,                   // string
    GEAR_POS_AUX,                       //      Aux gear    0 - 16k
    TOOLTIP_UNITS,                      // enum TOOLTIP_UNITS_TYPE
    LSO_TEXTURE_ID,                     // current LSO texture id
    LSO_TEXT,                           // text
    LEFT_FOLDING_WING_PERCENT,          // 0 - not folded; 1 - folded
    RIGHT_FOLDING_WING_PERCENT,         // 0 - not folded; 1 - folded
    MAIN_EXIT_OPEN,                     // 0 - not open; 1 - open
    TAILHOOK_POSITION,                    // 0 - retracted; 1 - extended
    COM2_FREQUENCY,                     // BCD same as COM_FREQUENCY
    COM2_STBY_FREQUENCY,                // BCD; same as COM_FREQUENCY
    NAV1_STBY_FREQUENCY,                // BCD NAV1 radio freq; same as NAV1_FREQUENCY
    NAV2_STBY_FREQUENCY,                // BCD NAV2 radio freq; same as NAV2_FREQUENCY
    COM1_TRANSMIT_SELECT,               // 1.0 - yes
    COM2_TRANSMIT_SELECT,               // 1.0 - yes
    COM_BOTH_RECEIVE,                   // 1.0 - yes
    NAV1_SOUND_TOGGLE,
    NAV2_SOUND_TOGGLE,
    DME_SOUND_TOGGLE,
    ADF_SOUND_TOGGLE,
    MARKER_SOUND_TOGGLE,
    VOR2_GS_NEEDLE,
    GENERAL_ENGINE1_ANTI_ICE_POS,       //0 - off 1 - on
    GENERAL_ENGINE2_ANTI_ICE_POS,       //0 - off 1 - on
    GENERAL_ENGINE3_ANTI_ICE_POS,       //0 - off 1 - on
    GENERAL_ENGINE4_ANTI_ICE_POS,       //0 - off 1 - on
    ENGINE1_ON_FIRE,                    // 0 - no, 1 - yes
    ENGINE2_ON_FIRE,
    ENGINE3_ON_FIRE,
    ENGINE4_ON_FIRE,
    ENGINE1_FUEL_PUMP_ON,               // 0 - no, 1 - yes
    ENGINE2_FUEL_PUMP_ON,               // 0 - no, 1 - yes
    ENGINE3_FUEL_PUMP_ON,               // 0 - no, 1 - yes
    ENGINE4_FUEL_PUMP_ON,               // 0 - no, 1 - yes
    GENERAL_ENGINE1_FUEL_VALVE,         //1 = Open, 0 = Closed
    GENERAL_ENGINE2_FUEL_VALVE,         //1 = Open, 0 = Closed
    GENERAL_ENGINE3_FUEL_VALVE,         //1 = Open, 0 = Closed
    GENERAL_ENGINE4_FUEL_VALVE,         //1 = Open, 0 = Closed
    GENERAL_ENGINE1_FUEL_PRESSURE,
    GENERAL_ENGINE2_FUEL_PRESSURE,
    GENERAL_ENGINE3_FUEL_PRESSURE,
    GENERAL_ENGINE4_FUEL_PRESSURE,
    WATER_RUDDER_ON,                    // 0 - up, 1 - down
    PROP_DEICE_SWITCH,                  // 0 = off, 1 = on
    STRUCTURAL_DEICE_SWITCH,            // 0 = off, 1 = on
    FUEL_TANK_SELECTOR_2,               //  see FUEL_TANK_SELECTOR_ enum values
    TRAILING_EDGE_FLAPS0_LEFT_ANGLE,    // Angle of primary trailing edge flaps
    TRAILING_EDGE_FLAPS0_RIGHT_ANGLE,   // Angle of primary trailing edge flaps


    ALTERNATE_STATIC_AIR_OPEN,                  // Alternate static air source

    AILERON_TRIM_PCT,                           // percent -1 to 1
    RUDDER_TRIM_PCT,                            // percent -1 to 1

    LIGHT_NAV_ON,
    LIGHT_BEACON_ON,
    LIGHT_LANDING_ON,
    LIGHT_TAXI_ON,
    LIGHT_STROBE_ON,
    LIGHT_PANEL_ON,
    LIGHT_RECOGNITION_ON,
    LIGHT_WING_ON,
    LIGHT_LOGO_ON,
    LIGHT_CABIN_ON,

    TOTAL_VELOCITY,
    TOTAL_WORLD_VELOCITY,

    VARIOMETER_RATE,
    VARIOMETER_SWITCH,

    RELATIVE_WIND_VELOCITY_BODY_X,
    RELATIVE_WIND_VELOCITY_BODY_Y,
    RELATIVE_WIND_VELOCITY_BODY_Z,
    ACCELERATION_WORLD_X,
    ACCELERATION_WORLD_Y,
    ACCELERATION_WORLD_Z,
    ACCELERATION_BODY_X,
    ACCELERATION_BODY_Y,
    ACCELERATION_BODY_Z,

    PLANE_ALT_ABOVE_GROUND,
    MAGNETIC_COMPASS,
    TURN_INDICATOR_RATE,
    TURN_INDICATOR_SWITCH,
    BRAKE_DEPENDENT_HYDRAULIC_PRESSURE,

    FLY_BY_WIRE_ELAC_SWITCH,
    FLY_BY_WIRE_FAC_SWITCH,
    FLY_BY_WIRE_SEC_SWITCH,
    FLY_BY_WIRE_ELAC_FAILED,
    FLY_BY_WIRE_FAC_FAILED,
    FLY_BY_WIRE_SEC_FAILED,

    GEAR_EMERGENCY_HANDLE_POSITION,
    GEAR_WARNING,
    TAILWHEEL_LOCK_ON,
    ANTISKID_BRAKES_ACTIVE,
    RETRACT_FLOAT_SWITCH,
    STEER_INPUT_CONTROL,

    STALL_ALPHA,
    EXIT_OPEN,
    DECISION_ALTITUDE_MSL,
    WATER_BALLAST_VALVE,
    AUTOPILOT_RPM_HOLD,
    AUTOPILOT_PITCH_HOLD_REF,
    AUTOPILOT_MAX_BANK,
    PROP_FEATHER_SWITCH,
    MASTER_IGNITION_SWITCH,
    BLEED_AIR_SOURCE_CONTROL,
    STRUCTURAL_ICE_PCT,

    ROTOR_BRAKE_HANDLE_POS,
    ROTOR_BRAKE_ACTIVE,
    ROTOR_CLUTCH_SWITCH_POS,
    ROTOR_CLUTCH_ACTIVE,
    ROTOR_GOV_SWITCH_POS,
    ROTOR_GOV_ACTIVE,
    ROTOR_LATERAL_TRIM_PCT,
    DISK_PITCH_ANGLE,
    DISK_BANK_ANGLE,
    DISK_PITCH_PCT,
    DISK_BANK_PCT,

    TOW_RELEASE_HANDLE,
    APU_PCT_RPM,
    APU_PCT_STARTER,
    APU_VOLTS,
    APU_GENERATOR_SWITCH,
    APU_GENERATOR_ACTIVE,
    APU_ON_FIRE_DETECTED,

    PRESSURIZATION_CABIN_ALTITUDE,
    PRESSURIZATION_CABIN_ALTITUDE_GOAL,
    PRESSURIZATION_CABIN_ALTITUDE_RATE,
    PRESSURIZATION_PRESSURE_DIFFERENTIAL,
    PRESSURIZATION_DUMP_SWITCH,

    FIRE_BOTTLE_SWITCH,
    FIRE_BOTTLE_DISCHARGED,

    CABIN_NO_SMOKING_ALERT_SWITCH,
    CABIN_SEATBELTS_ALERT_SWITCH,

    GPWS_WARNING,
    GPWS_SYSTEM_ACTIVE,

    IS_LATITUDE_LONGITUDE_FREEZE_ON,
    IS_ALTITUDE_FREEZE_ON,

    NOSEWHEEL_LOCK_ON,
    PAYLOAD_STATION_NUM_SIMOBJECTS,
    FOLDING_WING_HANDLE_POSITION,
    TAILHOOK_HANDLE,
    LAUNCHBAR_POSITION,
    LAUNCHBAR_SWITCH,
    LAUNCHBAR_HELD_EXTENDED,
    AUTOPILOT_PITCH_HOLD,
    NUMBER_OF_CATAPULTS,
    HOLDBACK_BAR_INSTALLED,
    BLAST_SHIELD_POSITION,
    CATAPULT_STROKE_POSITION,
    RECIP_ENG_DETONATING,
    RECIP_ENG_CYLINDER_HEALTH,
    RECIP_ENG_NUM_CYLINDERS,
    RECIP_ENG_NUM_CYLINDERS_FAILED,
    RECIP_ENG_ANTIDETONATION_TANK_VALVE,
    RECIP_ENG_ANTIDETONATION_TANK_QUANTITY,
    RECIP_ENG_ANTIDETONATION_TANK_MAX_QUANTITY,
    RECIP_ENG_NITROUS_TANK_VALVE,
    RECIP_ENG_NITROUS_TANK_QUANTITY,
    RECIP_ENG_NITROUS_TANK_MAX_QUANTITY,
    TURB_ENG_AFTERBURNER_STAGE_ACTIVE,
    TURB_ENG_AFTERBURNER_PCT_ACTIVE,
    FUEL_DUMP_SWITCH,
    FUEL_DUMP_ACTIVE,
    COLLECTIVE_POSITION,

    IS_ATTITUDE_FREEZE_ON,

    NUM_SLING_CABLES,
    SLING_OBJECT_ATTACHED,
    SLING_CABLE_BROKEN,
    SLING_CABLE_EXTENDED_LENGTH,
    SLING_ACTIVE_PAYLOAD_STATION,
    SLING_HOIST_PERCENT_DEPLOYED,
    SLING_HOIST_SWITCH,
    SLING_HOOK_IN_PICKUP_MODE,

    CABLE_CAUGHT_BY_TAILHOOK,
    IS_POSITION_FREEZE_ON,

    C_GAUGE_TOKEN                       // Always the last

} GAUGE_TOKEN;

typedef enum    VAR_TYPE {
    VAR_TYPE_NONE,

    TYPE_BOOL8,
    TYPE_UINT8,
    TYPE_SINT8,
    TYPE_FLAGS8,
    TYPE_ENUM8,

    TYPE_BOOL16,
    TYPE_ANGL16,
    TYPE_UINT16,
    TYPE_SINT16,
    TYPE_UIF16,
    TYPE_SIF16,
    TYPE_FLAGS16,
    TYPE_ENUM16,
    TYPE_BCD16,
    TYPE_BCO16,
    TYPE_VAR16,

    TYPE_BOOL32,
    TYPE_ANGL32,
    TYPE_UINT32,
    TYPE_SINT32,
    TYPE_UIF32,
    TYPE_SIF32,
    TYPE_FLAGS32,
    TYPE_ENUM32,
    TYPE_VAR32,

    TYPE_ANGL48,
    TYPE_SINT48,
    TYPE_UIF48,
    TYPE_SIF48,

    TYPE_UINT64,
    TYPE_SINT64,
    TYPE_SIF64,
    TYPE_FLOAT64,

    TYPE_BOOL,
    TYPE_FLAGS,
    TYPE_ENUM,

    TYPE_VOID,
    TYPE_PVOID,

    TYPE_PUINT32,
    TYPE_PSINT32,
    TYPE_PFLOAT64,

    VAR_TYPE_MAX
} VAR_TYPE;


// Panel identifiers
#define IDENT_MAIN_PANEL                         0
#define IDENT_MAIN_PANEL_ALT1                    1
#define IDENT_MAIN_PANEL_ALT2                    2
#define IDENT_MAIN_PANEL_ALT3                    3
#define IDENT_MAIN_PANEL_ALT4                    4
#define IDENT_MAIN_PANEL_ALT5                    5
#define IDENT_MAIN_PANEL_ALT6                    6
#define IDENT_MAIN_PANEL_ALT7                    7
#define IDENT_MAIN_PANEL_ALT8                    8
#define IDENT_MAIN_PANEL_ALT9                    9
#define IDENT_THROTTLE_PANEL                    10
#define IDENT_RADIO_STACK_PANEL                 50
#define IDENT_COMPASS_PANEL                     75
#define IDENT_MINI_CONTROLS_PANEL               100
#define IDENT_ANNUNCIATOR_PANEL                 125
#define IDENT_ANNUNCIATOR2_PANEL                150
#define IDENT_IFR_MAIN_PANEL                    175
#define IDENT_COLLECTIVE_PANEL                  200
#define IDENT_GPS_PANEL                         225
#define IDENT_OVERHEAD_PANEL                    250
#define IDENT_PARKING_BRAKE_PANEL               251
#define IDENT_FLAPS_TRIM_PANEL                  252
#define IDENT_FUEL_PANEL                        253
#define IDENT_ELECTRICAL_PANEL                  254
#define IDENT_TRIM_PANEL                        255
#define IDENT_LANDING_GEAR_PANEL                256
#define IDENT_WEAPONS_GAUGE                     257
#define IDENT_MISC_POPUP_1                      260
#define IDENT_MISC_POPUP_2                      261
#define IDENT_MISC_POPUP_3                      262
#define IDENT_MISC_POPUP_4                      263
#define IDENT_MISC_POPUP_5                      264
#define IDENT_MISC_POPUP_6                      265
#define IDENT_MISC_POPUP_7                      266
#define IDENT_MISC_POPUP_8                      267
#define IDENT_MISC_POPUP_9                      268
#define IDENT_MISC_POPUP_10                     269


#define IDENT_USER                              10000
#define IDENT_USER_MAX                          19999

#define MIN_HUD_IDENT                           20000
#define IDENT_AIRCRAFT_HUD_3D_PANEL             20000
#define IDENT_HELICOPTER_HUD_3D_PANEL           20001
#define IDENT_CONTROLS_HUD_3D_PANEL             20002
#define IDENT_TEXT_HUD_3D_PANEL                 20003
#define IDENT_DAMAGE_HUD_3D_PANEL               20004
#define IDENT_SCORE_HUD_3D_PANEL                20005
#define MAX_HUD_IDENT                           20006
#define IDENT_TEST_PANEL                        21000
#define IDENT_LSO_WINDOW                        22000

#define IDENT_LSO_WINDOW                        22000

// scenario windows are in this special range
#define IDENT_FIRST_SCENARIO_WINDOW             22001
#define IDENT_POI_WINDOW                        IDENT_FIRST_SCENARIO_WINDOW
#define IDENT_TIMER_WINDOW                      (IDENT_FIRST_SCENARIO_WINDOW + 1)
#define IDENT_DROPPABLE_OBJ_WINDOW              (IDENT_FIRST_SCENARIO_WINDOW + 2)
#define IDENT_RACEMAP_WINDOW                    (IDENT_FIRST_SCENARIO_WINDOW + 3)
#define IDENT_RACEINFO_WINDOW                   (IDENT_FIRST_SCENARIO_WINDOW + 4)
#define IDENT_G_METER_WINDOW                    (IDENT_FIRST_SCENARIO_WINDOW + 5)
#define IDENT_RACEPENALTY_WINDOW                (IDENT_FIRST_SCENARIO_WINDOW + 6)
#define IDENT_COUNTDOWN_WINDOW                  (IDENT_FIRST_SCENARIO_WINDOW + 7)
#define IDENT_MENU_WINDOW                       (IDENT_FIRST_SCENARIO_WINDOW + 8)
#define IDENT_ATC_WINDOW                        (IDENT_FIRST_SCENARIO_WINDOW + 9)
#define IDENT_SIMCONNECT_WINDOW                 (IDENT_FIRST_SCENARIO_WINDOW + 10)
#define IDENT_PANEL_MANAGER                     (IDENT_FIRST_SCENARIO_WINDOW + 11)
#define IDENT_APP_MENU_WINDOW                   (IDENT_FIRST_SCENARIO_WINDOW + 12)
#define IDENT_EYE_TRACKING_WINDOW               (IDENT_FIRST_SCENARIO_WINDOW + 13)
#define IDENT_MESSAGE_WINDOW                    (IDENT_FIRST_SCENARIO_WINDOW + 14)
#define IDENT_INFOGEN_WINDOW_DEPRECATED         (IDENT_FIRST_SCENARIO_WINDOW + 15) // Unused, kept here to prevent black screen issue from original 5.2 infogen panel
#define IDENT_DEV_MENU                          (IDENT_FIRST_SCENARIO_WINDOW + 16)
#define IDENT_INFOGEN_WINDOW                    (IDENT_FIRST_SCENARIO_WINDOW + 17)
#define IDENT_INSPECTOR_VIEW                    (IDENT_FIRST_SCENARIO_WINDOW + 18)
#define IDENT_RACEMANEUVER_WINDOW               (IDENT_FIRST_SCENARIO_WINDOW + 19)

#define IDENT_LAST_SCENARIO_WINDOW              (IDENT_FIRST_SCENARIO_WINDOW + 19)

// UIPanel windows use dynamically created ids
#define IDENT_UI_PANEL_WINDOW        30000
#define IDENT_SCALEFORM_PANEL_WINDOW IDENT_UI_PANEL_WINDOW // deprecated, kept for back compat

// dynamically generated IDs for duplicated panels
#define IDENT_DUPLICATE_PANEL                   40000

#define IDENT_INVALID                           4294967295

// HUD settings
#define HUD_ON                          0x1
#define HUD_METRIC                      0x2


// PANEL STATES
//
#define PS_MAIN_PANEL_VISIBLE           BIT1
#define PS_MAIN_PANEL_COMPOSED          BIT2
#define PS_PADLOCK_SERVER               BIT3            // not used yet
#define PS_PADLOCK_CLIENT               BIT4            // not used yet
#define PS_HELICOPTER_HUD_VISIBLE       BIT5
#define PS_AIRCRAFT_HUD_VISIBLE         BIT6
#define PS_AIRCRAFT_HUD_ON              BIT7
#define PS_RADIO_STACK_VISIBLE          BIT8
#define PS_HUD_METRIC_OUTPUT            BIT9
#define PS_MAIN_PANEL_ON                BIT10
#define PS_CONTROLS_HUD_VISIBLE         BIT11
#define PS_RADIO_STACK_AUTOPOPED        BIT12
#define PS_MAIN_PANEL_UNDOCKED          BIT13
#define PS_AIRCRAFT_HUD_EXIST           BIT14
#define PS_HELICOPTER_HUD_EXIST         BIT15
#define PS_HUD_EXIST                    (PS_AIRCRAFT_HUD_EXIST|PS_HELICOPTER_HUD_EXIST)
#define PS_PANELS_LOAD_VISIBLE          BIT16
#define PS_HUD_LOAD_VISIBLE             BIT17
#define PS_PANEL_VISIBLE                BIT18
#define PS_HUD_PANEL_VISIBLE            BIT19
#define PS_READONLY                      (~(PS_PADLOCK_SERVER|PS_PADLOCK_CLIENT|PS_HUD_METRIC_OUTPUT))

#define PS_SET                                          0xFFFFFFFF
#define PS_CLEAR                                        0x00000000

#define GAUGE_FLAG_NORMAL               0
#define GAUGE_FLAG_HIDDEN               0x1
#define GAUGE_FLAG_BLINKING             0x2
#define GAUGE_FLAG_GRAYED               0x4
#define GAUGE_FLAG_HILIGHTED            0x8

#define UNITS_UNKNOWN                   (-1)
#define UNITS_STRING                    (-2)
#define UNITS_LONG                      (-3)
#define UNITS_NUMBER                    UNITS_LONG
#define UNITS_WSTRING                   (-4)

#define INVALID_GAUGE_ID                0


enum PANEL_TYPE
{
    PANEL_TYPE_PLAIN,               //  Radio Stack
    PANEL_TYPE_HUD,                 //  Aircraft HUD
    PANEL_TYPE_SPECIAL,             //  LSO
    PANEL_TYPE_TEXTURE,             //  Virtual Cockpit Texture
    PANEL_TYPE_MISSION,             //  Context-specific (i.e. displayed during certain missions)
    PANEL_TYPE_SCENARIO = PANEL_TYPE_MISSION,   // Same as PANEL_TYPE_MISSION, new naming convention
    PANEL_TYPE_UI,
};

// Seqsel Selection stuff
#define SELECT_NONE                             0
#define SELECT_1                                1
#define SELECT_ZOOM                             2
#define SELECT_MAGNETO                          3
#define SELECT_COM_WHOLE                        4
#define SELECT_COM_FRACTION                     5
#define SELECT_NAV1_WHOLE                       6
#define SELECT_NAV1_FRACTION                    7
#define SELECT_NAV2_WHOLE                       8
#define SELECT_NAV2_FRACTION                    9
#define SELECT_XPNDR_1000                       10
#define SELECT_XPNDR_0100                       11
#define SELECT_XPNDR_0010                       12
#define SELECT_XPNDR_0001                       13
#define SELECT_VOR1                             14
#define SELECT_VOR2                             15
#define SELECT_ENGINE                           16
#define SELECT_DME1                             17
#define SELECT_DME2                             18
#define SELECT_ADF_100                          19
#define SELECT_ADF_010                          20
#define SELECT_ADF_001                          21
#define SELECT_EGT_BUG                          22
#define SELECT_SIM_RATE                         23
#define SELECT_CLOCK_HOURS                      24
#define SELECT_CLOCK_MINUTES                    25
#define SELECT_CLOCK_SECONDS                    26
#define SELECT_COM2_WHOLE                       27
#define SELECT_COM2_FRACTION                    28
#define SELECT_ADF_TENTHS                       29

// used for the image_flags field
#define         IMAGE_USE_TRANSPARENCY                  BIT0    // these don't change dynamically and are set
#define         IMAGE_USE_ERASE                         BIT1
#define         IMAGE_USE_BRIGHT                        BIT2
#define         IMAGE_ERASE_ON_FAILURE                  BIT3    // not used now
#define         IMAGE_NO_STATIC_BLENDING                BIT4    // not used now
#define         IMAGE_CREATE_DIBSECTION                 BIT5
#define         IMAGE_BILINEAR_GRAY                     BIT6
#define         IMAGE_BILINEAR_COLOR                    BIT7
#define         IMAGE_PRESERVE_COLOR_IN_HUD             BIT8
#define         IMAGE_CONTAINS_NO_MASK                  BIT9

#define         IMAGE_SPRITE_FORCE_TRANS                BIT10   // not used now
#define         IMAGE_BLT_MASK_ONLY                     BIT11

#define         IMAGE_CONTAINS_MASK                     BIT12   // Image contains mask bits
#define         IMAGE_USE_ALPHA                         BIT13   // Image contains alpha channel
#define         IMAGE_USE_LUMINOUS                      BIT14   // Image is bright when the interior light is on
#define         IMAGE_USE_LUMINOUS_PARTIAL              BIT15       // Parts of image are lit by interior light (alpha channel)
#define         IMAGE_ERASE_ALWAYS                      BIT16

#define         IMAGE_DRAW_IN_GRAY                      BIT23   // draw this image in gray as it was covered
#define         IMAGE_DRAWN_IN_GRAY                     BIT24   // this image was drawn in gray
#define         IMAGE_HIDDEN_TREE                       BIT25
#define         IMAGE_NO_STRETCH                        BIT27   // these change dynamically
#define         IMAGE_HUD_COLOR_MAP                     BIT28
#define         IMAGE_NO_TRANSLATION                    BIT29
#define         IMAGE_HIDDEN                            BIT30
#define         IMAGE_ON_SCREEN                         BIT31


#define         GET_IMAGE_HIDDEN(element)                       (element->image_flags & IMAGE_HIDDEN)
#define         SHOW_IMAGE(element)                             (element->image_flags &= ~IMAGE_HIDDEN)
#define         HIDE_IMAGE(element)                             (element->image_flags |= IMAGE_HIDDEN)

#define         GET_IMAGE_HIDDEN_TREE(element)                  (element->image_flags & IMAGE_HIDDEN_TREE)
#define         SHOW_IMAGE_TREE(element)                        (element->image_flags &= ~IMAGE_HIDDEN_TREE)
#define         HIDE_IMAGE_TREE(element)                        (element->image_flags |= IMAGE_HIDDEN_TREE)

#define         GET_USE_TRANSPARENCY( element )                 (element->image_flags & IMAGE_USE_TRANSPARENCY)
#define         GET_USE_ERASE( element )                        (element->image_flags & IMAGE_USE_ERASE)
#define         GET_USE_BRIGHT( element )                       (element->image_flags & IMAGE_USE_BRIGHT)
#define         GET_ERASE_ON_FAILURE( element )                 (element->image_flags & IMAGE_ERASE_ON_FAILURE)

#define         GET_ON_SCREEN( element )                        (element->image_flags & IMAGE_ON_SCREEN)
#define         SET_ON_SCREEN( element )                        (element->image_flags |= IMAGE_ON_SCREEN)
#define         SET_OFF_SCREEN( element )                       (element->image_flags &= ~IMAGE_ON_SCREEN)


#define         GET_FAILED( element )                           (element->image_flags & GAUGE_FAILURE)
#define         SET_GAUGE_FAILED( element)                      (element->image_flags |= GAUGE_FAILURE)
#define         SET_GAUGE_NOT_FAILED( element)                  (element->image_flags &= ~GAUGE_FAILURE)

#define         GET_IMAGE_ERASE_ALWAYS( element )               (element->image_flags &   IMAGE_ERASE_ALWAYS)

typedef enum    FAILURE_KEY
{
    FAIL_NONE = 0,

    OLD_FAIL_SYSTEM_ELECTRICAL,         // obsolete: dont use it in new gauges; use FAIL_SYSTEM_ELECTRICAL_PANELS
    FAIL_SYSTEM_ENGINE,
    FAIL_SYSTEM_PITOT_STATIC,
    FAIL_SYSTEM_VACUUM,

    FAIL_GAUGE_ADF,
    FAIL_GAUGE_AIRSPEED,
    FAIL_GAUGE_ALTIMETER,
    FAIL_GAUGE_ATTITUDE,
    FAIL_GAUGE_COMMUNICATIONS,              // Used for COM1
    FAIL_GAUGE_FUEL_INDICATORS,
    FAIL_GAUGE_GYRO_HEADING,
    FAIL_GAUGE_MAGNETIC_COMPASS,
    OLD_FAIL_GAUGE_NAVIGATION,              // OBSOLETE: DON'T USE
    FAIL_GAUGE_NAVIGATION_VOR1,             // only vor1
    FAIL_GAUGE_NAVIGATION_VOR2,             // only vor2
    OLD_FAIL_GAUGE_NAVIGATION_BOTH,         // OBSOLETE: DON'T USE
    FAIL_GAUGE_TRANSPONDER,
    FAIL_GAUGE_TURN_COORDINATOR,
    FAIL_GAUGE_VERTICAL_SPEED,

    FAIL_SYSTEM_ELECTRICAL_PANELS,
    FAIL_SYSTEM_ELECTRICAL_AVIONICS,

    FAIL_GAUGE_COMMUNICATIONS_COM2,        // Used for COM2


    FAIL_KEY_MAX
}
FAILURE_KEY, *PFAILURE_KEY, **PPFAILURE_KEY;

typedef enum    FAILURE_ACTION
{
    FAIL_ACTION_NONE = 0,
    FAIL_ACTION_FREEZE,
    FAIL_ACTION_ZERO,
    FAIL_ACTION_NO_DRAW,
    FAIL_ACTION_COVER,

    FAIL_ACTION_MAX
}
FAILURE_ACTION, *PFAILURE_ACTION, **PPFAILURE_ACTION;

#define PANEL_SERVICE_PRE_QUERY                         0
#define PANEL_SERVICE_POST_QUERY                        1
#define PANEL_SERVICE_PRE_INSTALL                       2       // extra_data = resource_handle
#define PANEL_SERVICE_POST_INSTALL                      3       // extra_data = resource_handle
#define PANEL_SERVICE_PRE_INITIALIZE                    4
#define PANEL_SERVICE_POST_INITIALIZE                   5
#define PANEL_SERVICE_PRE_UPDATE                        6
#define PANEL_SERVICE_POST_UPDATE                       7
#define PANEL_SERVICE_PRE_GENERATE                      8       // extra_data = phase
#define PANEL_SERVICE_POST_GENERATE                     9       // extra_data = phase
#define PANEL_SERVICE_PRE_DRAW                          10
#define PANEL_SERVICE_POST_DRAW                         11
#define PANEL_SERVICE_PRE_KILL                          12
#define PANEL_SERVICE_POST_KILL                         13
#define PANEL_SERVICE_CONNECT_TO_WINDOW                 14      // extra_data = PANEL_WND
#define PANEL_SERVICE_DISCONNECT                        15      // extra_data = PANEL_WND
#define PANEL_SERVICE_PANEL_OPEN                        16
#define PANEL_SERVICE_PANEL_CLOSE                       17


#define GAUGE_HEADER_VERSION_FS610                      610    // FS 6.10 gauges
#define GAUGE_HEADER_VERSION_FSNEW                      625    // OLD style gauges compiled in the FS70 TREE
#define GAUGE_HEADER_VERSION                            GAUGE_HEADER_VERSION_FSNEW                    
#define GAUGE_HEADER_VERSION_CFS1                       650    // CFS1 Gauges
#define GAUGE_HEADER_VERSION_SPITFIRE                   GAUGE_HEADER_VERSION_CFS1
#define GAUGE_HEADER_VERSION_FS700                      700    // new FS7 gauges built after CFS1 is finalized
#define GAUGE_HEADER_VERSION_CFS2                       750    // gauges built after FS2000 shipped and before CFS2 shipped
#define GAUGE_HEADER_VERSION_FS800                      800    // FS2002 gauges
#define GAUGE_HEADER_VERSION_FS900                      900    // FS2004 gauges
#define GAUGE_HEADER_VERSION_FS1000                     1000   // FSX gauges

#pragma pack(pop)

#endif // _GAUGES_DEFINES_H_
