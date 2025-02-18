#include "pch.h"

#include "Hydraulics.h"

/* Constructor
* Initialize with nominal values
@param [const std::string &] name: name of the Hydraulic System
*/
Hydraulics::Hydraulics(const std::string & name)
    : systemName(name), pressure(NOMINAL_PRESSURE), fluidReservoir(NOMINAL_FLUID_AMOUNT), isPumpActive(true), isRegulatorRunning(false), isPumpFailed(false)
{
    startRegulator();
}

/* Make sure the regulator is stopped and thread is not running anymore
*/
Hydraulics::~Hydraulics()
{
    stopRegulator();
}

/* Start the regulator thread
*/
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
                    //using this calculation, the pressure build up slows down the higher it gets closer to nominal 3000 value
                    double recoveryRate = RECOVERY_FACTOR * (NOMINAL_PRESSURE - pressure);
                    if (recoveryRate > MAX_RECOVERY_RATE)
                    {
                        recoveryRate = MAX_RECOVERY_RATE; //recovery rate cannot be too much
                    }

                    pressure += recoveryRate * deltaTime;
                    if (pressure > NOMINAL_PRESSURE)
                    {
                        pressure = NOMINAL_PRESSURE; //pressure limit, no simulation of pressure relief valve however can be implemented in the future here
                    }
                }

            }
            std::this_thread::sleep_for(std::chrono::milliseconds(33));
        }
        }).detach();
}

/* Stop the regulator thread
*/void Hydraulics::stopRegulator()
{
    isRegulatorRunning = false;
}

/* Activates the pump
*/
void Hydraulics::activatePump()
{
    isPumpActive = true;
}

/* Deactivate the pump, does not stop regulator, must be used carefully
*/void Hydraulics::deactivatePump()
{
    isPumpActive = false;
}

/* Set pressure
@param [double] newPressure: the new pressure level, must be 0-3000
*/
void Hydraulics::setPressure(double newPressure)
{
    std::lock_guard<std::mutex> lock(pressureMutex);
    pressure = newPressure;
}

/* Get pressure level
@return [double] pressure: PSI of the system
*/
double Hydraulics::getPressure()
{
    std::lock_guard<std::mutex> lock(pressureMutex);
    return pressure;
}

/* Set fluid reservoir level in percent
@param [double] newFluid: the new fluid level to set the reservoir level. Must be 0-100 value with 2 decimal places.
*/
void Hydraulics::setFluid(double newFluid)
{
    std::lock_guard<std::mutex> lock(fluidReservoirMutex);
    fluidReservoir = newFluid;
}

/* Get fluid reservoir level (in percent)
@return [double] fluidReservoir
*/
double Hydraulics::getFluid()
{
    std::lock_guard<std::mutex> lock(fluidReservoirMutex);
    return fluidReservoir;
}

/* Get if the pump is active
@return [bool] isPumpActive
*/
bool Hydraulics::getIsPumpActive()
{
    return isPumpActive.load();
}

/* Set the pump state, this only changes the variable, does not act as a "starter" neither does it start the regulator. 
@param [bool] state: state to set the isPumpActive variable
*/
void Hydraulics::setIsPumpActive(bool state)
{
    isPumpActive.store(state);
}

/* Get if there is leak in the system
@return [bool] isLeaking
*/
bool Hydraulics::getIsLeaking()
{
    return isLeaking.load();
}

/* Set leak state of the system
@param [bool] state: state to set the IsLeaking variable
*/
void Hydraulics::setIsLeaking(bool state)
{
    isLeaking.store(state);
}

/* Get if the pump has failed
@return [bool] isPumpFailed
*/
bool Hydraulics::getIsPumpFailed()
{
    return isPumpFailed.load();
}

/* Set the pump failure state
@param [bool] state: state to set the isPumpFailed variable
*/
void Hydraulics::setIsPumpFailed(bool state)
{
    isPumpFailed.store(state);
}

/* Simulate hydraulic fluid leak, runs on separate thread
*/
void Hydraulics::simulateLeak()
{
    isLeaking = true; //set leaking condition to true

    std::thread([this]() {
        while (isLeaking)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); //increased interval for better simulation

            std::scoped_lock<std::mutex, std::mutex> lock(pressureMutex, fluidReservoirMutex); //lock both pressure and fluidReservoir simultaneously

            //gradual fluid depletion
            if (fluidReservoir > 0.0)
            {
                fluidReservoir -= FLUID_DEPLETION_RATE;

                if (fluidReservoir < 0.0)
                {
                    fluidReservoir = 0.0; //Clamp to 0
                }
            }

            //gradual pressure drop based on reservoir level
            if (fluidReservoir <= 50.0) //start pressure drop when reservoir gets low
            {
                double pressureDropRate = (50.0 - fluidReservoir) / 50.0 * PRESSURE_DEPLETION_RATE; //leak based on the fluid and pressure values
                pressure -= pressureDropRate;

                if (pressure < 0.0)
                {
                    pressure = 0.0; //pressure cannot be negative
                }
            }

            //stop simulation when fluid and pressure are both depleted
            if (fluidReservoir <= 0.0 && pressure <= 0.0)
            {
                isLeaking = false;
            }
        }
        }).detach();
}

/* Stop fluid leak simulation, sets isLeaking to false
*/ 
void Hydraulics::stopLeak()
{
    isLeaking = false;
}

/* Simulates a PUMP failure by gradually lowering the pressure based on the PRESSURE_DEPLETION_RATE
*/
void Hydraulics::simulatePumpFail()
{
    isPumpFailed = true;
    isPumpActive = false;

    std::thread([this]() {
        while (isPumpFailed && !isPumpActive && pressure > 0.0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10)); //interval to reduce pressure

            //Lock the pressure mutex to safely modify the pressure
            std::scoped_lock<std::mutex> lock(pressureMutex);

            pressure -= PRESSURE_DEPLETION_RATE;

            if (pressure < 0.0)
            {
                pressure = 0.0; //pressure cannot be negative
            }
        }
        }).detach();

}

/* Stop pump failure simulation
*/
void Hydraulics::stopPumpFail()
{
    isPumpFailed = false;
    isPumpActive = true;
}