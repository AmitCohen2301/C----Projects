#include "Airport.h"

// Constructor
Airport::Airport(const char* codeOfIATA, const char* countryName) noexcept(false)
{
	this->codeOfIATA = nullptr;
	this->countryName = nullptr;
	if (setCodeOfIATA(codeOfIATA) == false) // Failed to set IATA
		throw "Failed to set code of IATA";
	if (setCountryName(countryName) == false) // Failed to set country name
		throw "Failed to set country name";
}

// Copy c'tor (there is dynamic alocation in class)
Airport::Airport(const Airport& airport)
{
	this->codeOfIATA = new char[strlen(airport.codeOfIATA) + 1];
	strcpy(this->codeOfIATA, airport.codeOfIATA);
	this->countryName = new char[strlen(airport.countryName) + 1];
	strcpy(this->countryName, airport.countryName);
}

// Move c'tor (there is dynamic alocation in class)
Airport::Airport(Airport&& airport)
{
	codeOfIATA = airport.codeOfIATA;
	airport.codeOfIATA = nullptr;
	countryName = airport.countryName;
	airport.countryName = nullptr;
}

// Destructor (there is dynamic alocation in class)
Airport::~Airport()
{
	delete[] codeOfIATA; // Free the code of IATA
	delete[] countryName; // Free the country name
}

// Gets
char* Airport::getCodeOfIATA() const // Get IATA
{
	return this->codeOfIATA;
}

char* Airport::getCountryName() const // Get country name
{
	return this->countryName;
}

// Sets
bool Airport::setCodeOfIATA(const char* codeOfIATA) // Set IATA
{
	if (codeOfIATA == NULL || codeOfIATA == nullptr || strlen(codeOfIATA) < MIN_CHARS_TO_IATA)
		return false;
	char* allocationToNewIATA = new char[strlen(codeOfIATA) + 1];
	if (allocationToNewIATA == NULL) // Failed to give dynamic allocation to IATA
		return false;
	delete[] this->codeOfIATA; // Free the old code of IATA
	this->codeOfIATA = allocationToNewIATA;
	strcpy(this->codeOfIATA, codeOfIATA);
	return true;
}

bool Airport::setCountryName(const char* countryName) // Set country name
{
	if (countryName == NULL || countryName == nullptr || strlen(countryName) < MIN_CHARS_TO_COUNTRY_NAME)
		return false;
	char* allocationToNewName = new char[strlen(countryName) + 1];
	if (allocationToNewName == NULL) // Failed to give dynamic allocation to name
		return false;
	delete[] this->countryName; // Free the old country name
	this->countryName = allocationToNewName;
	strcpy(this->countryName, countryName);
	return true;
}

// Operators
void Airport::operator=(const Airport& airport) // Operator = (there is dynamic alocation in class)
{
	delete[] codeOfIATA;
	codeOfIATA = strdup(airport.codeOfIATA);
	delete[] countryName;
	countryName = strdup(airport.countryName);
}