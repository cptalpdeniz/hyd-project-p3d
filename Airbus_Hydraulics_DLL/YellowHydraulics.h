#ifndef YELLOWHYDRAULICS_H
#define YELLOWHYDRAULICS_H

#include "Hydraulics.h"

class YellowHydraulics : public Hydraulics
{
public:
	YellowHydraulics();
	void displayStatus() const override;
};


#endif // !1