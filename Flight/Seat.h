#ifndef SEAT_H
#define SEAT_H

#pragma warning (disable : 4996)

#include "Customer.h"

using namespace std;

class Seat
{
private:
	bool occupied;
	Customer* customer;

public:
	// Constructors
	Seat() noexcept(false); // Empty constructor
	Seat(Customer* customer) noexcept(false); // Customer constructor

	// Gets
	bool isOccupied() const; // Get occupied
	Customer* getCustomer() const; // Get customer

	// Methods
	bool sitCustomer(Customer* customer); // Sit customer

	// Operators
	bool operator==(Customer& customer) const; // Operator == with customer
	bool operator==(Seat& seat) const; // Operator == with seat
};

#endif // !SEAT_H