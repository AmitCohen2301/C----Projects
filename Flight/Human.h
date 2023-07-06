#ifndef HUMAN_H
#define HUMAN_H

#pragma warning (disable : 4996)

#define MIN_CHARS_TO_HUMAN_NAME 1

#include <ostream>

using namespace std;

class Human 
{
protected:
	char* name;

public:
	// Constructor
	Human(const char* name) noexcept(false);
	
	// Copy c'tor (there is dynamic alocation in class)
	Human(const Human& human);

	// Move c'tor (there is dynamic alocation in class)
	Human(Human&& human);

	// Destructor (there is dynamic alocation in class)
	virtual ~Human();

	// Gets
	char* getName() const; // Get name

	// Sets
	bool setName(const char* name); // Set name

	// To OS
	virtual void toOs(ostream& os) const = 0;

	// Operators
	void operator=(const Human& human); // Operator = (there is dynamic alocation in class)
	friend ostream& operator<<(ostream& os, const Human& human); // Ostream
};

#endif // !HUMAN_H