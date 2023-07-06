#include "Customer.h"

// Constructor
Customer::Customer(const char* ticketNumber, const char* name, const Luggage* luggage) noexcept(false) : Human(name)
{
	this->ticketNumber = nullptr;
	this->luggage = nullptr;
	if (setTicketNumber(ticketNumber) == false)
		throw "Failed to set ticket number";
	if (setLuggage(luggage) == false)
		throw "Failed to set customer luggage";
}

// Copy c'tor (there is dynamic alocation in class)
Customer::Customer(const Customer& customer) : Human(customer)
{
	this->ticketNumber = new char[strlen(customer.ticketNumber) + 1];
	strcpy(this->ticketNumber, customer.ticketNumber);
	if (customer.luggage == NULL || customer.luggage == nullptr)
		luggage = nullptr;
	else
		luggage = new Luggage(customer.luggage->getWeight(), customer.luggage->getVolume());
}

// Move c'tor (there is dynamic alocation in class)
Customer::Customer(Customer&& customer) : Human(customer)
{
	ticketNumber = customer.ticketNumber;
	customer.ticketNumber = nullptr;
	luggage = customer.luggage;
	customer.luggage = nullptr;
}

// Destructor (there is dynamic alocation in class)
Customer::~Customer()
{
	delete[] ticketNumber; // Free the ticket number
	delete luggage; // Free the luggage
}

// Gets
char* Customer::getTicketNumber() const // Get ticket number
{
	return ticketNumber;
}

Luggage* Customer::getLuggage() const // Get luggage
{
	return luggage;
}

// Sets
bool Customer::setTicketNumber(const char* ticketNumber) // Set ticket number
{
	if (ticketNumber == NULL || ticketNumber == nullptr || strlen(ticketNumber) < MIN_CHARS_TO_TICKET_NUMBER)
		return false;
	char* allocationToNewTicketNumber = new char[strlen(ticketNumber) + 1];
	if (allocationToNewTicketNumber == NULL) // Failed to give dynamic allocation to ticket number
		return false;
	delete[] this->ticketNumber; // Free the old ticket number
	this->ticketNumber = allocationToNewTicketNumber;
	strcpy(this->ticketNumber, ticketNumber);
	return true;
}

bool Customer::setLuggage(const Luggage* luggage) // Set luggage
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

// To OS
void Customer::toOs(ostream& os) const
{
	os << ", Ticket number: " << this->ticketNumber;
	if (this->luggage != NULL || this->luggage == nullptr)
		os << ", Luggage: volume = " << this->luggage->getVolume() << ", weight = " << this->luggage->getWeight();
	else
		os << ", Luggage: no luggage";
}

// Operators
void Customer::operator=(const Customer& customer) // Operator = (there is dynamic alocation in class)
{
	delete[] ticketNumber;
	ticketNumber = strdup(customer.ticketNumber);
	delete luggage;
	luggage = customer.luggage;
}