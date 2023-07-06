#ifndef AIRPORT_H
#define AIRPORT_H

#pragma warning (disable : 4996)

#define MIN_CHARS_TO_IATA 1
#define MIN_CHARS_TO_COUNTRY_NAME 1

#include <string.h>

using namespace std;

class Airport
{
private:
	char* codeOfIATA;
	char* countryName;

public:
	// Constructor
	Airport(const char* codeOfIATA, const char* countryName) noexcept(false);

	// Copy c'tor (there is dynamic alocation in class)
	Airport(const Airport& airport);

	// Move c'tor (there is dynamic alocation in class)
	Airport(Airport&& airport);

	// Destructor (there is dynamic alocation in class)
	~Airport();

	// Gets
	char* getCodeOfIATA() const; // Get IATA
	char* getCountryName() const; // Get country name

	// Sets
	bool setCodeOfIATA(const char* codeOfIATA); // Set IATA
	bool setCountryName(const char* countryName); // Set country name

	// Operators
	void operator=(const Airport& airport); // Operator = (there is dynamic alocation in class)
};

#endif // !AIRPORT_H