#ifndef BLUEHYDRAULICS_H
#define BLUEHYDRAULICS_H

#include "Hydraulics.h"

class BlueHydraulics : public Hydraulics
{
public:
	BlueHydraulics();
	void displayStatus() const override;
};


#endif // !1