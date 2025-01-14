//Parts of this code uses Lockheed Martin Prepar3D SDK sample
//Copyright (c) 2010-2019 Lockheed Martin Corporation. All rights reserved.
//Use of this file is bound by the PREPAR3D® SOFTWARE DEVELOPER KIT END USER LICENSE AGREEMENT

#include "pch.h"

#include "Gauge.h"
#include "GreenHydraulics.h"
#include "BlueHydraulics.h"
#include "YellowHydraulics.h"



//Define globals - these need to be shared with SimConnect
bool green_hyd_pump_switch;
bool blue_hyd_pump_switch;
bool yellow_hyd_pump_switch;

bool green_hyd_fluid_leak_switch;
bool blue_hyd_fluid_leak_switch;
bool yellow_hyd_fluid_leak_switch;

bool green_hyd_pump_fail_switch;
bool blue_hyd_pump_fail_switch;
bool yellow_hyd_pump_fail_switch;

bool landing_gear_switch;
bool flight_controls_switch;
bool brake_switch;

FLOAT64 green_hyd_pressure;
FLOAT64 green_hyd_fluid;
FLOAT64 blue_hyd_pressure;
FLOAT64 blue_hyd_fluid;
FLOAT64 yellow_hyd_pressure;
FLOAT64 yellow_hyd_fluid;


//State of system holds - these are the current states of the modes (not switch position)
bool green_hyd_pump_state; 
bool blue_hyd_pump_state;
bool yellow_hyd_pump_state;

bool green_hyd_fluid_leak_state;
bool blue_hyd_fluid_leak_state;
bool yellow_hyd_fluid_leak_state;

bool green_hyd_pump_fail_state;
bool blue_hyd_pump_fail_state;
bool yellow_hyd_pump_fail_state;

bool landing_gear_state;
bool flight_controls_state;
bool brake_state;


std::unique_ptr<GreenHydraulics> greenHydraulicSystem;
std::unique_ptr<BlueHydraulics> blueHydraulicSystem;
std::unique_ptr<YellowHydraulics> yellowHydraulicSystem;

bool SetSwitchEvent(bool switch_in, bool hold_state, EVENT_ID switch_event)
{
	//Define a new hold state
	bool new_hold_state = hold_state;

	//Set the SimConnect event only when the mode is changed
	if (switch_in == true)
	{
		if (!hold_state)
		{
			new_hold_state = true;
			SendHydraulicsGaugeMode(switch_event);
		}
	}
	//switch OFF
	else
	{
		if (hold_state)
		{
			new_hold_state = false;
			SendHydraulicsGaugeMode(switch_event);
		}
	}
	return new_hold_state;
}


//----------------------------------------------------------------------------
//START BOILERPLATE C++ GAUGE CALLBACKS - DO NOT MODIFY. TAKEN FROM P3D SDK 
//"MIXED MODE GAUGE" EXAMPLE
//----------------------------------------------------------------------------
GAUGE_CALLBACK gauge_callback;
//Note: The items in the property table correspond to the indices that
//will be returned in the Get/Set Property functions
struct PROPERTY_TABLE
{
	PCSTRINGZ szPropertyName;
	PCSTRINGZ szUnitsName;
	ENUM units;
};

//
//PanelCallback is an abstract base class that can be overridden.  Implementors
//should override the functions CreateAircraftCallback() as
//well as GetPropertyTable.
class PanelCallback : public IPanelCCallback
{
	DECLARE_PANEL_CALLBACK_REFCOUNT(PanelCallback);

public:
	PanelCallback();

	//******* IPanelCCallback Methods *****************    
	IPanelCCallback * QueryInterface(PCSTRINGZ pszInterface);
	UINT32 GetVersion();
	bool ConvertStringToProperty(PCSTRINGZ keyword, SINT32 * pID);
	bool ConvertPropertyToString(SINT32 id, PPCSTRINGZ pKeyword);
	bool GetPropertyUnits(SINT32 id, ENUM * pEnum);

protected:
	//******** PanelCallback Methods ******************
	virtual const PROPERTY_TABLE * GetPropertyTable(UINT & uLength) = 0;
};

//
//AircraftCallback is an abstract base class that can be overridden.  Implementors
//should override the function CreateGaugeCCallback(UINT32 ContainerId)
class AircraftCallback : public IAircraftCCallback
{
	DECLARE_PANEL_CALLBACK_REFCOUNT(AircraftCallback);
public:
	AircraftCallback(UINT32 containerId);

	//******* IAircraftCCallback Methods ************* 
	IAircraftCCallback * QueryInterface(PCSTRINGZ pszInterface);
	void Update();

protected:
	UINT32 GetContainerId() const;

private:
	UINT32 m_containerId;
};
//End of paneldefs.h
DEFINE_PANEL_CALLBACK_REFCOUNT(PanelCallback);

