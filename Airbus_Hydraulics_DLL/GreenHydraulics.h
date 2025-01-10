#ifndef GREENHYDRAULICS_H
#define GREENHYDRAULICS_H

#include "Hydraulics.h"

class GreenHydraulics : public Hydraulics
{
public:
	GreenHydraulics();
	void applyBraking();
	//void displayStatus() const override;
};


#endif