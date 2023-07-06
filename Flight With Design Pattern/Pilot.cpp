#include "Pilot.h"

// Constructor
Pilot::Pilot(const int employeeID, const string name, const int licenseNumber) noexcept(false) : Crew(employeeID, name), Human(name)
{
	if (setLicenseNumber(licenseNumber) == false)
		throw "Failed to set license number";
}

// Destructor (inheritance)
Pilot::~Pilot() {}

// Gets
int Pilot::getLicenseNumber() const // Get license number
{
	return licenseNumber;
}

// Sets
bool Pilot::setLicenseNumber(const int licenseNumber) // Set license number
{
	if (licenseNumber < MIN_LICENSE_NUMBER)
		return false;
	this->licenseNumber = licenseNumber;
	return true;
}