PanelCallback::PanelCallback()
	: m_RefCount(1)
{
}

IPanelCCallback * PanelCallback::QueryInterface(PCSTRINGZ pszInterface)
{
	return NULL;
}

UINT32 PanelCallback::GetVersion()
{
	return 1;
}

bool PanelCallback::ConvertStringToProperty(PCSTRINGZ keyword, SINT32 * pID)
{
	if (!keyword)
	{
		return false;
	}
	if (!pID)
	{
		return false;
	}

	UINT uNumProperties;
	const PROPERTY_TABLE * parPropertyTable = GetPropertyTable(uNumProperties);

	for (UINT i = 0; i < uNumProperties; i++)
	{
		if (_stricmp(parPropertyTable[i].szPropertyName, keyword) == 0)
		{
			*pID = i;
			return true;
		}
	}
	return false;
}

bool PanelCallback::ConvertPropertyToString(SINT32 id, PPCSTRINGZ pKeyword)
{
	if (!pKeyword)
	{
		return false;
	}

	UINT uNumProperties;
	const PROPERTY_TABLE * parPropertyTable = GetPropertyTable(uNumProperties);

	if (id < 0 || id >= (SINT32)uNumProperties)
	{
		return false;
	}
	*pKeyword = parPropertyTable[id].szPropertyName;
	return true;
}

bool PanelCallback::GetPropertyUnits(SINT32 id, ENUM * pEnum)
{
	if (!pEnum)
	{
		return false;
	}

	UINT uNumProperties;
	const PROPERTY_TABLE * parPropertyTable = GetPropertyTable(uNumProperties);

	if (id < 0 || id >= (SINT32)uNumProperties)
	{
		return false;
	}

	*pEnum = parPropertyTable[id].units;
	return true;
}

DEFINE_PANEL_CALLBACK_REFCOUNT(AircraftCallback);

AircraftCallback::AircraftCallback(UINT32 containerId)
	: m_containerId(containerId),
	m_RefCount(1)
{
}

IAircraftCCallback * AircraftCallback::QueryInterface(PCSTRINGZ pszInterface)
{
	return NULL;
}

void AircraftCallback::Update()
{
}

UINT32 AircraftCallback::GetContainerId() const
{
	return m_containerId;
}
//----------------------------------------------------------------------------
//STOP BOILERPLATE C++ GAUGE CALLBACKS - DO NOT MODIFY. TAKEN FROM P3D SDK 
//"MIXED MODE GAUGE" EXAMPLE
//----------------------------------------------------------------------------

static const char AH_CALLBACK_NAME[] = "Airbus-Hydraulics";

//PROPERTY TABLE array that contains the properties of the variables defined in the XML file
static PROPERTY_TABLE AH_PROPERTY_TABLE[] =
{
	{"GreenHYDPressure", "PSI", UNITS_NUMBER},
	{"BlueHYDPressure", "PSI", UNITS_NUMBER},
	{"YellowHYDPressure", "PSI", UNITS_NUMBER},
	{"GreenHYDFluidLevel", "Percent", UNITS_NUMBER},
	{"BlueHYDFluidLevel", "Percent", UNITS_NUMBER},
	{"YellowHYDFluidLevel", "Percent", UNITS_NUMBER},
	{"GreenHYDEnableSwitch", "Bool", UNITS_UNKNOWN},
	{"BlueHYDEnableSwitch", "Bool", UNITS_UNKNOWN},
	{"YellowHYDEnableSwitch", "Bool", UNITS_UNKNOWN},
	{"GreenHYDFluidLeakSwitch", "Bool", UNITS_UNKNOWN},
	{"BlueHYDFluidLeakSwitch", "Bool", UNITS_UNKNOWN},
	{"YellowHYDFluidLeakSwitch", "Bool", UNITS_UNKNOWN},
	{"GreenHYDPumpFailSwitch", "Bool", UNITS_UNKNOWN},
	{"BlueHYDPumpFailSwitch", "Bool", UNITS_UNKNOWN},
	{"YellowHYDPumpFailSwitch", "Bool", UNITS_UNKNOWN},
	{"LGStatusLamp", "Bool", UNITS_UNKNOWN},
	{"FlightControlsStatusLamp", "Bool", UNITS_UNKNOWN},
	{"BrakeStatusLamp", "Bool", UNITS_UNKNOWN}
};

