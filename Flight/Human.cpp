#include "Human.h"

// Constructor
Human::Human(const char* name) noexcept(false)
{
	this->name = nullptr;
	if (setName(name) == false) // Failed to set human name
		throw "Failed to set human name";
}

// Copy c'tor (there is dynamic alocation in class)
Human::Human(const Human& human)
{
	this->name = new char[strlen(human.name) + 1];
	strcpy(this->name, human.name);
}

// Move c'tor (there is dynamic alocation in class)
Human::Human(Human&& human)
{
	name = human.name;
	human.name = nullptr;
}

// Destructor (there is dynamic alocation in class)
Human::~Human()
{
	delete[] name; // Free the human name
}

// Gets
char* Human::getName() const // Get name
{
	return this->name;
}

// Sets
bool Human::setName(const char* name) // Set name
{
	if (name == NULL || name == nullptr || strlen(name) < MIN_CHARS_TO_HUMAN_NAME)
		return false;
	char* allocationToNewName = new char[strlen(name) + 1];
	if (allocationToNewName == NULL) // Failed to give dynamic allocation to name
		return false;
	delete[] this->name; // Free the old human name
	this->name = allocationToNewName;
	strcpy(this->name, name);
	return true;
}

// Operators
void Human::operator=(const Human& human) // Operator = (there is dynamic alocation in class)
{
	delete[] name;
	name = strdup(human.name);
}

ostream& operator<<(ostream& os, const Human& human) // Ostream
{
	os << "Name: " << human.getName();
	human.toOs(os);
	os << endl;
	return os;
}
