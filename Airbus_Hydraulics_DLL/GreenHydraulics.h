#ifndef GREENHYDRAULICS_H
#define GREENHYDRAULICS_H

#include "Hydraulics.h"

class GreenHydraulics : public Hydraulics
{
public:
	GreenHydraulics();
	//void displayStatus() const override;
	void applyBraking(double deltaTime);
};


#endif