//Enum that contains the properties 
enum AH_VAR
{
	AH_GREEN_HYDRAULIC_PRESSURE,
	AH_BLUE_HYDRAULIC_PRESSURE,
	AH_YELLOW_HYDRAULIC_PRESSURE,
	AH_GREEN_HYDRAULIC_FLUID,
	AH_BLUE_HYDRAULIC_FLUID,
	AH_YELLOW_HYDRAULIC_FLUID,
	AH_GREEN_HYDRAULIC_PUMP_ACTIVE,
	AH_BLUE_HYDRAULIC_PUMP_ACTIVE,
	AH_YELLOW_HYDRAULIC_PUMP_ACTIVE,
	AH_GREEN_HYDRAULIC_FLUID_LEAK,
	AH_BLUE_HYDRAULIC_FLUID_LEAK,
	AH_YELLOW_HYDRAULIC_FLUID_LEAK,
	AH_GREEN_HYDRAULIC_PUMP_FAILURE,
	AH_BLUE_HYDRAULIC_PUMP_FAILURE,
	AH_YELLOW_HYDRAULIC_PUMP_FAILURE,
	AH_LANDING_GEAR_STATUS,
	AH_FLIGHT_CONTROLS_STATUS,
	AH_BRAKE_STATUS
};

class AHGaugeCallback : public IGaugeCCallback
{
	DECLARE_PANEL_CALLBACK_REFCOUNT(AHGaugeCallback);

public:
	AHGaugeCallback(UINT32 containerId);

	//************* IGaugeCCallback Methods ***************
	IGaugeCCallback * QueryInterface(PCSTRINGZ pszInterface);
	void Update();
	bool GetPropertyValue(SINT32 id, FLOAT64 * pValue);
	bool GetPropertyValue(SINT32 id, LPCSTR * pszValue);
	bool GetPropertyValue(SINT32 id, LPCWSTR * pszValue);
	bool SetPropertyValue(SINT32 id, FLOAT64 value);
	bool SetPropertyValue(SINT32 id, LPCSTR szValue);
	bool SetPropertyValue(SINT32 id, LPCWSTR szValue);
	IGaugeCDrawable * CreateGaugeCDrawable(SINT32 id, const IGaugeCDrawableCreateParameters * pParameters);

	/*
	* GETTER FUNCTIONS
	* Gauge return functions (GET) - these get called during the 18Hz polling to update the gauge values
	*/

	/* Get Green HYD pump switch
	* Calls SetSwitchEvent() to invoke SimConnect EVENT_GREEN_HYDRAULICS_PUMP_TOGGLE
	@return [bool] Yellow HYD pump switch
	*/
	bool get_green_hyd_pump_switch()
	{
		green_hyd_pump_state = SetSwitchEvent(green_hyd_pump_switch, green_hyd_pump_state, EVENT_GREEN_HYDRAULICS_PUMP_TOGGLE);

		return green_hyd_pump_switch;
	}

	/* Get Blue HYD pump switch
	* Calls SetSwitchEvent() to invoke SimConnect EVENT_BLUE_HYDRAULICS_PUMP_TOGGLE
	@return [bool] Yellow HYD pump switch
	*/
	bool get_blue_hyd_pump_switch()
	{
		blue_hyd_pump_state = SetSwitchEvent(blue_hyd_pump_switch, blue_hyd_pump_state, EVENT_BLUE_HYDRAULICS_PUMP_TOGGLE);

		return blue_hyd_pump_switch;
	}

	/* Get Yellow HYD pump switch.
	* Calls SetSwitchEvent() to invoke SimConnect EVENT_YELLOW_HYDRAULICS_PUMP_TOGGLE
	@return [bool] Yellow HYD pump switch
	*/
	bool get_yellow_hyd_pump_switch()
	{
		yellow_hyd_pump_state = SetSwitchEvent(yellow_hyd_pump_switch, yellow_hyd_pump_state, EVENT_YELLOW_HYDRAULICS_PUMP_TOGGLE);

		return yellow_hyd_pump_switch;
	}

	/* Get Green HYD Pressure
	@return [double] Green HYD pressure (PSI)
	*/
	double get_green_hyd_pressure()
	{
		return greenHydraulicSystem->getPressure();
	}

	/* Get Green HYD fluid amount in percent
	@return [double] Green HYD fluid amount in 2 decimals (%)
	*/
	double get_green_hyd_fluid()
	{
		return greenHydraulicSystem->getFluid();
	}

	/* Get Blue HYD Pressure
	@return [double] Blue HYD pressure (PSI)
	*/
	double get_blue_hyd_pressure()
	{
		return blueHydraulicSystem->getPressure();
	}

	/* Get Blue HYD fluid amount in percent
	@return [double] Blue HYD fluid amount in 2 decimals (%)
	*/
	double get_blue_hyd_fluid()
	{
		return blueHydraulicSystem->getFluid();
	}

	/* Get Yellow HYD Pressure
	@return [double] Yellow HYD pressure (PSI)
	*/
	double get_yellow_hyd_pressure()
	{
		return yellowHydraulicSystem->getPressure();
	}


	/* Get Yellow HYD fluid amount in percent
	@return [double] Yellow HYD fluid amount in 2 decimals (%)
	*/
	double get_yellow_hyd_fluid()
	{
		return yellowHydraulicSystem->getFluid();
	}

