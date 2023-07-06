#ifndef PLANE_H
#define PLANE_H

#pragma warning (disable : 4996)

#define ROWS_IN_PLANE 40
#define SEATS_PER_ROW 6
#define MIN_CHARS_TO_MODEL 1
#define DEFAULT_MODEL "No Model Name"

#include "Customer.h"
#include "Seat.h"
#include <iostream>

using namespace std;

class Plane
{
private:
	char* model;
	Seat* seats[ROWS_IN_PLANE][SEATS_PER_ROW];

public:
	// Constructors
	Plane() noexcept(false); // Empty constructor
	Plane(const char* model) noexcept(false); // Name constructor

	// Copy c'tor (there is dynamic alocation in class)
	Plane(const Plane& plane);

	// Move c'tor (there is dynamic alocation in class)
	Plane(Plane&& plane);

	// Destructor (there is dynamic alocation in class)
	~Plane();

	// Gets
	char* getModel() const; // Get model
	Seat* getSeatAt(const int row, const int col) const; // Get seat at

	// Sets
	bool setModel(const char* model); // Set model

	// Methods
	void showSeats() const; // Show seats
	Customer** getCustomers() const; // Get customers
	bool addCustomer(Customer* customer); // Add customer to first free place (or false if plane is full)
	bool addCustomer(Customer* customer, const int row, const int col); // Add customer to specific place (or false if place is occupied)
	bool removeCustomer(const Customer* customer); // Remove customer
	Customer* findCustomerByName(const char* name); // Find customer by name
	Customer* findCustomerBySeat(const int row, const int col); // Find customer by seat

	// Operators
	void operator=(const Plane& plane); // Operator = (there is dynamic alocation in class)
};

#endif // !PLANE_H