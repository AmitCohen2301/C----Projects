#include "SecurityGuard.h"

// Constructor
SecurityGuard::SecurityGuard(const char* ticketNumber, const char* name, const Luggage* luggage, const int employeeID, const char* weapon) noexcept(false) : Customer(ticketNumber, name, luggage), Crew(employeeID, name), Human(name)
{
	this->weapon = new char[strlen(weapon) + 1];
	strcpy(this->weapon, weapon);
}

// Copy c'tor (there is dynamic alocation in class)
SecurityGuard::SecurityGuard(const SecurityGuard& securityGuard) : Customer(securityGuard), Crew(securityGuard), Human(securityGuard)
{
	this->weapon = new char[strlen(securityGuard.weapon) + 1];
	strcpy(this->weapon, securityGuard.weapon);
}

// Move c'tor (there is dynamic alocation in class)
SecurityGuard::SecurityGuard(SecurityGuard&& securityGuard) : Customer(securityGuard), Crew(securityGuard), Human(securityGuard)
{
	weapon = securityGuard.weapon;
	securityGuard.weapon = nullptr;
}

// Destructor (there is dynamic alocation in class)
SecurityGuard::~SecurityGuard()
{
	delete[] weapon;
}

// Gets
char* SecurityGuard::getWeapon() const // Get weapon
{
	return this->weapon;
}

// Sets
bool SecurityGuard::setWeapon(const char* weapon) // Set weapon
{
	if (weapon == NULL || weapon == nullptr || strlen(weapon) < MIN_CHARS_TO_WAPON)
		return false;
	char* allocationToNewWeapon = new char[strlen(weapon) + 1];
	if (allocationToNewWeapon == NULL) // Failed to give dynamic allocation to IATA
		return false;
	delete[] this->weapon; // Free the old weapon
	this->weapon = allocationToNewWeapon;
	strcpy(this->weapon, weapon);
	return true;
}

// To OS
void SecurityGuard::toOs(ostream& os) const
{
	os << ", Employee ID: " << this->employeeID
		<< ", Weapon: " << this->weapon
		<< ", Ticket number: " << this->ticketNumber;
	if (this->luggage != NULL || this->luggage == nullptr)
		os << "Luggage: volume = " << this->luggage->getVolume() << ", weight = " << this->luggage->getWeight();
	else
		os << "Luggage: no luggage";
}

// Operators
void SecurityGuard::operator=(const SecurityGuard& securityGuard) // Operator = (there is dynamic alocation in class)
{
	delete[] weapon;
	weapon = strdup(securityGuard.weapon);
}