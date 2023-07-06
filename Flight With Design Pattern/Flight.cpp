#include "Flight.h"

Flight* Flight::flightInstance = nullptr;

using namespace std;

// Constructors
Flight::Flight() noexcept(false)
{
	this->plane = new Plane();
	this->sourceAirport = nullptr;
	this->destinationAirport = nullptr;
	this->takeoffTime = new tm();
	this->landingTime = new tm();
	this->mainPilot = nullptr;
	this->coPilot = nullptr;
	this->securityGuard1 = nullptr;
	this->securityGuard2 = nullptr;
	this->currentNumberOfAttendants = 0;
}

Flight::Flight(const Airport* sourceAirport, const Airport* destinationAirport) noexcept(false)
{
	this->plane = new Plane();
	this->sourceAirport = nullptr;
	this->destinationAirport = nullptr;
	this->takeoffTime = new tm();
	this->landingTime = new tm();
	this->mainPilot = nullptr;
	this->coPilot = nullptr;
	this->securityGuard1 = nullptr;
	this->securityGuard2 = nullptr;
	this->currentNumberOfAttendants = 0;
	if (setSourceAirport(sourceAirport) == false)
		throw "Failed to set source airport";
	if (setDestinationAirport(destinationAirport) == false)
		throw "Failed to set destination airport";
}

// Copy c'tor (there is dynamic alocation in class)
Flight::Flight(const Flight& flight)
{
	// Copy plane
	plane = new Plane(flight.plane->getModel());
	// Copy source airport
	sourceAirport = new Airport(flight.sourceAirport->getCodeOfIATA(), flight.sourceAirport->getCountryName());
	// Copy destination airport
	destinationAirport = new Airport(flight.destinationAirport->getCodeOfIATA(), flight.destinationAirport->getCountryName());
	// Copy takeoff time
	memcpy(takeoffTime, flight.takeoffTime, sizeof(tm));
	// Copy landing time
	memcpy(landingTime, flight.landingTime, sizeof(tm));
	// Copy main pilot
	if (flight.mainPilot != NULL && flight.mainPilot != nullptr)
		mainPilot = new Pilot(flight.mainPilot->getEmployeeID(), flight.mainPilot->getName(), flight.mainPilot->getLicenseNumber());
	else
		mainPilot = nullptr;
	// Copy co pilot
	if (flight.coPilot != NULL && flight.coPilot != nullptr)
		coPilot = new Pilot(flight.coPilot->getEmployeeID(), flight.coPilot->getName(), flight.coPilot->getLicenseNumber());
	else
		coPilot = nullptr;
	// Copy security guard 1
	if (flight.securityGuard1 != NULL && flight.securityGuard1 != nullptr)
		securityGuard1 = new SecurityGuard(flight.securityGuard1->getTicketNumber(), flight.securityGuard1->getName(), flight.securityGuard1->getLuggage(), flight.securityGuard1->getEmployeeID(), flight.securityGuard1->getWeapon());
	else
		securityGuard1 = nullptr;
	// Copy security guard 2
	if (flight.securityGuard2 != NULL && flight.securityGuard2 != nullptr)
		securityGuard2 = new SecurityGuard(flight.securityGuard2->getTicketNumber(), flight.securityGuard2->getName(), flight.securityGuard2->getLuggage(), flight.securityGuard2->getEmployeeID(), flight.securityGuard2->getWeapon());
	else
		securityGuard2 = nullptr;
	// Copy attendants list
	for (int attendantNum = 0; attendantNum < flight.currentNumberOfAttendants; attendantNum++)
	{
		Attendant* currentAttendant = flight.attendantsList.getDataInIndex(attendantNum)->getData();
		Attendant* attendant = new Attendant(currentAttendant->getEmployeeID(), currentAttendant->getName(), currentAttendant->getFirstAidKnowledge(), currentAttendant->getLuggage());
		attendantsList.insert(attendant);
	}
		//attendantsList.insert(flight.getAttendantsList().getDataInIndex(attendantNum)->getData()); // Copy attendant
	// Copy current number of attendants
	currentNumberOfAttendants = flight.currentNumberOfAttendants;
}

