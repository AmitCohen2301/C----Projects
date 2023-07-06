#ifndef AIRPORT_H
#define AIRPORT_H

#pragma warning (disable : 4996)

#define MIN_CHARS_TO_IATA 1
#define MIN_CHARS_TO_COUNTRY_NAME 1

#include <string.h>
#include <string>

using namespace std;

class Airport
{
private:
	string codeOfIATA;
	string countryName;

public:
	// Constructor
	Airport(const string codeOfIATA, const string countryName) noexcept(false);

	// Gets
	string getCodeOfIATA() const; // Get IATA
	string getCountryName() const; // Get country name

	// Sets
	bool setCodeOfIATA(const string codeOfIATA); // Set IATA
	bool setCountryName(const string countryName); // Set country name
};

#endif // !AIRPORT_H