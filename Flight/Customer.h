#ifndef CUSTOMER_H
#define CUSTOMER_H

#pragma warning (disable : 4996)

#define MIN_CHARS_TO_TICKET_NUMBER 1

#include <string.h>
#include "Human.h"
#include "Luggage.h"

using namespace std;

class Customer : virtual public Human
{
protected:
	char* ticketNumber; // NOT NECCESSRILY A NUMBER, can be 'y7xu2mm54' for example
	Luggage* luggage;

public:
	// Constructor
	Customer(const char* ticketNumber, const char* name, const Luggage* luggage) noexcept(false);

	// Copy c'tor (there is dynamic alocation in class)
	Customer(const Customer& customer);

	// Move c'tor (there is dynamic alocation in class)
	Customer(Customer&& customer);

	// Destructor (there is dynamic alocation in class)
	virtual ~Customer();

	// Gets
	char* getTicketNumber() const; // Get ticket number
	Luggage* getLuggage() const; // Get luggage

	// Sets
	bool setTicketNumber(const char* ticketNumber); // Set ticket number
	bool setLuggage(const Luggage* luggage); // Set luggage

	// To OS
	virtual void toOs(ostream& os) const override;

	// Operators
	void operator=(const Customer& customer); // Operator = (there is dynamic alocation in class)
};

#endif // !CUSTOMER_H