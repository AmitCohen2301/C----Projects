#ifndef SECURITY_GUARD_H
#define SECURITY_GUARD_H

#pragma warning (disable : 4996)

#define MIN_CHARS_TO_WAPON 1

#include <string.h>
#include <string>
#include "Crew.h"
#include "Customer.h"

using namespace std;

class SecurityGuard : public Crew, public Customer, virtual public Human
{
private:
	string weapon;

public:
	// Constructor
	SecurityGuard(const string ticketNumber, const string name, const Luggage* luggage, const int employeeID, const string weapon) noexcept(false);

	// Gets
	string getWeapon() const; // Get weapon

	// Sets
	bool setWeapon(const string weapon); // Set weapon

	// To OS
	virtual void toOs(ostream& os) const override;
};

#endif // !SECURITY_GUARD_H