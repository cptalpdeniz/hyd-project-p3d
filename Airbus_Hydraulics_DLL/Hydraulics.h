/*
* iniBuilds Task by Alp Deniz Senyurt
*
* This file is the header file for the Hydraulics base class
*/

#ifndef A320_HYDRAULICS_H
#define A320_HYDRAULICS_H

#include <chrono>
#include <mutex>

class Hydraulics
{
protected:
    std::string systemName;
    double pressure; // PSI unit
    double fluidReservoir; // in %, 0-100 range

    std::atomic<bool> isPumpActive;
    std::atomic<bool> isLeaking;
    std::atomic<bool> isRegulatorRunning;
    std::atomic<bool> isPumpFailed;

    std::mutex pressureMutex;
    std::mutex fluidReservoirMutex;

    // following variables are the same for all hydraulic systems (obviously there might be differences
    // between systems however that is not simulated for simplicity purposes)
    static constexpr double NOMINAL_PRESSURE = 3000.0;          // target pressure in PSI
    static constexpr double NOMINAL_FLUID_AMOUNT = 100.0;       // percent of the fluid reservoir
    static constexpr double MAX_RECOVERY_RATE = 300.0;          // maximum PSI per second
    static constexpr double RECOVERY_FACTOR = 0.1;              // proportional recovery factor
    static constexpr double FLUID_DEPLETION_RATE = 0.51;        // depletion rate of the fluid in a leak situation (ORIGINAL VALUE 0.01)

public:
    // Constructor
    Hydraulics(const std::string & name);

    // Virtual destructor
    virtual ~Hydraulics();

    // Start the regulator thread
    void startRegulator();

    // Stop the regulator thread
    void stopRegulator();

    // Activate pump
    virtual void activatePump();

    // Deactivate pump
    virtual void deactivatePump();

    // Set pressure
    virtual void setPressure(double newPressure);

    // Get pressure
    virtual double getPressure();

    // Set fluid
    virtual void setFluid(double newFluid);

    // Get fluid
    virtual double getFluid();

    // Get if the pump is active
    virtual bool getIsPumpActive();

    // Set the pump state
    virtual void setIsPumpActive(bool state);

    // Get if the pump is active
    virtual bool getIsLeaking();

    // Set the pump state
    virtual void setIsLeaking(bool state);

    // Get if the pump has failed
    virtual bool getIsPumpFailed();

    // Set the pump failure state
    virtual void setIsPumpFailed(bool state);

    // Display system status
    //virtual void displayStatus();

    /*
    * Failures Section
    */
    // Simulate fluid leak
    void simulateLeak();

    // Stop fluid leak simulation
    void stopLeak();

    // Simulate pump failure
    void simulatePumpFail();

    // Stop pump failure simulation
    void stopPumpFail();

protected:
    // Regulate pressure automatically
    void regulatePressure(double deltaTime);
};

#endif
