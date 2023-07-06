#ifndef FLIGHT_H
#define FLIGHT_H

#pragma warning (disable : 4996)

#include <ostream>
#include <iostream>
#include <string>
#include "Plane.h"
#include "Airport.h"
#include "Attendant.h"
#include "SecurityGuard.h"
#include "Pilot.h"
#include "LinkedList.h"
#include <time.h>

using namespace std;

class Flight
{
private:
	Plane* plane;
	Airport* sourceAirport;
	Airport* destinationAirport;
	tm* takeoffTime;
	tm* landingTime;
	Pilot* mainPilot;
	Pilot* coPilot;
	SecurityGuard* securityGuard1;
	SecurityGuard* securityGuard2;
	LinkedList<Attendant*> attendantsList;
	int currentNumberOfAttendants;

	static Flight* flightInstance; // Singelton

	// Constructors
	Flight() noexcept(false);
	Flight(const Airport* sourceAirport, const Airport* destinationAirport) noexcept(false);

	// Copy c'tor (there is dynamic alocation in class)
	Flight(const Flight& flight);

	// Move c'tor (there is dynamic alocation in class)
	Flight(Flight&& flight);

	// Destructor (there is dynamic alocation in class)
	~Flight();

	// Operator = (there is dynamic alocation in class)
	void operator=(const Flight& flight);

public:
	// Gets
	static Flight* getInstance(); // Get instance (Singleton)
	Plane* getPlane() const; // Get plane
	Airport* getSourceAirport() const; // Get source airport
	Airport* getDestinationAirport() const; // Get destination airport
	tm* getTakeoffTime() const; // Get takeoff time
	tm* getLandingTime() const; // Get landing time
	Pilot* getMainPilot() const; // Get main pilot
	Pilot* getCoPilot() const; // Get co pilot
	SecurityGuard* getSecurityGuard1() const; // Get security gurad 1
	SecurityGuard* getSecurityGuard2() const; // Get security gurad 2
	LinkedList<Attendant*> getAttendantsList() const; // Get attendants list
	int getCurrentNumberOfAttendants() const; // Get current number of attendants

	// Sets
	bool setPlane(const Plane* plane); // Set plane
	bool setSourceAirport(const Airport* sourceAirport); // Set source airport
	bool setDestinationAirport(const Airport* destinationAirport); // Set destination airport
	bool setTakeoffTime(const tm* takeoffTime); // Set takeoff time
	bool setLandingTime(const tm* landingTime); // Set landing time
	bool setMainPilot(const Pilot* mainPilot); // Set main pilot
	bool setCoPilot(const Pilot* coPilot); // Set co pilot
	bool setSecurityGuard1(const SecurityGuard* securityGuard1); // Set security guard 1
	bool setSecurityGuard2(const SecurityGuard* securityGuard2); // Set security guard 2

	// Pilot Methods
	bool addMainPilot(const Pilot* mainPilot); // Add main pilot
	bool addCoPilot(const Pilot* coPilot); // Add co pilot
	bool removeMainPilot(); // Remove main pilot
	bool removeCoPilot(); // Remove co pilot

	// Attendant Methods
	Attendant* getAttendantAtPos(const int position) const; // Get attendant at pos
	bool removeAttendantAtPos(const int position); // Remove attendant at pos
	bool addAttendant(Attendant* attendant); // Add attendant
	bool removeAttendant(Attendant& attendant); // Remove attendant
	bool removeAllAttendants(); // Remove all attendants

	// SecurityGuard Methods
	bool addSecurityGuard1(const SecurityGuard* securityGuard1); // Add security guard 1
	bool removeSecurityGuard1(); // Remove security guard 1
	bool addSecurityGuard2(const SecurityGuard* securityGuard2); // Add security guard 2
	bool removeSecurityGuard2(); // Remove security guard 2

	// Customer Methods
	bool addCustomer(Customer* customer, const int row, const int col); // Add customer
	bool removeCustomerByName(const string name); // Remove customer by name
	bool removeCustomerBySeat(const int seatRow, const int seatColumn); // Remove customer by seat
	bool resitCustomerByName(const string name, const int seatRow, const int seatColumn); // Resit customer by name
	bool resitCustomerBySeat(const int oldSeatRow, const int oldSeatColumn, const int newSeatRow, const int newSeatColumn); // Resit customer by seat
	bool changeCustomerLuggageByName(const string name, Luggage* luggage); // Change customer luggage by name

	// General Flight details methods
	void showFlight() const; // Show flight
	string getStatusAt(const tm time) const; // Get status of flight (not left / on air / landed)

	// Operators
	bool operator<(tm& time) const; // Operator <
	bool operator>(tm& time) const; // Operator >
	bool operator==(tm& time) const; // Operator ==
	bool operator+=(Customer& customer) const; // Operator +=
	bool operator-=(Customer& customer) const; // Operator -=

	// Ostream
	friend ostream& operator<<(ostream& os, const Flight& flight); // Flight ostream
};

#endif // !FLIGHT_H