// Move c'tor (there is dynamic alocation in class)
Flight::Flight(Flight&& flight)
{
	plane = flight.plane; // Move plane
	flight.plane = nullptr;
	sourceAirport = flight.sourceAirport; // Move source airport
	flight.sourceAirport = nullptr;
	destinationAirport = flight.destinationAirport; // Move destination airport
	flight.destinationAirport = nullptr;
	takeoffTime = flight.takeoffTime; // Move takeoff time
	flight.takeoffTime = nullptr;
	landingTime = flight.landingTime; // Move landing time
	flight.landingTime = nullptr;
	mainPilot = flight.mainPilot; // Move main pilot
	flight.mainPilot = nullptr;
	coPilot = flight.coPilot; // Move co pilot
	flight.coPilot = nullptr;
	securityGuard1 = flight.securityGuard1; // Move security guard 1
	flight.securityGuard1 = nullptr;
	securityGuard2 = flight.securityGuard2; // Move security guard 2
	flight.securityGuard2 = nullptr;
	attendantsList = move(flight.attendantsList); // Move attendants list
	currentNumberOfAttendants = flight.currentNumberOfAttendants; // Move current number of attendants
}

// Destructor (there is dynamic alocation in class)
Flight::~Flight()
{
	delete this->plane;
	delete this->sourceAirport;
	delete this->destinationAirport;
	delete this->takeoffTime;
	delete this->landingTime;
	delete this->mainPilot;
	delete this->coPilot;
	delete this->securityGuard1;
	delete this->securityGuard2;
	delete &(this->attendantsList);
}

// Gets
Flight* Flight::getInstance() // Get instance (Singleton)
{
	if (flightInstance == nullptr)
		flightInstance = new Flight();
	return flightInstance;
}

Plane* Flight::getPlane() const // Get plane
{
	return this->plane;
}

Airport* Flight::getSourceAirport() const // Get source airport
{
	return this->sourceAirport;
}

Airport* Flight::getDestinationAirport() const // Get destination airport
{
	return this->destinationAirport;
}

tm* Flight::getTakeoffTime() const // Get takeoff time
{
	return this->takeoffTime;
}

tm* Flight::getLandingTime() const // Get landing time
{
	return this->landingTime;
}

Pilot* Flight::getMainPilot() const // Get main pilot
{
	return this->mainPilot;
}

Pilot* Flight::getCoPilot() const // Get co pilot
{
	return this->coPilot;
}

SecurityGuard* Flight::getSecurityGuard1() const // Get security gurad 1
{
	return this->securityGuard1;
}

SecurityGuard* Flight::getSecurityGuard2() const // Get security gurad 2
{
	return this->securityGuard2;
}

LinkedList<Attendant*> Flight::getAttendantsList() const // Get attendants list
{
	return this->attendantsList;
}

int Flight::getCurrentNumberOfAttendants() const // Get current number of attendants
{
	return this->currentNumberOfAttendants;
}

// Sets
bool Flight::setPlane(const Plane* plane) // Set plane
{
	if (plane == NULL || plane == nullptr)
		return false;
	Plane* newPlane = new Plane(plane->getModel());
	if (newPlane == NULL) // Failed to give dynamic allocation to plane
		return false;
	delete this->plane; // Free the old plane
	this->plane = newPlane;
	return true;
}

bool Flight::setSourceAirport(const Airport* sourceAirport) // Set source airport
{
	if (sourceAirport == NULL || sourceAirport == nullptr)
		return false;
	Airport* newSourceAirport = new Airport(sourceAirport->getCodeOfIATA(), sourceAirport->getCountryName());
	if (newSourceAirport == NULL) // Failed to give dynamic allocation to source airport
		return false;
	delete this->sourceAirport; // Free the old source airport
	this->sourceAirport = newSourceAirport;
	return true;
}

bool Flight::setDestinationAirport(const Airport* destinationAirport) // Set destination airport
{
	if (destinationAirport == NULL || destinationAirport == nullptr)
		return false;
	Airport* newDestinationAirport = new Airport(destinationAirport->getCodeOfIATA(), destinationAirport->getCountryName());
	if (newDestinationAirport == NULL) // Failed to give dynamic allocation to destination airport
		return false;
	delete this->destinationAirport; // Free the old destination airport
	this->destinationAirport = newDestinationAirport;
	return true;
}

bool Flight::setTakeoffTime(const tm* takeoffTime) // Set takeoff time
{
	if (takeoffTime == NULL || takeoffTime == nullptr)
		return false;
	memcpy(this->takeoffTime, takeoffTime, sizeof(tm));
	return true;
}

bool Flight::setLandingTime(const tm* landingTime) // Set landing time
{
	if (landingTime == NULL || landingTime == nullptr)
		return false;
	memcpy(this->landingTime, landingTime, sizeof(tm));
	return true;
}

