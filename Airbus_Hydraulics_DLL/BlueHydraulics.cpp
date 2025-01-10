#include "BlueHydraulics.h"

// Blue Hydraulics system
class BlueHydraulics : public Hydraulics
{
public:
	BlueHydraulics() : Hydraulics("Blue", 3000.0)
	{
	} // Default pressure: 3000 PSI

	void displayStatus() const override
	{
		std::cout << "[Blue System] ";
		Hydraulics::displayStatus();
	}
};