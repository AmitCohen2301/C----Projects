#include "Plane.h"

// Constructors
Plane::Plane() noexcept(false) : Plane(DEFAULT_MODEL) {} // Empty constructor

Plane::Plane(const char* model) noexcept(false) // Name constructor
{
	if (setModel(model) == false)
		throw "Failed to set model";
	for (int i = 0; i < ROWS_IN_PLANE; i++)
		for (int j = 0; j < SEATS_PER_ROW; j++)
			seats[i][j] = new Seat();
}

// Copy c'tor (there is dynamic alocation in class)
Plane::Plane(const Plane& plane)
{
	this->model = new char[strlen(plane.model) + 1];
	strcpy(this->model, plane.model);
	for (int rowNum = 0; rowNum < ROWS_IN_PLANE; rowNum++) // Move on every row
	{
		for (int colNum = 0; colNum < SEATS_PER_ROW; colNum++) // Move on every seat in row
		{
			if (plane.getSeatAt(rowNum + 1, colNum + 1)->isOccupied())
				seats[rowNum][colNum] = new Seat(plane.getSeatAt(rowNum + 1, colNum + 1)->getCustomer());
			else
				seats[rowNum][colNum] = new Seat();
		}
	}
}

// Move c'tor (there is dynamic alocation in class)
Plane::Plane(Plane&& plane)
{
	model = plane.model;
	plane.model = nullptr;
	for (int rowNum = 0; rowNum < ROWS_IN_PLANE; rowNum++) // Move on every row
		for (int colNum = 0; colNum < SEATS_PER_ROW; colNum++) // Move on every seat in row
			seats[rowNum][colNum] = plane.getSeatAt(rowNum + 1, colNum + 1);
}

// Destructor (there is dynamic alocation in class)
Plane::~Plane()
{
	for (int rowNum = 0; rowNum < ROWS_IN_PLANE; rowNum++)
		for (int colNum = 0; colNum < SEATS_PER_ROW; colNum++)
			delete seats[rowNum][colNum];
	delete[] model;
}

// Gets
char* Plane::getModel() const // Get model
{
	return this->model;
}

Seat* Plane::getSeatAt(const int row, const int col) const // Get seat at
{
	if (row > ROWS_IN_PLANE || row < 1 || col < 1 || col > SEATS_PER_ROW)
		return NULL;
	return seats[row - 1][col - 1];
}

// Sets
bool Plane::setModel(const char* model) // Set model
{
	if (model == NULL || model == nullptr || strlen(model) < MIN_CHARS_TO_MODEL)
		return false;
	char* allocationToNewModel = new char[strlen(model) + 1];
	if (allocationToNewModel == NULL) // Failed to give dynamic allocation to ticket number
		return false;
	delete[] this->model; // Free the old model
	this->model = allocationToNewModel;
	strcpy(this->model, model);
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
			if (this->seats[rowNum][seatNum]->isOccupied()) // Seat is occupied
				cout << "[Customer: " << this->seats[rowNum][seatNum]->getCustomer()->getName() << ", Ticket: " << this->seats[rowNum][seatNum]->getCustomer()->getTicketNumber() << "]";
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
			if (this->seats[rowNum][seatNum]->isOccupied()) // Seat is occupied
			{
				allCustomers[customerNo] = this->seats[rowNum][seatNum]->getCustomer();
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
			if (this->seats[rowNum][seatNum]->isOccupied() == false) // Seat is not occupied
			{
				this->seats[rowNum][seatNum]->sitCustomer(customer); // Put customer
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
	if (this->seats[row][col]->isOccupied()) // Seat is occupied
		return false;
	this->seats[row - 1][col - 1]->sitCustomer(customer);
	return true;
}

bool Plane::removeCustomer(const Customer* customer) // Remove customer
{
	for (int rowNum = 0; rowNum < ROWS_IN_PLANE; rowNum++) // Move on every row
	{
		for (int seatNum = 0; seatNum < SEATS_PER_ROW; seatNum++) // Move on every seat in row
		{
			if ((this->seats[rowNum][seatNum]->isOccupied()) && (strcmp(this->seats[rowNum][seatNum]->getCustomer()->getName(), customer->getName()) == 0) && (strcmp(this->seats[rowNum][seatNum]->getCustomer()->getTicketNumber(), customer->getTicketNumber()) == 0))
			{
				this->seats[rowNum][seatNum] = new Seat();
				return true;
			}
		}
	}
	return false;
}

Customer* Plane::findCustomerByName(const char* name) // Find customer by name
{
	for (int rowNum = 0; rowNum < ROWS_IN_PLANE; rowNum++) // Move on every row
	{
		for (int seatNum = 0; seatNum < SEATS_PER_ROW; seatNum++) // Move on every seat in row
		{
			if ((this->seats[rowNum][seatNum]->isOccupied()) && (strcmp(this->seats[rowNum][seatNum]->getCustomer()->getName(), name) == 0))
				return this->seats[rowNum][seatNum]->getCustomer();
		}
	}
	return NULL;
}

Customer* Plane::findCustomerBySeat(const int row, const int col) // Find customer by seat
{
	if (row < 1 || row > ROWS_IN_PLANE || col < 1 || col > SEATS_PER_ROW)
		return NULL;
	if (seats[row][col]->isOccupied())
		return seats[row][col]->getCustomer();
	return NULL;
}

// Operators
void Plane::operator=(const Plane& plane) // Operator = (there is dynamic alocation in class)
{
	delete[] model;
	model = strdup(plane.model);
	for (int rowNum = 0; rowNum < ROWS_IN_PLANE; rowNum++)
		for (int colNum = 0; colNum < ROWS_IN_PLANE; colNum++)
			delete seats[rowNum][colNum];
	for (int rowNum = 0; rowNum < ROWS_IN_PLANE; rowNum++) // Move on every row
	{
		for (int colNum = 0; colNum < SEATS_PER_ROW; colNum++) // Move on every seat in row
		{
			if (plane.getSeatAt(rowNum + 1, colNum + 1)->isOccupied())
				seats[rowNum][colNum] = new Seat(plane.getSeatAt(rowNum + 1, colNum + 1)->getCustomer());
			else
				seats[rowNum][colNum] = new Seat();
		}
	}
}