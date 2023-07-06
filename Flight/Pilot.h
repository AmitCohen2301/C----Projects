#ifndef PILOT_H
#define PILOT_H

#pragma warning (disable : 4996)

#define MIN_LICENSE_NUMBER 1

#include "Crew.h"

using namespace std;

class Pilot : public Crew
{
private:
	int licenseNumber;

public:
	// Constructor
	Pilot(const int employeeID, const char* name, const int licenseNumber) noexcept(false);

	// Destructor (inheritance)
	virtual ~Pilot();

	// Gets
	int getLicenseNumber() const; // Get license number

	// Sets
	bool setLicenseNumber(const int licenseNumber); // Set license number
};

#endif // !PILOT_H