	/* Get Green HYD fluid leak fail status.
	* Calls SetSwitchEvent() to update status and invoke SimConnect EVENT_GREEN_HYDRAULICS_FLUID_LEAK_TOGGLE if switch has been clicked
	@return [bool] green_hyd_fluid_leak_switch : true if pump fail switch has been pressed and state is on
	*/
	bool get_green_hyd_fluid_leak_switch()
	{
		green_hyd_fluid_leak_state = SetSwitchEvent(green_hyd_fluid_leak_switch, green_hyd_fluid_leak_state, EVENT_GREEN_HYDRAULICS_FLUID_LEAK_TOGGLE);

		return green_hyd_fluid_leak_switch;
	}

	/* Get Blue HYD fluid leak fail status.
	* Calls SetSwitchEvent() to update status and invoke SimConnect EVENT_BLUE_HYDRAULICS_FLUID_LEAK_TOGGLE if switch has been clicked
	@return [bool] blue_hyd_fluid_leak_switch : true if pump fail switch has been pressed and state is on
	*/
	bool get_blue_hyd_fluid_leak_switch()
	{
		blue_hyd_fluid_leak_state = SetSwitchEvent(blue_hyd_fluid_leak_switch, blue_hyd_fluid_leak_state, EVENT_BLUE_HYDRAULICS_FLUID_LEAK_TOGGLE);

		return blue_hyd_fluid_leak_switch;
	}

	/* Get Yellow HYD fluid leak fail status.
	* Calls SetSwitchEvent() to update status and invoke SimConnect EVENT_YELLOW_HYDRAULICS_FLUID_LEAK_TOGGLE if switch has been clicked
	@return [bool] yellow_hyd_fluid_leak_switch : true if pump fail switch has been pressed and state is on
	*/
	bool get_yellow_hyd_fluid_leak_switch()
	{
		yellow_hyd_fluid_leak_state = SetSwitchEvent(yellow_hyd_fluid_leak_switch, yellow_hyd_fluid_leak_state, EVENT_YELLOW_HYDRAULICS_FLUID_LEAK_TOGGLE);

		return yellow_hyd_fluid_leak_switch;
	}

	/* Get Green HYD pump fail status.
	* Calls SetSwitchEvent() to update status and invoke SimConnect EVENT_GREEN_HYDRAULICS_PUMP_FAIL_TOGGLE if switch has been clicked
	@return [bool] green_hyd_pump_fail_state : true if pump fail switch has been pressed and state is on
	*/
	bool get_green_hyd_pump_fail_switch()
	{
		green_hyd_pump_fail_state = SetSwitchEvent(green_hyd_pump_fail_switch, green_hyd_pump_fail_state, EVENT_GREEN_HYDRAULICS_PUMP_FAIL_TOGGLE);

		return green_hyd_pump_fail_switch;
	}

	/* Get Blue HYD pump fail status.
	* Calls SetSwitchEvent() to update status and invoke SimConnect EVENT_BLUE_HYDRAULICS_PUMP_FAIL_TOGGLE if switch has been clicked
	@return [bool] blue_hyd_pump_fail_switch : true if pump fail switch has been pressed and state is on
	*/
	bool get_blue_hyd_pump_fail_switch()
	{
		blue_hyd_pump_fail_state = SetSwitchEvent(blue_hyd_pump_fail_switch, blue_hyd_pump_fail_state, EVENT_BLUE_HYDRAULICS_PUMP_FAIL_TOGGLE);

		return blue_hyd_pump_fail_switch;
	}

	/* Get Yellow HYD pump fail status.
	* Calls SetSwitchEvent() to update status and invoke SimConnect EVENT_YELLOW_HYDRAULICS_PUMP_FAIL_TOGGLE if switch has been clicked
	@return [bool] yellow_hyd_pump_fail_switch : true if pump fail switch has been pressed and state is on
	*/
	bool get_yellow_hyd_pump_fail_switch()
	{
		yellow_hyd_pump_fail_state = SetSwitchEvent(yellow_hyd_pump_fail_switch, yellow_hyd_pump_fail_state, EVENT_YELLOW_HYDRAULICS_PUMP_FAIL_TOGGLE);

		return yellow_hyd_pump_fail_switch;
	}

	// NOT A SWITCH - NAME KEPT AS SWITCH FOR CONVENTION
	/* Get the Landing Gear switch value to set the panel
	@return [bool] landing_gear_switch : true if Green HYD pressure >= 2800
	*/
	bool get_landing_gear_switch()
	{
		if (greenHydraulicSystem->getPressure() >= 2800)
		{
			landing_gear_switch = true;
		}
		else
		{
			landing_gear_switch = false;
		}

 		return landing_gear_switch;
	}

