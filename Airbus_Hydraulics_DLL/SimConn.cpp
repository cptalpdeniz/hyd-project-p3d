#include "pch.h"

#include "SimConn.h"
#include "Gauge.h"

//SimConnect initializers
int     quit = 0;
HANDLE  hAirbusHydraulicsGauge = NULL;

void SendHydraulicsGaugeMode(EVENT_ID switch_event)
{
	SimConnect_TransmitClientEvent(hAirbusHydraulicsGauge, 0, switch_event, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
}

double unsignedToInt(uint32_t uint)
{
	if (uint <= INT_MAX)
	{
		return static_cast<int>(uint);
	}

	if (uint >= INT_MIN)
	{
		return (static_cast<int>(uint - INT_MIN) + INT_MIN);
	}
}

double calculatePercentage(double receivedData)
{
	return ((unsignedToInt((uint32_t)receivedData) + 16383.00) / 32766.00) * 100;
}

/*The main SimConnect callback loop*/
void CALLBACK DispatchProcedure(SIMCONNECT_RECV* pData, DWORD cbData, void* pContext)
{
	//HRESULT hr;

	switch (pData->dwID)
	{
		case SIMCONNECT_RECV_ID_EVENT:
		{
			SIMCONNECT_RECV_EVENT* evt = (SIMCONNECT_RECV_EVENT*)pData;

			switch (evt->uEventID)
			{
				case EVENT_GREEN_HYDRAULICS_PUMP_TOGGLE:
				{
					if (green_hyd_pump_state == true)
					{
						greenHydraulicSystem->startRegulator();
					}
					else
					{
						greenHydraulicSystem->stopRegulator();
					}

					break;
				}
				case EVENT_BLUE_HYDRAULICS_PUMP_TOGGLE:
				{
					if (blue_hyd_pump_state == true)
					{
						blueHydraulicSystem->startRegulator();
					}
					else
					{
						blueHydraulicSystem->stopRegulator();
					}

					break;
				}
				case EVENT_YELLOW_HYDRAULICS_PUMP_TOGGLE:
				{
					if (yellow_hyd_pump_state == true)
					{
						yellowHydraulicSystem->startRegulator();
					}
					else
					{
						yellowHydraulicSystem->stopRegulator();
					}

					break;
				}
				case EVENT_GREEN_HYDRAULICS_FLUID_LEAK_TOGGLE:
				{
					if (green_hyd_fluid_leak_state == true)
					{
						greenHydraulicSystem->simulateLeak();
					}
					else
					{
						greenHydraulicSystem->setFluid(100.0);
						greenHydraulicSystem->stopLeak();
					}

					break;
				}
				case EVENT_BLUE_HYDRAULICS_FLUID_LEAK_TOGGLE:
				{
					if (blue_hyd_fluid_leak_state == true)
					{
						blueHydraulicSystem->simulateLeak();
					}
					else
					{
						blueHydraulicSystem->setFluid(100.0);
						blueHydraulicSystem->stopLeak();
					}

					break;
				}
				case EVENT_YELLOW_HYDRAULICS_FLUID_LEAK_TOGGLE:
				{
					if (yellow_hyd_fluid_leak_state == true)
					{
						yellowHydraulicSystem->simulateLeak();
					}
					else
					{
						yellowHydraulicSystem->setFluid(100.0);
						yellowHydraulicSystem->stopLeak();
					}

					break;
				}
				case EVENT_GREEN_HYDRAULICS_PUMP_FAIL_TOGGLE:
				{
					if (green_hyd_pump_fail_state == true)
					{
						greenHydraulicSystem->simulatePumpFail();
					}
					else
					{
						greenHydraulicSystem->stopPumpFail();
					}

					break;
				}
				case EVENT_BLUE_HYDRAULICS_PUMP_FAIL_TOGGLE:
				{
					if (blue_hyd_pump_fail_state == true)
					{
						blueHydraulicSystem->simulatePumpFail();
					}
					else
					{
						blueHydraulicSystem->stopPumpFail();
					}

					break;

				}
				case EVENT_YELLOW_HYDRAULICS_PUMP_FAIL_TOGGLE:
				{
					if (yellow_hyd_pump_fail_state == true)
					{
						yellowHydraulicSystem->simulatePumpFail();
					}
					else
					{
						yellowHydraulicSystem->stopPumpFail();
					}

					break;
				}

				case EVENT_DISABLE_FLIGHT_CONTROLS:
				{
 					SimConnect_RemoveClientEvent(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_AXIS_RUDDER_SET);
					SimConnect_RemoveClientEvent(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_AXIS_ELEVATOR_SET);
					SimConnect_RemoveClientEvent(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_AXIS_AILERONS_SET);

					SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST_MASKABLE, EVENT_AXIS_RUDDER_SET, true);
					SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST_MASKABLE, EVENT_AXIS_ELEVATOR_SET, true);
					SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST_MASKABLE, EVENT_AXIS_AILERONS_SET, true);

				case EVENT_GEAR_TOGGLE:
				{
					SimConnect_RequestDataOnSimObject(hAirbusHydraulicsGauge, REQUEST_LANDING_GEAR, DEF_GEAR_POSITION, SIMCONNECT_SIMOBJECT_TYPE_USER, SIMCONNECT_PERIOD_ONCE);
					break;
				}

				case EVENT_ENABLE_FLIGHT_CONTROLS:
				{
					SimConnect_RemoveClientEvent(hAirbusHydraulicsGauge, GROUP_HIGHEST_MASKABLE, EVENT_AXIS_RUDDER_SET);
					SimConnect_RemoveClientEvent(hAirbusHydraulicsGauge, GROUP_HIGHEST_MASKABLE, EVENT_AXIS_ELEVATOR_SET);
					SimConnect_RemoveClientEvent(hAirbusHydraulicsGauge, GROUP_HIGHEST_MASKABLE, EVENT_AXIS_AILERONS_SET);


					SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_AXIS_RUDDER_SET, false);
					SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_AXIS_ELEVATOR_SET, false);
					SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_AXIS_AILERONS_SET, false);

					break;
				}

				case EVENT_GEAR_TOGGLE:
				{
					SimConnect_RequestDataOnSimObject(hAirbusHydraulicsGauge, REQUEST_LANDING_GEAR, DEF_GEAR_POSITION, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_ONCE);

					break;
				}

				case EVENT_AXIS_RUDDER_SET:
				{
					//the returned data from SimConnect is reversed hence the 100- operation
					//double rudderSimPosition = 100 - calculatePercentage(evt->dwData);

					if ((greenHydraulicSystem->getFluid() < 1 || greenHydraulicSystem->getPressure() < 1000) && (blueHydraulicSystem->getFluid() < 1 || blueHydraulicSystem->getPressure() < 1000))
					{
						SimConnect_RequestDataOnSimObject(hAirbusHydraulicsGauge, REQUEST_RUDDER_POSITION, DEF_RUDDER_POSITION, SIMCONNECT_SIMOBJECT_TYPE_USER, SIMCONNECT_PERIOD_ONCE);
					}
					break;
				}
	
				break;
			}
			break;
		}
		case SIMCONNECT_RECV_ID_SIMOBJECT_DATA:
		{
			SIMCONNECT_RECV_SIMOBJECT_DATA* pObjData = (SIMCONNECT_RECV_SIMOBJECT_DATA*)pData;

			switch (pObjData->dwRequestID)
			{
				case REQUEST_LANDING_GEAR:
				{
					if (greenHydraulicSystem->getPressure() < 2800 || greenHydraulicSystem->getFluid() <= 0)
					{
						if (pObjData->dwData == 0)
						{
							DWORD gearPosition = 1;

							landing_gear_state = gearPosition;
							landing_gear_switch = gearPosition;

							SimConnect_TransmitClientEvent(hAirbusHydraulicsGauge, SIMCONNECT_OBJECT_ID_USER, EVENT_GEAR_DOWN, gearPosition, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
						}
						else if (pObjData->dwData == 1)
						{
							DWORD gearPosition = 0;

							landing_gear_state = gearPosition;
							landing_gear_switch = gearPosition;

							SimConnect_TransmitClientEvent(hAirbusHydraulicsGauge, SIMCONNECT_OBJECT_ID_USER, EVENT_GEAR_UP, gearPosition, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
						}
					}
					else
					{
						DWORD gearPosition = pObjData->dwData;
						SimConnect_TransmitClientEvent(hAirbusHydraulicsGauge, SIMCONNECT_OBJECT_ID_USER, EVENT_GEAR_SET, gearPosition, SIMCONNECT_GROUP_PRIORITY_HIGHEST, 0);
					}

					break;
				}

				default:
					break;
			}
			break;
		}
		case SIMCONNECT_RECV_ID_EXCEPTION:
		{
			SIMCONNECT_RECV_EXCEPTION * pException = (SIMCONNECT_RECV_EXCEPTION *)pData;
			std::cout << "SimConnect Exception: " << pException->dwException << std::endl;
			break;
		}
		/*
		case SIMCONNECT_RECV_ID_EVENT_FRAME:
		{
			SIMCONNECT_RECV_EVENT_FRAME* evt = (SIMCONNECT_RECV_EVENT_FRAME*)pData;
			switch (evt->uEventID)
			{

				case EVENT_FRAME_TIMER:
				{

					break;
				}

				default:
					break;
			}
			break;
		}
		*/

		default:
			break;
	}
}

