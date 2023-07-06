#include "SecurityGuard.h"

// Constructor
SecurityGuard::SecurityGuard(const string ticketNumber, const string name, const Luggage* luggage, const int employeeID, const string weapon) noexcept(false) : Customer(ticketNumber, name, luggage), Crew(employeeID, name), Human(name)
{
	if(setWeapon(weapon) == false)
		throw "Failed to set weapon";
}

// Gets
string SecurityGuard::getWeapon() const // Get weapon
{
	return this->weapon;
}

// Sets
bool SecurityGuard::setWeapon(const string weapon) // Set weapon
{
	if (weapon.length() < MIN_CHARS_TO_WAPON)
		return false;
	this->weapon = weapon;
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