bool Flight::setMainPilot(const Pilot* mainPilot) // Set main pilot
{
	if (mainPilot == NULL || mainPilot == nullptr)
		return false;
	Pilot* newMainPilot = new Pilot(mainPilot->getEmployeeID(), mainPilot->getName(), mainPilot->getLicenseNumber());
	if (newMainPilot == NULL) // Failed to give dynamic allocation to main pilot
		return false;
	delete this->mainPilot; // Free the old main pilot
	this->mainPilot = newMainPilot;
	return true;
}

bool Flight::setCoPilot(const Pilot* coPilot) // Set co pilot
{
	if (coPilot == NULL || coPilot == nullptr)
		return false;
	Pilot* newCoPilot = new Pilot(coPilot->getEmployeeID(), coPilot->getName(), coPilot->getLicenseNumber());
	if (newCoPilot == NULL) // Failed to give dynamic allocation to co pilot
		return false;
	delete this->coPilot; // Free the old co pilot
	this->coPilot = newCoPilot;
	return true;
}

bool Flight::setSecurityGuard1(const SecurityGuard* securityGuard1) // Set security guard 1
{
	if (securityGuard1 == NULL || securityGuard1 == nullptr)
		return false;
	SecurityGuard* newSecurityGuard = new SecurityGuard(securityGuard1->getTicketNumber(), securityGuard1->getName(), securityGuard1->getLuggage(), securityGuard1->getEmployeeID(), securityGuard1->getWeapon());
	if (newSecurityGuard == NULL) // Failed to give dynamic allocation to security guard 1
		return false;
	delete this->securityGuard1; // Free the old co security guard 1
	this->securityGuard1 = newSecurityGuard;
	return true;
}

bool Flight::setSecurityGuard2(const SecurityGuard* securityGuard2) // Set security guard 2
{
	if (securityGuard2 == NULL || securityGuard2 == nullptr)
		return false;
	SecurityGuard* newSecurityGuard = new SecurityGuard(securityGuard2->getTicketNumber(), securityGuard2->getName(), securityGuard2->getLuggage(), securityGuard2->getEmployeeID(), securityGuard2->getWeapon());
	if (newSecurityGuard == NULL) // Failed to give dynamic allocation to security guard 2
		return false;
	delete this->securityGuard2; // Free the old co security guard 2
	this->securityGuard2 = newSecurityGuard;
	return true;
}

// Pilot Methods
bool Flight::addMainPilot(const Pilot* mainPilot) // Add main pilot
{
	if (mainPilot == NULL || mainPilot == nullptr)
		return false;
	return setMainPilot(mainPilot);
}

bool Flight::addCoPilot(const Pilot* coPilot) // Add co pilot
{
	if (coPilot == NULL || coPilot == nullptr)
		return false;
	return setCoPilot(coPilot);
}

bool Flight::removeMainPilot() // Remove main pilot
{
	delete mainPilot;
	mainPilot = nullptr;
	return true;
}

bool Flight::removeCoPilot() // Remove co pilot
{
	delete coPilot;
	coPilot = nullptr;
	return true;
}

// Attendant Methods
Attendant* Flight::getAttendantAtPos(const int position) const // Get attendant at pos
{
	if (position > currentNumberOfAttendants || position < 1)
		return NULL;
	return this->attendantsList.getDataInIndex(position - 1)->getData();
}

bool Flight::removeAttendantAtPos(const int position) // Remove attendant at pos
{
	if (position > currentNumberOfAttendants || position < 1) // Out of list range
		return false;
	if (this->attendantsList.removeNodeAt(position - 1))
	{
		this->currentNumberOfAttendants--;
		return true;
	}
	return false;
}

bool Flight::addAttendant(Attendant* attendant) // Add attendant
{
	if (attendant == NULL || attendant == nullptr)
		return false;
	if (this->attendantsList.insert(attendant))
	{
		this->currentNumberOfAttendants++;
		return true;
	}
	return false;
}

bool Flight::removeAttendant(Attendant& attendant) // Remove attendant
{
	for (int attendantIndex = 0; attendantIndex < this->currentNumberOfAttendants; attendantIndex++) // Move on every attendant
		if (this->attendantsList.getDataInIndex(attendantIndex)->getData()->getEmployeeID() == attendant.getEmployeeID()) // Same attendant
		{
			if (removeAttendantAtPos(attendantIndex + 1))
			{
				this->currentNumberOfAttendants--;
				return true;
			}
		}
	return false;
}

bool Flight::removeAllAttendants() // Remove all attendants
{
	delete &attendantsList;
	currentNumberOfAttendants = 0;
	return true;
}

// SecurityGuard Methods
bool Flight::addSecurityGuard1(const SecurityGuard* securityGuard1) // Add security guard 1
{
	if (securityGuard1 == NULL || securityGuard1 == nullptr)
		return false;
	return setSecurityGuard1(securityGuard1);
}