/*Launches the SimConnect callback loop and sets the required SimConnect definitions for the get/set of sim variables*/
void OpenSimConnect()
{
	HRESULT hr;

	// Instantiate SimConnect
	if (SUCCEEDED(SimConnect_Open(&hAirbusHydraulicsGauge, ("Airbus-Hydraulics"), NULL, 0, 0, SIMCONNECT_OPEN_CONFIGINDEX_LOCAL)))
	{
		std::cout << "\n(Airbus-Hydraulics Message): Airbus-Hydraulics connected to Prepar3D!\n";

		/*
		//Create a frame timer event
		hr = SimConnect_SubscribeToSystemEvent(hAirbusHydraulicsGauge, EVENT_FRAME_TIMER, "6Hz"); //6Hz timer
		hr = SimConnect_SetSystemEventState(hAirbusHydraulicsGauge, EVENT_FRAME_TIMER, SIMCONNECT_STATE_OFF);
		*/

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_DISABLE_FLIGHT_CONTROLS, "Airbus.Hydraulics.SetFlightControls.DisableEvent");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_DISABLE_FLIGHT_CONTROLS);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_ENABLE_FLIGHT_CONTROLS, "Airbus.Hydraulics.SetFlightControls.EnableEvent");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_ENABLE_FLIGHT_CONTROLS);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_GREEN_HYDRAULICS_PUMP_TOGGLE, "Airbus.Hydraulics.SetGrenHydraulicsPump.Event");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_GREEN_HYDRAULICS_PUMP_TOGGLE);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_BLUE_HYDRAULICS_PUMP_TOGGLE, "Airbus.Hydraulics.SetBlueHydraulicsPump.Event");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_BLUE_HYDRAULICS_PUMP_TOGGLE);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_YELLOW_HYDRAULICS_PUMP_TOGGLE, "Airbus.Hydraulics.SetYellowHydraulicsPump.Event");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_YELLOW_HYDRAULICS_PUMP_TOGGLE);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_GREEN_HYDRAULICS_FLUID_LEAK_TOGGLE, "Airbus.Hydraulics.SetGrenHydraulicsFluidLeak.Event");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_GREEN_HYDRAULICS_FLUID_LEAK_TOGGLE);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_BLUE_HYDRAULICS_FLUID_LEAK_TOGGLE, "Airbus.Hydraulics.SetBlueHydraulicsFluidLeak.Event");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_BLUE_HYDRAULICS_FLUID_LEAK_TOGGLE);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_YELLOW_HYDRAULICS_FLUID_LEAK_TOGGLE, "Airbus.Hydraulics.SetYellowHydraulicsFluidLeak.Event");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_YELLOW_HYDRAULICS_FLUID_LEAK_TOGGLE);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_GREEN_HYDRAULICS_PUMP_FAIL_TOGGLE, "Airbus.Hydraulics.SetGrenHydraulicsPumpFail.Event");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_GREEN_HYDRAULICS_PUMP_FAIL_TOGGLE);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_BLUE_HYDRAULICS_PUMP_FAIL_TOGGLE, "Airbus.Hydraulics.SetBlueHydraulicsPumpFail.Event");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_BLUE_HYDRAULICS_PUMP_FAIL_TOGGLE);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_YELLOW_HYDRAULICS_PUMP_FAIL_TOGGLE, "Airbus.Hydraulics.SetYellowHydraulicsPumpFail.Event");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_YELLOW_HYDRAULICS_PUMP_FAIL_TOGGLE);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_AXIS_ELEVATOR_SET, "AXIS_ELEVATOR_SET");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_AXIS_ELEVATOR_SET, false);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_AXIS_AILERONS_SET, "AXIS_AILERONS_SET");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_AXIS_AILERONS_SET, false);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_AXIS_RUDDER_SET, "AXIS_RUDDER_SET");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_AXIS_RUDDER_SET, false);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_BRAKING_ACTION, "BRAKES");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_BRAKING_ACTION, true);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_GEAR_TOGGLE, "GEAR_TOGGLE");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_GEAR_TOGGLE, false);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_GEAR_SET, "GEAR_SET");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_GEAR_SET, false);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_AXIS_LEFT_BRAKE_SET, "AXIS_LEFT_BRAKE_SET");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_AXIS_LEFT_BRAKE_SET, true);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_AXIS_RIGHT_BRAKE_SET, "AXIS_RIGHT_BRAKE_SET");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST_MASKABLE, EVENT_AXIS_RIGHT_BRAKE_SET, true);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_GEAR_UP, "GEAR_UP");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_GEAR_UP, false);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_GEAR_DOWN, "GEAR_DOWN");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_GEAR_DOWN, false);


		
		
		// Set notificaiton priority groups
		hr = SimConnect_SetNotificationGroupPriority(hAirbusHydraulicsGauge, GROUP_HIGHEST, SIMCONNECT_GROUP_PRIORITY_HIGHEST);
		hr = SimConnect_SetNotificationGroupPriority(hAirbusHydraulicsGauge, GROUP_HIGHEST_MASKABLE, SIMCONNECT_GROUP_PRIORITY_HIGHEST_MASKABLE);
				
		// Define aircraft gear position
		hr = SimConnect_AddToDataDefinition(hAirbusHydraulicsGauge, DEF_GEAR_POSITION, "GEAR HANDLE POSITION", "Bool", SIMCONNECT_DATATYPE_INT32);


		//Define a callback in this dll so that the simulation can be notified of SimConnect events
		if (hr == S_OK)
			hr = SimConnect_CallDispatch(hAirbusHydraulicsGauge, DispatchProcedure, NULL);

	}
}

void CloseSimConnect()
{
	if (hAirbusHydraulicsGauge != NULL)
		HRESULT hr = SimConnect_Close(hAirbusHydraulicsGauge);
}