	// NOT A SWITCH - NAME KEPT AS SWITCH FOR CONVENTION
	/* Get the Flight Control Status switch value to set the panel.
	* Calls SetSwitchEvent() to update status and invoke necessary ENABLE/DISABLE FLIGHT CONTROL event based on system pressures.
	@return [bool] flight_controls_switch : true if any of the systems have more than 1000 PSI
	*/
	bool get_flight_controls_switch()
	{
		if (!(greenHydraulicSystem->getPressure() > 1000 || blueHydraulicSystem->getPressure() > 1000 || yellowHydraulicSystem->getPressure() > 1000))
		{
			flight_controls_switch = false;
			flight_controls_state = SetSwitchEvent(flight_controls_switch, flight_controls_state, EVENT_DISABLE_FLIGHT_CONTROLS);
		}
		else
		{
			flight_controls_switch = true;
			flight_controls_state = SetSwitchEvent(flight_controls_switch, flight_controls_state, EVENT_ENABLE_FLIGHT_CONTROLS);
		}

		return flight_controls_switch;
	}

	// NOT A SWITCH - NAME KEPT AS SWITCH FOR CONVENTION
	/* Get the Brake Status switch value to set the panel.
	* Calls SetSwitchEvent() to update status and invoke necessary ENABLE/DISABLE BRAKES event based on system pressures.
	@return [bool] brake_switch : true if green system has more than 1000 PSI and has more then 5% fluid
	*/
	bool get_brake_switch()
	{
		if (!(greenHydraulicSystem->getPressure() > 1000 && greenHydraulicSystem->getFluid() > 5))
		{
			brake_switch = false;
			brake_state = SetSwitchEvent(brake_switch, brake_state, EVENT_DISABLE_BRAKES);
		}
		else
		{
			brake_switch = true;
			brake_state = SetSwitchEvent(brake_switch, brake_state, EVENT_ENABLE_BRAKES);
		}

		return brake_switch;
	}

	/*
	* SETTER FUNCTIONS
	* Gauge assignment functions (SET) - these are called when updated
	*/
	//Set Green HYD pump switch
	void set_green_hyd_pump_switch(bool switch_state)
	{
		if (!greenHydraulicSystem->getIsPumpFailed())
		{
			green_hyd_pump_switch = switch_state;
		}
	}

	//Set Blue HYD pump switch
	void set_blue_hyd_pump_switch(bool switch_state)
	{
		if (!blueHydraulicSystem->getIsPumpFailed())
		{
			blue_hyd_pump_switch = switch_state;
		}
	}

	//Set Yellow HYD pump switch
	void set_yellow_hyd_pump_switch(bool switch_state)
	{
		if (!yellowHydraulicSystem->getIsPumpFailed())
		{
			yellow_hyd_pump_switch = switch_state;
		}
	}

	//Set Green HYD pressure
	void set_green_hyd_pressure(double value)
	{
		if (greenHydraulicSystem->getPressure() < 2800)
		{
			landing_gear_switch = false;
		}

		green_hyd_pressure = value;
	}

	//Set Green HYD fluid amount in percent
	void set_green_hyd_fluid(double value)
	{
		green_hyd_fluid = value;
	}

	//Set Blue HYD pressure
	void set_blue_hyd_pressure(double value)
	{
		blue_hyd_pressure = value;
	}

	//Set Blue HYD fluid amount in percent
	void set_blue_hyd_fluid(double value)
	{
		blue_hyd_fluid = value;
	}

	//Set Yellow HYD pressure
	void set_yellow_hyd_pressure(double value)
	{
		yellow_hyd_pressure = value;
	}

	//Set Yellow HYD HYD fluid amount in percent
	void set_yellow_hyd_fluid(double value)
	{
		yellow_hyd_fluid = value;
	}

	//Set Green HYD fluid leak fail status
	void set_green_hyd_fluid_leak_switch(bool switch_state)
	{
		green_hyd_fluid_leak_switch = switch_state;
	}

	//Set Blue HYD fluid leak fail status
	void set_blue_hyd_fluid_leak_switch(bool switch_state)
	{
		blue_hyd_fluid_leak_switch = switch_state;
	}

	//Set Yellow HYD fluid leak fail status
	void set_yellow_hyd_fluid_leak_switch(bool switch_state)
	{
		yellow_hyd_fluid_leak_switch = switch_state;
	}

	//Set Green HYD pump fail status
	void set_green_hyd_pump_fail_switch(bool switch_state)
	{
		if (switch_state == true)
		{
			green_hyd_pump_switch = false;
		}

		green_hyd_pump_fail_switch = switch_state;
	}

	//Set Blue HYD pump fail status
	void set_blue_hyd_pump_fail_switch(bool switch_state)
	{
		if (switch_state == true)
		{ 
			blue_hyd_pump_switch = false;
		}

		blue_hyd_pump_fail_switch = switch_state;
	}

