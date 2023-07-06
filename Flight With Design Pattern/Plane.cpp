#include "Plane.h"

// Constructors
Plane::Plane() noexcept(false) : Plane(DEFAULT_MODEL) {} // Empty constructor

Plane::Plane(const string model) noexcept(false) // Name constructor
{
	if (setModel(model) == false)
		throw "Failed to set model";
	seats = vector <vector <Seat>>(ROWS_IN_PLANE);
	for (int rowNo = 0; rowNo < ROWS_IN_PLANE; rowNo++)
		seats[rowNo] = vector <Seat>(SEATS_PER_ROW);
}

// Gets
string Plane::getModel() const // Get model
{
	return this->model;
}

Seat Plane::getSeatAt(const int row, const int col) const // Get seat at
{
	if (row > ROWS_IN_PLANE || row < 1 || col < 1 || col > SEATS_PER_ROW)
		return NULL;
	return this->seats[row - 1][col - 1];
}

// Sets
bool Plane::setModel(const string model) // Set model
{
	if (model.length() < MIN_CHARS_TO_MODEL)
		return false;
	this->model = model;
	return true;
}

// Methods
void Plane::showSeats() const // Show seats
{
	cout << "Seats:" << endl;
	for (int rowNum = 0; rowNum < ROWS_IN_PLANE; rowNum++) // Move on every row
	{
		cout << "Row " << rowNum + 1 << ":\t";
		for (int seatNum = 0; seatNum < SEATS_PER_ROW; seatNum++) // Move on every seat in row
		{
			if (this->seats[rowNum][seatNum].isOccupied()) // Seat is occupied
				cout << "[Customer: " << this->seats[rowNum][seatNum].getCustomer()->getName() << ", Ticket: " << this->seats[rowNum][seatNum].getCustomer()->getTicketNumber() << "]";
			else // Seat is free
				cout << "[seat " << seatNum + 1 << " is free]";
		}
		cout << endl;
	}
}

Customer** Plane::getCustomers() const // Get customers
{
	Customer** allCustomers = new Customer*[ROWS_IN_PLANE * SEATS_PER_ROW];
	int customerNo = 0;
	for (int rowNum = 0; rowNum < ROWS_IN_PLANE; rowNum++) // Move on every row
	{
		for (int seatNum = 0; seatNum < SEATS_PER_ROW; seatNum++) // Move on every seat in row
		{
			if (this->seats[rowNum][seatNum].isOccupied()) // Seat is occupied
			{
				allCustomers[customerNo] = this->seats[rowNum][seatNum].getCustomer();
				customerNo += 1;
			}
		}
	}
	return allCustomers;
}

bool Plane::addCustomer(Customer* customer) // Add customer to first free place (or false if plane is full)
{
	for (int rowNum = 0; rowNum < ROWS_IN_PLANE; rowNum++) // Move on every row
	{
		for (int seatNum = 0; seatNum < SEATS_PER_ROW; seatNum++) // Move on every seat in row
		{
			if (this->seats[rowNum][seatNum].isOccupied() == false) // Seat is not occupied
			{
				this->seats[rowNum][seatNum].sitCustomer(customer); // Put customer
				return true;
			}
		}
	}
	return false;
}

bool Plane::addCustomer(Customer* customer, const int row, const int col) // Add customer to specific place (or false if place is occupied)
{
	if (row < 1 || row > ROWS_IN_PLANE || col < 1 || col > SEATS_PER_ROW)
		return false;
	if (this->seats[row][col].isOccupied()) // Seat is occupied
		return false;
	this->seats[row - 1][col - 1].sitCustomer(customer);
	return true;
}

bool Plane::removeCustomer(const Customer* customer) // Remove customer
{
	for (int rowNum = 0; rowNum < ROWS_IN_PLANE; rowNum++) // Move on every row
	{
		for (int seatNum = 0; seatNum < SEATS_PER_ROW; seatNum++) // Move on every seat in row
		{
			if ((this->seats[rowNum][seatNum].isOccupied()) && (this->seats[rowNum][seatNum].getCustomer()->getName() == customer->getName()) && (this->seats[rowNum][seatNum].getCustomer()->getTicketNumber() == customer->getTicketNumber()))
			{
				this->seats[rowNum][seatNum] = Seat();
				return true;
			}
		}
	}
	return false;
}

Customer* Plane::findCustomerByName(const string name) // Find customer by name
{
	for (int rowNum = 0; rowNum < ROWS_IN_PLANE; rowNum++) // Move on every row
	{
		for (int seatNum = 0; seatNum < SEATS_PER_ROW; seatNum++) // Move on every seat in row
		{
			if ((this->seats[rowNum][seatNum].isOccupied()) && (this->seats[rowNum][seatNum].getCustomer()->getName() == name))
				return this->seats[rowNum][seatNum].getCustomer();
		}
	}
	return NULL;
}

Customer* Plane::findCustomerBySeat(const int row, const int col) // Find customer by seat
{
	if (row < 1 || row > ROWS_IN_PLANE || col < 1 || col > SEATS_PER_ROW)
		return NULL;
	if (seats[row][col].isOccupied())
		return seats[row][col].getCustomer();
	return NULL;
}