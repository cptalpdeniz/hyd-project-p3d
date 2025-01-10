/*
* iniBuilds Task by Alp Deniz Senyurt
*
* This file is the cpp file for the Hydraulics base class
*/

#include "Hydraulics.h"

//#include <iostream>
#include <thread>
#include <chrono>

/*
* Constructor
* Initialize with nominal values
*/
Hydraulics::Hydraulics(const std::string & name)
    : systemName(name), pressure(NOMINAL_PRESSURE), fluidReservoir(NOMINAL_FLUID_AMOUNT), isPumpActive(false), running(false)
{
}

// Make sure the regulator is stopped and thread is not running anymore
Hydraulics::~Hydraulics()
{
    stopRegulator();
}

// Start the regulator thread
void Hydraulics::startRegulator()
{
    running = true;
    std::thread([this]() {
        while (running)
        {
            if (isPumpActive)
            {
                regulatePressure(0.033); // 16ms time step (~60 FPS)
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(33));
        }
        }).detach();
}

// Stop the regulator thread
void Hydraulics::stopRegulator()
{
    running = false;
}

void Hydraulics::activatePump()
{
    isPumpActive = true;
    //std::cout << systemName << " pump activated." << std::endl; // for debugging
}

void Hydraulics::deactivatePump()
{
    isPumpActive = false;
    //std::cout << systemName << " pump deactivated." << std::endl; // for debugging
}

// Set pressure
void Hydraulics::setPressure(double newPressure)
{
    std::lock_guard<std::mutex> lock(pressureMutex);
    pressure = newPressure;
}

// Get pressure
double Hydraulics::getPressure()
{
    std::lock_guard<std::mutex> lock(pressureMutex);
    return pressure;
}

//// Display system status
//void Hydraulics::displayStatus()
//{
//    std::lock_guard<std::mutex> lock(pressureMutex);
//    std::cout << "System: " << systemName << " | Pressure: " << pressure << " PSI" << " | Fluid Reservoir: " << fluidReservoir << "%" << " | Pump: " << (isPumpActive ? "Active" : "Inactive") << std::endl;  // for debugging
//}

// Regulate pressure automatically
void Hydraulics::regulatePressure(double deltaTime)
{
    std::lock_guard<std::mutex> lock(pressureMutex);
    if (fluidReservoir > 0.0 && pressure < NOMINAL_PRESSURE)
    {
        // using this calculation, the pressure build up slows down the higher it gets closer to nominal 3000 value
        double recoveryRate = RECOVERY_FACTOR * (NOMINAL_PRESSURE - pressure);
        if (recoveryRate > MAX_RECOVERY_RATE)
        {
            recoveryRate = MAX_RECOVERY_RATE; // recovery rate cannot be too much
        }

        pressure += recoveryRate * deltaTime;
        if (pressure > NOMINAL_PRESSURE)
        {
            pressure = NOMINAL_PRESSURE; // pressure limit, no simulation of pressure relief valve however can be implemented in the future here
        }
    }
}

// Simulate hydraulic fluid leak
void Hydraulics::simulateLeak(double deltaTime)
{
    std::lock_guard<std::mutex> lock(pressureMutex);
    fluidReservoir -= FLUID_DEPLETION_RATE * deltaTime;
    if (fluidReservoir < 0.0)
    {
        fluidReservoir = 0.0; // reservoir can't go negative
    }

    // if there is no hydraulic fluid, pressure decreases
    if (fluidReservoir <= 0.0)
    {
        pressure -= 50.0 * deltaTime; // simulate pressure drop due to fluid leak
        if (pressure < 0.0)
        {
            pressure = 0.0; // pressure can't go negative
        }
    }
}

// Simulate pump failure
void Hydraulics::simulatePumpFailure()
{
    std::lock_guard<std::mutex> lock(pressureMutex);

    isPumpActive = false;
}