#include "pch.h"

#include "GreenHydraulics.h"


GreenHydraulics::GreenHydraulics() : Hydraulics("Green")
{
}

// Function to handle braking action of the Green HYD system.
void GreenHydraulics::applyBraking(double deltaTime)
{
    std::lock_guard<std::mutex> lock(pressureMutex);

    if (pressure > MIN_BRAKING_PRESSURE && fluidReservoir > 0.0)
    {
        pressure -= BRAKING_PRESSURE_DROP_RATE * deltaTime; // pressure drops a bit due to braking

        if (pressure < MIN_BRAKING_PRESSURE)
        {
            pressure = MIN_BRAKING_PRESSURE; // pressure cannot go below the min value
        }

    }
}


//void GreenHydraulics::displayStatus() const
//{
//	std::cout << "[Green System] ";
//	Hydraulics::displayStatus();
//}