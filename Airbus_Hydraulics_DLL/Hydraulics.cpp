/*
* iniBuilds Task by Alp Deniz Senyurt
*
* This file is the cpp file for the Hydraulics base class
*/
#include "pch.h"

#include "Hydraulics.h"

/*
* Constructor
* Initialize with nominal values
*/
Hydraulics::Hydraulics(const std::string & name)
    : systemName(name), pressure(NOMINAL_PRESSURE), fluidReservoir(NOMINAL_FLUID_AMOUNT), isPumpActive(true), isRegulatorRunning(false), isPumpFailed(false)
{
    startRegulator();
}

// Make sure the regulator is stopped and thread is not running anymore
Hydraulics::~Hydraulics()
{
    stopRegulator();
}

// Start the regulator thread
void Hydraulics::startRegulator()
{
    isRegulatorRunning = true;

    std::thread([this]() {
        while (isRegulatorRunning)
        {
            if (isPumpActive)
            {
                std::lock_guard<std::mutex> lock(pressureMutex);
                
                double deltaTime = 0.033;

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
            std::this_thread::sleep_for(std::chrono::milliseconds(33));
        }
        }).detach();
}

// Stop the regulator thread
void Hydraulics::stopRegulator()
{
    isRegulatorRunning = false;
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

// Set fluid
void Hydraulics::setFluid(double newFluid)
{
    std::lock_guard<std::mutex> lock(fluidReservoirMutex);
    fluidReservoir = newFluid;
}

// Get fluid
double Hydraulics::getFluid()
{
    std::lock_guard<std::mutex> lock(fluidReservoirMutex);
    return fluidReservoir;
}

// Get if the pump is active
bool Hydraulics::getIsPumpActive()
{
    return isPumpActive.load();
}

// Set the pump state
void Hydraulics::setIsPumpActive(bool state)
{
    isPumpActive.store(state);
}

// Get if there is leak in the system
bool Hydraulics::getIsLeaking()
{
    return isLeaking.load();
}

// Set leak state of the system
void Hydraulics::setIsLeaking(bool state)
{
    isLeaking.store(state);
}

// Get if the pump has failed
bool Hydraulics::getIsPumpFailed()
{
    return isPumpFailed.load();
}

// Set the pump failure state
void Hydraulics::setIsPumpFailed(bool state)
{
    isPumpFailed.store(state);
}

// Simulate hydraulic fluid leak
void Hydraulics::simulateLeak()
{
    isLeaking = true;

    std::thread([this]() {
        while (isLeaking && fluidReservoir > 0.0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10)); // drip interval

            // lock both pressure and fluidReservoir simultaneously
            std::scoped_lock<std::mutex, std::mutex> lock(pressureMutex, fluidReservoirMutex);

            fluidReservoir -= FLUID_DEPLETION_RATE;

            if (fluidReservoir < 50.0)
            {
                pressure -= 0.1; // simulate pressure drop when fluid is depleted
                if (pressure < 0.0)
                {
                    pressure = 0.0; // pressure can't go negative
                }

                if (fluidReservoir < 0.0)
                {
                    fluidReservoir = 0.0; // reservoir can't go negative
                }
            }
        }
        }).detach();
}

// Stop fluid leak simulation
void Hydraulics::stopLeak()
{
    isLeaking = false;
}

// Simulate pump failure
void Hydraulics::simulatePumpFail()
{
    isPumpFailed = true;
    isPumpActive = false;

    std::thread([this]() {
        while (isPumpFailed && !isPumpActive && pressure > 0.0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10)); // interval to reduce pressure

            // Lock the pressure mutex to safely modify the pressure
            std::scoped_lock<std::mutex> lock(pressureMutex);

            pressure -= PRESSURE_DEPLETION_RATE;

            if (pressure < 0.0)
            {
                pressure = 0.0; // pressure can't go negative
            }
        }
        }).detach();

}


// Stop pump failure simulation
void Hydraulics::stopPumpFail()
{
    isPumpFailed = false;
    isPumpActive = true;
}


//// Display system status
//void Hydraulics::displayStatus()
//{
//    std::lock_guard<std::mutex> lock(pressureMutex);
//    std::cout << "System: " << systemName << " | Pressure: " << pressure << " PSI" << " | Fluid Reservoir: " << fluidReservoir << "%" << " | Pump: " << (isPumpActive ? "Active" : "Inactive") << std::endl;  // for debugging
//}