#ifndef CREW_H
#define CREW_H

#pragma warning (disable : 4996)

#define MIN_NUM_TO_EMPLOYEE_ID 1

#include <stdio.h>
#include <string.h>
#include "Human.h"

using namespace std;

class Crew : virtual public Human
{
protected:
	int employeeID;

	// Constructor (in 'protected' in order to make the class abstract)
	Crew(const int employeeID, const char* name) noexcept(false);

public:
	// Gets
	int getEmployeeID() const; // Get employee ID

	// Sets
	bool setEmployeeID(const int employeeID); // Set employee ID

	// To OS
	virtual void toOs(ostream& os) const override;
};

#endif // !CREW_H