	//Set Yellow HYD pump fail status
	void set_yellow_hyd_pump_fail_switch(bool switch_state)
	{
 		if (switch_state == true)
		{
			yellow_hyd_pump_switch = false;
		}

		yellow_hyd_pump_fail_switch = switch_state;
	}

	//Set landing gear status
	void set_landing_gear_switch(bool switch_state)
	{
		if (greenHydraulicSystem->getPressure() >= 2800)
		{
			landing_gear_switch = true;
		}
		else
		{
			landing_gear_switch = false;
		}
	}

	//Set flight control engagement status
	void set_flight_controls_switch(bool switch_state)
	{
		if (!(greenHydraulicSystem->getPressure() > 1000 || blueHydraulicSystem->getPressure() > 10000 || yellowHydraulicSystem->getPressure() > 1000))
		{
			flight_controls_switch = false;
		}
		else
		{
			flight_controls_switch = true;
		}
	}

	//Set brake status
	void set_brake_switch(bool switch_state)
	{
		if (!(greenHydraulicSystem->getPressure() > 1000 || greenHydraulicSystem->getFluid() > 5))
		{
			brake_switch = false;
		}
		else
		{
			brake_switch = true;
		}
	}

private:
	UINT32 m_containerId;
};


DEFINE_PANEL_CALLBACK_REFCOUNT(AHGaugeCallback)

AHGaugeCallback::AHGaugeCallback(UINT32 containerId)
	: m_RefCount(1),
	m_containerId(containerId)
{
	//Set initial states
	green_hyd_pump_switch = greenHydraulicSystem->getIsPumpActive();
	blue_hyd_pump_switch = blueHydraulicSystem->getIsPumpActive();
	yellow_hyd_pump_switch = yellowHydraulicSystem->getIsPumpActive();
	green_hyd_fluid_leak_switch = greenHydraulicSystem->getIsLeaking();
	blue_hyd_fluid_leak_switch = blueHydraulicSystem->getIsLeaking();
	yellow_hyd_fluid_leak_switch = yellowHydraulicSystem->getIsLeaking();
	green_hyd_pump_fail_switch = greenHydraulicSystem->getIsPumpFailed();
	blue_hyd_pump_fail_switch = blueHydraulicSystem->getIsPumpFailed();
	yellow_hyd_pump_fail_switch = yellowHydraulicSystem->getIsPumpFailed();
	landing_gear_switch = true;
	flight_controls_switch = true;
	brake_switch = true;

	green_hyd_pressure = greenHydraulicSystem->getPressure();
	green_hyd_fluid = greenHydraulicSystem->getFluid();
	blue_hyd_pressure = blueHydraulicSystem->getPressure();
	blue_hyd_fluid = blueHydraulicSystem->getFluid();
	yellow_hyd_pressure = yellowHydraulicSystem->getPressure();
	yellow_hyd_fluid = yellowHydraulicSystem->getFluid();
}
IGaugeCCallback * AHGaugeCallback::QueryInterface(PCSTRINGZ pszInterface)
{
	return NULL;
}
//
//The Update functions is called on a 18Hz cycle
//
void AHGaugeCallback::Update()
{
	unsigned int	random;
}
//
//Getting float/numeric values
//
bool AHGaugeCallback::GetPropertyValue(SINT32 id, FLOAT64 * pValue)
{
	if (!pValue)
	{
		return false;
	}

	*pValue = 1.0;      //Start with a reasonable default (by the SDK?)

	AH_VAR eAPVar = (AH_VAR)id;

	switch (eAPVar)
	{
		case AH_GREEN_HYDRAULIC_PUMP_ACTIVE:
			*pValue = get_green_hyd_pump_switch();
			break;
		case AH_BLUE_HYDRAULIC_PUMP_ACTIVE:
			*pValue = get_blue_hyd_pump_switch();
			break;
		case AH_YELLOW_HYDRAULIC_PUMP_ACTIVE:
			*pValue = get_yellow_hyd_pump_switch();
			break;
		case AH_GREEN_HYDRAULIC_PRESSURE:
			*pValue = get_green_hyd_pressure();
			break;
		case AH_GREEN_HYDRAULIC_FLUID:
			*pValue = get_green_hyd_fluid();
			break;
		case AH_BLUE_HYDRAULIC_PRESSURE:
			*pValue = get_blue_hyd_pressure();
			break;
		case AH_BLUE_HYDRAULIC_FLUID:
			*pValue = get_blue_hyd_fluid();
			break;
		case AH_YELLOW_HYDRAULIC_PRESSURE:
			*pValue = get_yellow_hyd_pressure();
			break;
		case AH_YELLOW_HYDRAULIC_FLUID:
			*pValue = get_yellow_hyd_fluid();
			break;
		case AH_GREEN_HYDRAULIC_FLUID_LEAK:
			*pValue = get_green_hyd_fluid_leak_switch();
			break;
		case AH_BLUE_HYDRAULIC_FLUID_LEAK:
			*pValue = get_blue_hyd_fluid_leak_switch();
			break;
		case AH_YELLOW_HYDRAULIC_FLUID_LEAK:
			*pValue = get_yellow_hyd_fluid_leak_switch();
			break;
		case AH_GREEN_HYDRAULIC_PUMP_FAILURE:
			*pValue = get_green_hyd_pump_fail_switch();
			break;
		case AH_BLUE_HYDRAULIC_PUMP_FAILURE:
			*pValue = get_blue_hyd_pump_fail_switch();
			break;
		case AH_YELLOW_HYDRAULIC_PUMP_FAILURE:
			*pValue = get_yellow_hyd_pump_fail_switch();
			break;
		case AH_LANDING_GEAR_STATUS:
			*pValue = get_landing_gear_switch();
			break;
		case AH_FLIGHT_CONTROLS_STATUS:
			*pValue = get_flight_controls_switch();
			break;
		case AH_BRAKE_STATUS:
			*pValue = get_brake_switch();
			break;
		default:
			return false;
	}
	return true;
}
//
//Getting string property values (N/A BUT LEAVE SCAFFOLING IN CASE YOU WANT TO ADD A REGULAR STRING)
//
bool AHGaugeCallback::GetPropertyValue(SINT32 id, LPCSTR * pszValue)
{
	return false;
}


