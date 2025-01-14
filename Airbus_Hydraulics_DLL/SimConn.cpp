#include "pch.h"

#include "SimConn.h"
#include "Gauge.h"


//SimConnect related variable
HANDLE  hAirbusHydraulicsGauge = NULL;

/* Event Invoker for the switch clicks
@param [enum] switch_event: SimConnect EVENT_ID
*/
void SendHydraulicsGaugeMode(EVENT_ID switch_event)
{
	SimConnect_TransmitClientEvent(hAirbusHydraulicsGauge, 0, switch_event, 0, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
}

/*The main SimConnect callback loop*/
void CALLBACK DispatchProcedure(SIMCONNECT_RECV* pData, DWORD cbData, void* pContext)
{
	switch (pData->dwID)
	{
		case SIMCONNECT_RECV_ID_EVENT:
		{
			SIMCONNECT_RECV_EVENT* evt = (SIMCONNECT_RECV_EVENT*)pData;

			switch (evt->uEventID)
			{
				case EVENT_GREEN_HYDRAULICS_PUMP_TOGGLE:
				{
					//if state is true, start the regulator to increase pressure
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
					//if state is true, start the regulator to increase pressure
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
					//if state is true, start the regulator to increase pressure
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
					//if state is true, start the fluid leak simulation by calling the respective simulateLeak() function
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
					//if state is true, start the fluid leak simulation by calling the respective simulateLeak() function
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
					//if state is true, start the fluid leak simulation by calling the respective simulateLeak() function
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
					//if state is true, start the pump failure simulation by calling the respective simulatePumpFail() function
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
					//if state is true, start the pump failure simulation by calling the respective simulatePumpFail() function
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
					//if state is true, start the pump failure simulation by calling the respective simulatePumpFail() function
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

				//Disable flight controls by masking all AXIS and input/set events of primary flight control surfaces (ELEVATOR, AILERON, RUDDER)
				//a better and more consistent, custom solution could be made however would require a lot of work with not just the gauge but combination of the model, animations etc.
				case EVENT_DISABLE_FLIGHT_CONTROLS:
				{
 					SimConnect_RemoveClientEvent(hAirbusHydraulicsGauge, GROUP_STANDARD, EVENT_AXIS_RUDDER_SET);
					SimConnect_RemoveClientEvent(hAirbusHydraulicsGauge, GROUP_STANDARD, EVENT_AXIS_ELEVATOR_SET);
					SimConnect_RemoveClientEvent(hAirbusHydraulicsGauge, GROUP_STANDARD, EVENT_AXIS_AILERONS_SET);

					SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST_MASKABLE, EVENT_AXIS_RUDDER_SET, true);
					SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST_MASKABLE, EVENT_AXIS_ELEVATOR_SET, true);
					SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST_MASKABLE, EVENT_AXIS_AILERONS_SET, true);

					SimConnect_RemoveClientEvent(hAirbusHydraulicsGauge, GROUP_STANDARD, EVENT_RUDDER_SET);
					SimConnect_RemoveClientEvent(hAirbusHydraulicsGauge, GROUP_STANDARD, EVENT_ELEVATOR_SET);
					SimConnect_RemoveClientEvent(hAirbusHydraulicsGauge, GROUP_STANDARD, EVENT_AILERON_SET);

					SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST_MASKABLE, EVENT_RUDDER_SET, true);
					SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST_MASKABLE, EVENT_ELEVATOR_SET, true);
					SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST_MASKABLE, EVENT_AILERON_SET, true);

					break;
				}

				//Enable flight controls by setting higher notification priority, removing masking on all AXIS and input/set events of primary flight control surfaces (ELEVATOR, AILERON, RUDDER)
				//a better and more consistent, custom solution could be made however would require a lot of work with not just the gauge but combination of the model, animations etc.
				case EVENT_ENABLE_FLIGHT_CONTROLS:
				{
					SimConnect_RemoveClientEvent(hAirbusHydraulicsGauge, GROUP_HIGHEST_MASKABLE, EVENT_AXIS_RUDDER_SET);
					SimConnect_RemoveClientEvent(hAirbusHydraulicsGauge, GROUP_HIGHEST_MASKABLE, EVENT_AXIS_ELEVATOR_SET);
					SimConnect_RemoveClientEvent(hAirbusHydraulicsGauge, GROUP_HIGHEST_MASKABLE, EVENT_AXIS_AILERONS_SET);


					SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_STANDARD, EVENT_AXIS_RUDDER_SET, true);
					SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_STANDARD, EVENT_AXIS_ELEVATOR_SET, true);
					SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_STANDARD, EVENT_AXIS_AILERONS_SET, true);

					SimConnect_RemoveClientEvent(hAirbusHydraulicsGauge, GROUP_HIGHEST_MASKABLE, EVENT_RUDDER_SET);
					SimConnect_RemoveClientEvent(hAirbusHydraulicsGauge, GROUP_HIGHEST_MASKABLE, EVENT_ELEVATOR_SET);
					SimConnect_RemoveClientEvent(hAirbusHydraulicsGauge, GROUP_HIGHEST_MASKABLE, EVENT_AILERON_SET);


					SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_STANDARD, EVENT_RUDDER_SET, true);
					SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_STANDARD, EVENT_ELEVATOR_SET, true);
					SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_STANDARD, EVENT_AILERON_SET, true);

					break;
				}

				//Different approach compared to flight controls, more cases to handle and gear position is required.
				case EVENT_GEAR_TOGGLE:
				{
					SimConnect_RequestDataOnSimObject(hAirbusHydraulicsGauge, REQUEST_LANDING_GEAR, DEF_GEAR_POSITION, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_ONCE);

					break;
				}

				//Handle braking by checking for Green HYD system status and applying braking (pressure drop simulation)
				case EVENT_BRAKING_ACTION:
				{
					if (greenHydraulicSystem->getFluid() > 0 && greenHydraulicSystem->getPressure() > 1000)
					{
						greenHydraulicSystem->applyBraking(0.0333); //calling for 30 fps timer
					}
					break;
				}
				
				//Handle disabling of the brakes by toggling brake failure
				//there is no way to mask brake events hence failure methodology
				//there is probably better way to do this, however I was not able to find any examples or come up with something that works consistently like this one
				case EVENT_DISABLE_BRAKES:
				{
					SimConnect_TransmitClientEvent(hAirbusHydraulicsGauge, SIMCONNECT_OBJECT_ID_USER, EVENT_TOGGLE_BRAKE_FAIL, 1, GROUP_HIGHEST, 0);
					SimConnect_RemoveClientEvent(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_BRAKING_ACTION);

					SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST_MASKABLE, EVENT_BRAKING_ACTION, true);

					break;
				}

				//Handle enabling brakes by cancelling brake failure status
				case EVENT_ENABLE_BRAKES:
				{
					SimConnect_TransmitClientEvent(hAirbusHydraulicsGauge, SIMCONNECT_OBJECT_ID_USER, EVENT_TOGGLE_BRAKE_FAIL, 0, GROUP_HIGHEST, 0);

					SimConnect_RemoveClientEvent(hAirbusHydraulicsGauge, GROUP_HIGHEST_MASKABLE, EVENT_BRAKING_ACTION);

					SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_BRAKING_ACTION, false);

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
				//Same as other implementations, my goal was to not even touch the gear lever however without a custom aircraft (or a complete project), I couldn't achieve how I wanted it to be, it simulates
				//and works as expected and required however if the gear handle was not touched and gear status was not tied to the position of the handle would have been a big improvement
				case REQUEST_LANDING_GEAR:
				{
					if (greenHydraulicSystem->getPressure() < 2800 || greenHydraulicSystem->getFluid() <= 0)
					{
						//if gear is set up, keep it down as we don't have pressure
						if (pObjData->dwData == 0)
						{
							DWORD gearPosition = 1;

							landing_gear_state = gearPosition;
							landing_gear_switch = gearPosition;

							SimConnect_TransmitClientEvent(hAirbusHydraulicsGauge, SIMCONNECT_OBJECT_ID_USER, EVENT_GEAR_DOWN, gearPosition, SIMCONNECT_GROUP_PRIORITY_HIGHEST, SIMCONNECT_EVENT_FLAG_GROUPID_IS_PRIORITY);
						}
						//if gear is set down, keep it up as we don't have pressure
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
						//gear can be set to whatever the position is deemed so
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

		default:
			break;
	}
}

