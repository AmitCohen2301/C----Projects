#ifndef HUMAN_H
#define HUMAN_H

#pragma warning (disable : 4996)

#define MIN_CHARS_TO_HUMAN_NAME 1

#include <ostream>
#include <string>

using namespace std;

class Human 
{
protected:
	string name;

public:
	// Constructor
	Human(const string name) noexcept(false);

	// Gets
	string getName() const; // Get name

	// Sets
	bool setName(const string name); // Set name

	// To OS
	virtual void toOs(ostream& os) const = 0;

	// Operators
	friend ostream& operator<<(ostream& os, const Human& human); // Ostream
};

#endif // !HUMAN_H