bool AHGaugeCallback::GetPropertyValue(SINT32 id, LPCWSTR * pszValue)
{
	if (!pszValue)
	{
		return false;
	}

	*pszValue = TEXT("null");     //Return a reasonable default

	AH_VAR eAPVar = (AH_VAR)id;

	switch (eAPVar)
	{
		default:
			return false;
	}
	return true;
}
//
//Setting float/numeric values
//
bool AHGaugeCallback::SetPropertyValue(SINT32 id, FLOAT64 value)
{
	AH_VAR eAPVar = (AH_VAR)id;

	switch (eAPVar)
	{
		case AH_GREEN_HYDRAULIC_PRESSURE:
			set_green_hyd_pressure(greenHydraulicSystem->getPressure());
			break;
		case AH_BLUE_HYDRAULIC_PRESSURE:
			set_blue_hyd_pressure(blueHydraulicSystem->getPressure());
			break;
		case AH_YELLOW_HYDRAULIC_PRESSURE:
			set_yellow_hyd_pressure(yellowHydraulicSystem->getPressure());
			break;
		case AH_GREEN_HYDRAULIC_FLUID:
			set_green_hyd_fluid(greenHydraulicSystem->getFluid());
			break;
		case AH_BLUE_HYDRAULIC_FLUID:
			set_blue_hyd_fluid(blueHydraulicSystem->getFluid());
			break;
		case AH_YELLOW_HYDRAULIC_FLUID:
			set_yellow_hyd_fluid(yellowHydraulicSystem->getFluid());
			break;
		case AH_GREEN_HYDRAULIC_PUMP_ACTIVE:
			set_green_hyd_pump_switch(static_cast<bool>(value));
			break;
		case AH_BLUE_HYDRAULIC_PUMP_ACTIVE:
			set_blue_hyd_pump_switch(static_cast<bool>(value));
			break;
		case AH_YELLOW_HYDRAULIC_PUMP_ACTIVE:
			set_yellow_hyd_pump_switch(static_cast<bool>(value));
			break;
		case AH_GREEN_HYDRAULIC_FLUID_LEAK:
			set_green_hyd_fluid_leak_switch(static_cast<bool>(value));
			break;
		case AH_BLUE_HYDRAULIC_FLUID_LEAK:
			set_blue_hyd_fluid_leak_switch(static_cast<bool>(value));
			break;
		case AH_YELLOW_HYDRAULIC_FLUID_LEAK:
			set_yellow_hyd_fluid_leak_switch(static_cast<bool>(value));
			break;
		case AH_GREEN_HYDRAULIC_PUMP_FAILURE:
			set_green_hyd_pump_fail_switch(static_cast<bool>(value));
			break;
		case AH_BLUE_HYDRAULIC_PUMP_FAILURE:
			set_blue_hyd_pump_fail_switch(static_cast<bool>(value));
			break;
		case AH_YELLOW_HYDRAULIC_PUMP_FAILURE:
			set_yellow_hyd_pump_fail_switch(static_cast<bool>(value));
			break;
		case AH_LANDING_GEAR_STATUS:
			set_landing_gear_switch(static_cast<bool>(value));
			break;
		case AH_FLIGHT_CONTROLS_STATUS:
			set_flight_controls_switch(static_cast<bool>(value));
			break;
		case AH_BRAKE_STATUS:
			set_brake_switch(static_cast<bool>(value));
			break;
		default:
			return false;
	}
	return true;
}