bool Flight::removeSecurityGuard1() // Remove security guard 1
{
	delete securityGuard1;
	securityGuard1 = nullptr;
	return true;
}

bool Flight::addSecurityGuard2(const SecurityGuard* securityGuard2) // Add security guard 2
{
	if (securityGuard2 == NULL || securityGuard2 == nullptr)
		return false;
	return setSecurityGuard2(securityGuard2);
}

bool Flight::removeSecurityGuard2() // Remove security guard 2
{
	delete securityGuard2;
	securityGuard2 = nullptr;
	return true;
}

// Customer Methods
bool Flight::addCustomer(Customer* customer, const int row, const int col) // Add customer
{
	if (customer == NULL || customer == nullptr)
		return false;
	if (row < 1 || row > ROWS_IN_PLANE || col < 1 || col > SEATS_PER_ROW)
		return false;
	if (plane == NULL || plane == nullptr)
		return false;
	return plane->addCustomer(customer, row, col);
}

bool Flight::removeCustomerByName(const string name) // Remove customer by name
{
	if (plane == NULL || plane == nullptr)
		return false;
	Customer* foundCustomer1 = plane->findCustomerByName(name);
	if (foundCustomer1 == NULL)
		return false;
	return plane->removeCustomer(foundCustomer1);
}

bool Flight::removeCustomerBySeat(const int seatRow, const int seatColumn) // Remove customer by seat
{
	if (seatRow < 1 || seatRow > ROWS_IN_PLANE || seatColumn < 1 || seatColumn > SEATS_PER_ROW)
		return false;
	if (plane == NULL || plane == nullptr)
		return false;
	Customer* foundCustomer1 = plane->findCustomerBySeat(seatRow, seatColumn);
	if (foundCustomer1 == NULL)
		return false;
	return plane->removeCustomer(foundCustomer1);
}

bool Flight::resitCustomerByName(const string name, const int seatRow, const int seatColumn) // Resit customer by name
{
	if (seatRow < 1 || seatRow > ROWS_IN_PLANE || seatColumn < 1 || seatColumn > SEATS_PER_ROW)
		return false;
	if (plane == NULL || plane == nullptr)
		return false;
	Customer* foundCustomer1 = plane->findCustomerByName(name);
	Customer* foundCustomer2 = plane->findCustomerBySeat(seatRow, seatColumn);
	if (foundCustomer1 == NULL || foundCustomer2 != NULL)
		return false;
	return (plane->removeCustomer(foundCustomer1)) && (plane->addCustomer(foundCustomer1, seatRow, seatColumn));
}

bool Flight::resitCustomerBySeat(const int oldSeatRow, const int oldSeatColumn, const int newSeatRow, const int newSeatColumn) // Resit customer by seat
{
	if (oldSeatRow < 1 || oldSeatRow > ROWS_IN_PLANE || oldSeatColumn < 1 || oldSeatColumn > SEATS_PER_ROW)
		return false;
	if (newSeatRow < 1 || newSeatRow > ROWS_IN_PLANE || newSeatColumn < 1 || newSeatColumn > SEATS_PER_ROW)
		return false;
	if (plane == NULL || plane == nullptr)
		return false;
	Customer* foundCustomer1 = plane->findCustomerBySeat(oldSeatRow, oldSeatColumn);
	Customer* foundCustomer2 = plane->findCustomerBySeat(newSeatRow, newSeatColumn);
	if (foundCustomer1 == NULL || foundCustomer2 != NULL)
		return false;
	return (plane->removeCustomer(foundCustomer1)) && (plane->addCustomer(foundCustomer1, newSeatRow, newSeatColumn));
}

bool Flight::changeCustomerLuggageByName(const string name, Luggage* luggage) // Change customer luggage by name
{
	if (plane == NULL || plane == nullptr)
		return false;
	Customer* foundCustomer = plane->findCustomerByName(name);
	if (foundCustomer == NULL)
		return false;
	return foundCustomer->setLuggage(luggage);
}

// General Flight details methods
void Flight::showFlight() const // Show flight
{
	cout << this;
}

string Flight::getStatusAt(const tm time) const // Get status of flight (not left / on air / landed)
{
	if (time.tm_hour < this->takeoffTime->tm_hour || (time.tm_hour == this->takeoffTime->tm_hour && time.tm_min < this->takeoffTime->tm_min))
		return "The flight hasn't taken off yet";
	else if (time.tm_hour > this->landingTime->tm_hour || (time.tm_hour == this->landingTime->tm_hour && time.tm_min > this->landingTime->tm_min))
		return "The flight has landed";
	else 
		return "The flight is currently underway";
}

