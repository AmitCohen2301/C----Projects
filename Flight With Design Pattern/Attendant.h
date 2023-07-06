#ifndef ATTENDANT_H
#define ATTENDANT_H

#pragma warning (disable : 4996)

#define MIN_FIRST_AID_KNOWLEDGE 1
#define MAX_FIRST_AID_KNOWLEDGE 10

#include <string>
#include "Crew.h"
#include "Luggage.h"

using namespace std;

class Attendant : public Crew
{
private:
	int firstAidKnowledge;
	Luggage* luggage;

public:
	// Constructor
	Attendant(const int employeeID, const string name, const int firstAidKnowledge, const Luggage* luggage) noexcept(false);

	// Copy c'tor (there is dynamic alocation in class)
	Attendant(const Attendant& attendant);

	// Move c'tor (there is dynamic alocation in class)
	Attendant(Attendant&& attendant);

	// Destructor (there is dynamic alocation in class)
	virtual ~Attendant();

	// Gets
	int getFirstAidKnowledge() const; // Get first aid knowledge
	Luggage* getLuggage() const; // Get luggage

	// Sets
	bool setFirstAidKnowledge(const int firstAidKnowledge); // Set first aid knowledge
	bool setLuggage(const Luggage* luggage); // Set luggage

	// Operators
	void operator=(const Attendant& attendant); // Operator = (there is dynamic alocation in class)
};

#endif // !ATTENDANT_H