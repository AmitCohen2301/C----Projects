#include "Airport.h"

// Constructor
Airport::Airport(const string codeOfIATA, const string countryName) noexcept(false)
{
	if (setCodeOfIATA(codeOfIATA) == false) // Failed to set IATA
		throw "Failed to set code of IATA";
	if (setCountryName(countryName) == false) // Failed to set country name
		throw "Failed to set country name";
}

// Gets
string Airport::getCodeOfIATA() const // Get IATA
{
	return this->codeOfIATA;
}

string Airport::getCountryName() const // Get country name
{
	return this->countryName;
}

// Sets
bool Airport::setCodeOfIATA(const string codeOfIATA) // Set IATA
{
	if (codeOfIATA.length() < MIN_CHARS_TO_IATA)
		return false;
	this->codeOfIATA = codeOfIATA;
	return true;
}

bool Airport::setCountryName(const string countryName) // Set country name
{
	if (countryName.length() < MIN_CHARS_TO_COUNTRY_NAME)
		return false;
	this->countryName = countryName;
	return true;
}