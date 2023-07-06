#ifndef SECURITY_GUARD_H
#define SECURITY_GUARD_H

#pragma warning (disable : 4996)

#define MIN_CHARS_TO_WAPON 1

#include "Crew.h"
#include "Customer.h"
#include <string.h>

using namespace std;

class SecurityGuard : public Crew, public Customer, virtual public Human
{
private:
	char* weapon;

public:
	// Constructor
	SecurityGuard(const char* ticketNumber, const char* name, const Luggage* luggage, const int employeeID, const char* weapon) noexcept(false);

	// Copy c'tor (there is dynamic alocation in class)
	SecurityGuard(const SecurityGuard& securityGuard);

	// Move c'tor (there is dynamic alocation in class)
	SecurityGuard(SecurityGuard&& securityGuard);

	// Destructor (there is dynamic alocation in class)
	~SecurityGuard();

	// Gets
	char* getWeapon() const; // Get weapon

	// Sets
	bool setWeapon(const char* weapon); // Set weapon

	// To OS
	virtual void toOs(ostream& os) const override;

	// Operators
	void operator=(const SecurityGuard& securityGuard); // Operator = (there is dynamic alocation in class)
};

#endif // !SECURITY_GUARD_H