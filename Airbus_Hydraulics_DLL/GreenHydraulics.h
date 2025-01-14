#ifndef GREENHYDRAULICS_H
#define GREENHYDRAULICS_H

#include "Hydraulics.h"

class GreenHydraulics : public Hydraulics
{
public:
	GreenHydraulics();
	void applyBraking(double deltaTime);

private:
	static constexpr double MIN_BRAKING_PRESSURE = 1000.0; //PSI
	static constexpr double BRAKING_FLUID_CONSUMPTION_RATE = 0.5; //percentage per second
	static constexpr double BRAKING_PRESSURE_DROP_RATE = 2.2; //PSI per second
};


#endif