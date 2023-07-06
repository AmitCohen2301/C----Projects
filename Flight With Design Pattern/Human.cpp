#include "Human.h"

// Constructor
Human::Human(const string name) noexcept(false)
{
	if (setName(name) == false) // Failed to set human name
		throw "Failed to set human name";
}

// Gets
string Human::getName() const // Get name
{
	return this->name;
}

// Sets
bool Human::setName(const string name) // Set name
{
	if (name.length() < MIN_CHARS_TO_HUMAN_NAME)
		return false;
	this->name = name;
	return true;
}

// Operators
ostream& operator<<(ostream& os, const Human& human) // Ostream
{
	os << "Name: " << human.getName();
	human.toOs(os);
	os << endl;
	return os;
}