/*Launches the SimConnect callback loop and sets the required SimConnect definitions for the get/set of sim variables*/
void OpenSimConnect()
{
	HRESULT hr;

	//Instantiate SimConnect
	if (SUCCEEDED(SimConnect_Open(&hAirbusHydraulicsGauge, ("Airbus-Hydraulics"), NULL, 0, 0, SIMCONNECT_OPEN_CONFIGINDEX_LOCAL)))
	{
		std::cout << "\n(Airbus-Hydraulics Message): Airbus-Hydraulics connected to Prepar3D!\n";

		//Map custom events to sim events
		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_DISABLE_FLIGHT_CONTROLS, "Airbus.Hydraulics.SetFlightControls.DisableEvent");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_DISABLE_FLIGHT_CONTROLS);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_ENABLE_FLIGHT_CONTROLS, "Airbus.Hydraulics.SetFlightControls.EnableEvent");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_ENABLE_FLIGHT_CONTROLS);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_DISABLE_BRAKES, "Airbus.Hydraulics.SetBrakes.DisableEvent");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_DISABLE_BRAKES);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_ENABLE_BRAKES, "Airbus.Hydraulics.SetBrakes.EnableEvent");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_ENABLE_BRAKES);

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
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_STANDARD, EVENT_AXIS_ELEVATOR_SET, true);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_AXIS_AILERONS_SET, "AXIS_AILERONS_SET");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_STANDARD, EVENT_AXIS_AILERONS_SET, true);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_AXIS_RUDDER_SET, "AXIS_RUDDER_SET");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_STANDARD, EVENT_AXIS_RUDDER_SET, true);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_ELEVATOR_SET, "ELEVATOR_SET");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_STANDARD, EVENT_ELEVATOR_SET, true);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_AILERON_SET, "AILERON_SET");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_STANDARD, EVENT_AILERON_SET, true);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_RUDDER_SET, "RUDDER_SET");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_STANDARD, EVENT_RUDDER_SET, true);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_BRAKING_ACTION, "BRAKES");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST_MASKABLE, EVENT_BRAKING_ACTION, false);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_GEAR_TOGGLE, "GEAR_TOGGLE");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_HIGHEST, EVENT_GEAR_TOGGLE, false);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_GEAR_SET, "GEAR_SET");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_STANDARD, EVENT_GEAR_SET, false);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_GEAR_UP, "GEAR_UP");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_STANDARD, EVENT_GEAR_UP, false);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_GEAR_DOWN, "GEAR_DOWN");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_STANDARD, EVENT_GEAR_DOWN, false);

		hr = SimConnect_MapClientEventToSimEvent(hAirbusHydraulicsGauge, EVENT_TOGGLE_BRAKE_FAIL, "TOGGLE_TOTAL_BRAKE_FAILURE");
		hr = SimConnect_AddClientEventToNotificationGroup(hAirbusHydraulicsGauge, GROUP_STANDARD, EVENT_TOGGLE_BRAKE_FAIL, false);
		
		
		//Define aircraft gear position
		hr = SimConnect_AddToDataDefinition(hAirbusHydraulicsGauge, DEF_GEAR_POSITION, "GEAR HANDLE POSITION", "Bool", SIMCONNECT_DATATYPE_INT32);

		//Set notificaiton priority groups
		hr = SimConnect_SetNotificationGroupPriority(hAirbusHydraulicsGauge, GROUP_HIGHEST, SIMCONNECT_GROUP_PRIORITY_HIGHEST);
		hr = SimConnect_SetNotificationGroupPriority(hAirbusHydraulicsGauge, GROUP_HIGHEST_MASKABLE, SIMCONNECT_GROUP_PRIORITY_HIGHEST_MASKABLE);
		hr = SimConnect_SetNotificationGroupPriority(hAirbusHydraulicsGauge, GROUP_STANDARD, SIMCONNECT_GROUP_PRIORITY_STANDARD);


		//Define a callback in this dll so that the simulation can be notified of SimConnect events
		if (hr == S_OK)
		{
			hr = SimConnect_CallDispatch(hAirbusHydraulicsGauge, DispatchProcedure, NULL);
		}		
	}
}

void CloseSimConnect()
{
	if (hAirbusHydraulicsGauge != NULL)
	{
		HRESULT hr = SimConnect_Close(hAirbusHydraulicsGauge);
	}
}
