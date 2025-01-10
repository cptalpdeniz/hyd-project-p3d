#include "GreenHydraulics.h"


GreenHydraulics::GreenHydraulics() : Hydraulics("Green", 3000.0)
{
} // Default pressure: 3000 PSI

void GreenHydraulics::displayStatus() const
{
	std::cout << "[Green System] ";
	Hydraulics::displayStatus();
}

void GreenHydraulics::applyBraking()
{

}