// Operators
void Flight::operator=(const Flight& flight) // Operator = (there is dynamic alocation in class)
{
	delete plane;
	plane = flight.plane;
	delete sourceAirport;
	sourceAirport = flight.sourceAirport;
	delete destinationAirport;
	destinationAirport = flight.destinationAirport;
	delete takeoffTime;
	takeoffTime = flight.takeoffTime;
	delete landingTime;
	landingTime = flight.landingTime;
	delete mainPilot;
	mainPilot = flight.mainPilot;
	delete coPilot;
	coPilot = flight.coPilot;
	delete securityGuard1;
	securityGuard1 = flight.securityGuard1;
	delete securityGuard2;
	securityGuard2 = flight.securityGuard2;
	delete &attendantsList;
	attendantsList = flight.attendantsList;
}

bool Flight::operator<(tm& time) const // Operator <
{
	if (time.tm_hour > this->landingTime->tm_hour || (time.tm_hour == this->landingTime->tm_hour && time.tm_min > this->landingTime->tm_min))
		return true;
	return false;
}

bool Flight::operator>(tm& time) const // Operator >
{
	if (time.tm_hour < this->takeoffTime->tm_hour || (time.tm_hour == this->takeoffTime->tm_hour && time.tm_min < this->takeoffTime->tm_min))
		return true;
	return false;
}

bool Flight::operator==(tm& time) const // Operator ==
{
	return (time.tm_hour == this->takeoffTime->tm_hour) && (time.tm_min == this->takeoffTime->tm_min);
}

bool Flight::operator+=(Customer& customer) const // Operator +=
{
	return this->plane->addCustomer(&customer);
}

bool Flight::operator-=(Customer& customer) const // Operator -=
{
	return this->plane->removeCustomer(&customer);
}

// Ostream
ostream& operator<<(ostream& os, const Flight& flight) // Flight ostream
{
	os << "Flight:" << endl;
	os << "\tPlane: " << flight.plane->getModel() << endl;
	if (flight.sourceAirport != NULL && flight.sourceAirport != nullptr)
		os << "\tSource airport: " << flight.sourceAirport->getCodeOfIATA() << ", " << flight.sourceAirport->getCountryName() << endl;
	else
		os << "\tSource airport: no source airport" << endl;
	if (flight.destinationAirport != NULL && flight.destinationAirport != nullptr)
		os << "\tDestination airport: " << flight.destinationAirport->getCodeOfIATA() << ", " << flight.destinationAirport->getCountryName() << endl;
	else
		os << "\tDestination airport: no destination airport" << endl;
	if (flight.getTakeoffTime()->tm_min >= 10)
		os << "\tDeparture time: " << flight.getTakeoffTime()->tm_hour << ":" << flight.getTakeoffTime()->tm_min << endl;
	else
		os << "\tDeparture time: " << flight.getTakeoffTime()->tm_hour << ":0" << flight.getTakeoffTime()->tm_min << endl;
	if (flight.getLandingTime()->tm_min >= 10)
		os << "\tArrival time: " << flight.getLandingTime()->tm_hour << ":" << flight.getLandingTime()->tm_min << endl;
	else
		os << "\tArrival time: " << flight.getLandingTime()->tm_hour << ":0" << flight.getLandingTime()->tm_min << endl;
	if(flight.mainPilot != NULL && flight.mainPilot != nullptr)
		os << "\tMain pilot: " << *(flight.mainPilot);
	else
		os << "\tMain pilot: no main pilot" << endl;
	if (flight.coPilot != NULL && flight.coPilot != nullptr)
		os << "\tCo pilot: " << *(flight.coPilot);
	else
		os << "\tCo pilot: no co pilot" << endl;
	if (flight.currentNumberOfAttendants > 0)
	{
		os << "\tAttendants: " << endl;
		for (int i = 0; i < flight.currentNumberOfAttendants; i++)
			os << "\t" << "\t" << (i + 1) << ")" << *(flight.attendantsList.getDataInIndex(i)->getData());
	}
	else
		os << "\tAttendants: no attendants" << endl;
	if (flight.securityGuard1 != NULL && flight.securityGuard1 != nullptr)
		os << "\tSecurity guard1: " << *(flight.securityGuard1);
	else
		os << "\tSecurity guard1: no security guard1" << endl;
	if (flight.securityGuard2 != NULL && flight.securityGuard2 != nullptr)
		os << "\tSecurity guard2: " << *(flight.securityGuard2);
	else
		os << "\tSecurity guard2: no security guard2" << endl;
	return os;
}