#include "YellowHydraulics.h"

// Yellow Hydraulics system
class YellowHydraulics : public Hydraulics
{
public:
	YellowHydraulics() : Hydraulics("Yellow", 3000.0)
	{
	} // Default pressure: 3000 PSI

	void displayStatus() const override
	{
		std::cout << "[Yellow System] ";
		Hydraulics::displayStatus();
	}
};