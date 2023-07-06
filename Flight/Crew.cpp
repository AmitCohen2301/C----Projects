#include "Crew.h"

// Constructor (in 'protected' in order to make the class abstract)
Crew::Crew(const int employeeID, const char* name) noexcept(false) : Human(name)
{
	if (setEmployeeID(employeeID) == false)
		throw "Failed to set employee ID";
}

// Gets
int Crew::getEmployeeID() const // Get employee ID
{
	return this->employeeID;
}

// Sets
bool Crew::setEmployeeID(const int employeeID) // Set employee ID
{
	if (employeeID < MIN_NUM_TO_EMPLOYEE_ID)
		return false;
	this->employeeID = employeeID;
	return true;
}

// To OS
void Crew ::toOs(ostream& os) const
{
	os << ", Employee ID: " << this->employeeID;
}