//
//Setting string values
//
bool AHGaugeCallback::SetPropertyValue(SINT32 id, LPCSTR szValue)
{
	return false;   //String properties not permitted to be set
}
bool AHGaugeCallback::SetPropertyValue(SINT32 id, LPCWSTR szValue)
{
	AH_VAR eAPVar = (AH_VAR)id;

	switch (eAPVar)
	{

	}

	return false;   //String properties not permitted to be set
}

IGaugeCDrawable * AHGaugeCallback::CreateGaugeCDrawable(SINT32 id, const IGaugeCDrawableCreateParameters * pParameters)
{
	return NULL;	//No implementation of this necessary
}

//
//AircraftCallback Override
//
class AHAircraftCallback : public AircraftCallback
{
private:

public:
	AHAircraftCallback(UINT32 ContainerID) : AircraftCallback(ContainerID)
	{
	}
	IGaugeCCallback * CreateGaugeCCallback()
	{
		return new AHGaugeCallback(GetContainerId());
	}
};

//
//PanelCallback Override
//

class AHPanelCallback : public PanelCallback
{
public:

	AHPanelCallback()

	{
		//init property table
		for (int n = 0; n < LENGTHOF(AH_PROPERTY_TABLE); n++)
		{
			if (ImportTable.PANELSentry.fnptr != NULL &&
				AH_PROPERTY_TABLE[n].units == UNITS_UNKNOWN)
			{
				AH_PROPERTY_TABLE[n].units = get_units_enum(AH_PROPERTY_TABLE[n].szUnitsName);
			}
		}
	}

	IAircraftCCallback * CreateAircraftCCallback(UINT32 ContainerID)
	{
		return new AHAircraftCallback(ContainerID);
	}


protected:
	const PROPERTY_TABLE * GetPropertyTable(UINT & uLength)
	{
		uLength = LENGTHOF(AH_PROPERTY_TABLE);
		return AH_PROPERTY_TABLE;
	}
};

void AHPanelCallbackInit()
{

	AHPanelCallback * pPanelCallback = new AHPanelCallback();

	if (pPanelCallback)
	{
		bool b = panel_register_c_callback(AH_CALLBACK_NAME, pPanelCallback);
		pPanelCallback->Release();
	}
}

void AHPanelCallbackDeInit()
{
	panel_register_c_callback(AH_CALLBACK_NAME, NULL);
}

//The Panels pointer will get filled in during the loading process
//if this DLL is listed in DLL.XML

PPANELS Panels = NULL;

GAUGESIMPORT    ImportTable =
{
	{ 0x0000000F, (PPANELS)NULL },
	{ 0x00000000, NULL }
};



void FSAPI module_init(void)
{
	//instantiate hydraulic systems
	greenHydraulicSystem = std::make_unique<GreenHydraulics>();
	blueHydraulicSystem = std::make_unique<BlueHydraulics>();
	yellowHydraulicSystem = std::make_unique<YellowHydraulics>();

	//initialize state variables based on the systems themselves
	green_hyd_pump_state = greenHydraulicSystem->getIsPumpActive();
	blue_hyd_pump_state = blueHydraulicSystem->getIsPumpActive();
	yellow_hyd_pump_state = yellowHydraulicSystem->getIsPumpActive();

	green_hyd_fluid_leak_state = greenHydraulicSystem->getIsLeaking();
	blue_hyd_fluid_leak_state = blueHydraulicSystem->getIsLeaking();
	yellow_hyd_fluid_leak_state = yellowHydraulicSystem->getIsLeaking();

	green_hyd_pump_fail_state = greenHydraulicSystem->getIsPumpFailed();
	blue_hyd_pump_fail_state = blueHydraulicSystem->getIsPumpFailed();
	yellow_hyd_pump_fail_state = yellowHydraulicSystem->getIsPumpFailed();

	landing_gear_state = true;
	flight_controls_state = true;
	brake_state = true;

	if (NULL != Panels)
	{
		ImportTable.PANELSentry.fnptr = (PPANELS)Panels;
		AHPanelCallbackInit();
	}

	OpenSimConnect();
}

void FSAPI module_deinit(void)
{
	greenHydraulicSystem.reset();
	blueHydraulicSystem.reset();
	yellowHydraulicSystem.reset();

	AHPanelCallbackDeInit();

	CloseSimConnect();
}

BOOL WINAPI DllMain(HINSTANCE hDLL, DWORD dwReason, LPVOID lpReserved)
{
	return TRUE;
}

//This is the module's export table.
GAUGESLINKAGE   Linkage =
{
	0x00000013,
	module_init,
	module_deinit,
	0,
	0,

	FS9LINK_VERSION, { 0 }
};

