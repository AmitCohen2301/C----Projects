#include "Attendant.h"

// Constructor
Attendant::Attendant(const int employeeID, const char* name, const int firstAidKnowledge, const Luggage* luggage) noexcept(false) : Crew(employeeID, name), Human(name)
{
	this->luggage = nullptr;
	if (setFirstAidKnowledge(firstAidKnowledge) == false)
		throw "Failed to set first aid knowledge";
	if (setLuggage(luggage) == false)
		throw "Failed to set attendant luggage";
}

// Copy c'tor (there is dynamic alocation in class)
Attendant::Attendant(const Attendant& attendant) : Crew(attendant), Human(attendant)
{
	firstAidKnowledge = attendant.firstAidKnowledge;
	if (attendant.luggage == NULL || attendant.luggage == nullptr)
		luggage = nullptr;
	else
		luggage = new Luggage(attendant.luggage->getWeight(), attendant.luggage->getVolume());
}

// Move c'tor (there is dynamic alocation in class)
Attendant::Attendant(Attendant&& attendant) : Crew(attendant), Human(attendant)
{
	firstAidKnowledge = attendant.firstAidKnowledge;
	luggage = attendant.luggage;
	attendant.luggage = nullptr;
}

// Destructor (there is dynamic alocation in class)
Attendant::~Attendant()
{
	delete luggage; // Free the luggage
}

// Gets
int Attendant::getFirstAidKnowledge() const // Get first aid knowledge
{
	return this->firstAidKnowledge;
}

Luggage* Attendant::getLuggage() const // Get luggage
{
	return this->luggage;
}

// Sets
bool Attendant::setFirstAidKnowledge(const int firstAidKnowledge) // Set first aid knowledge
{
	if (firstAidKnowledge > MAX_FIRST_AID_KNOWLEDGE || firstAidKnowledge < MIN_FIRST_AID_KNOWLEDGE) // Check the validity of first aid knowledge
		return false;
	this->firstAidKnowledge = firstAidKnowledge;
	return true;
}

bool Attendant::setLuggage(const Luggage* luggage) // Set luggage
{
	if (luggage == NULL || luggage == nullptr) // No luggage
	{
		delete this->luggage; // Free the old luggage
		this->luggage = nullptr;
		return true;
	}
	Luggage* newLuggage = new Luggage(luggage->getWeight(), luggage->getVolume());
	if (newLuggage == NULL) // Failed to give dynamic allocation to luggage
		return false;
	delete this->luggage; // Free the old luggage
	this->luggage = newLuggage;
	return true;
}

// Operators
void Attendant::operator=(const Attendant& attendant) // Operator = (there is dynamic alocation in class)
{
	firstAidKnowledge = attendant.firstAidKnowledge;
	delete luggage;
	luggage = attendant.luggage;
}