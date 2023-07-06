// Pragmas
#pragma warning(disable: 4996) // To override the _s error

// Includes
#include <iostream>
#include <array>
#include <string.h>
#include "Plane.h"
#include "Pilot.h"
#include "Airport.h"
#include "Attendant.h"
#include "Luggage.h"
#include "SecurityGuard.h"
#include "Flight.h"

using namespace std;

// Statics to generate objects
static int licenseID = 1;
static int employeeID = 1;

// Defines
#define EXIT -1
#define BACK -1
#define MAIN_MENU 0

// inside main menu:
#define CREW_MENU 1
#define CUSTOMERS_MENU 2
#define DETAILS_MENU 3

// inside crew menu:
#define PILOT_MENU 1
#define ATTENDANTS_MENU 2
#define SECURITY_GUARDS_MENU 3

// inside details menu:
#define DETAILS_AIRPORTS_MENU 1
#define DETAILS_TIMES_MENU 2

void cleanBuffer(); // Clean buffer
int getUserIntegerInput(int min, int max); // Get integer from user
Luggage* getNewLuggage(); // Generate luggage
Pilot* getANewPilot(); // Generate pilot
Attendant* getANewAttendant(); // Generate attendant
SecurityGuard* getANewSecurityGuard(); // Generate security guard
Plane* makeNewPlane(); // Generate plane
Airport* getNewAirport(); // Generate airport
Flight* getANewFlight(); // Generate flight
void addPilot(Flight* flight, int designation); // Add pilot (main > CREW_MENU > PILOT_MENU > addPilot)
void pilotsMenu(Flight* flight); // Pilots menu (main > CREW_MENU > PILOT_MENU)
void showAttendantsList(Flight* flight); // Show attendants list (main > CREW_MENU > ATTENDANTS_MENU > showAttendantsList)
void addAttendant(Flight* flight); // Add attendant (main > CREW_MENU > ATTENDANTS_MENU > addAttendant) 
void removeAttendant(Flight* flight); // Remove attendant (main > CREW_MENU > ATTENDANTS_MENU > removeAttendant)
void attendantMenu(Flight* flight); // Attendant menu (main > CREW_MENU > ATTENDANTS_MENU)
void addSecurityGuard(Flight* flight, int designation); // Add security guard (main > CREW_MENU > SECURITY_GUARDS_MENU > addGuard)
void guardsMenu(Flight* flight); // Guards menu (main > CREW_MENU > SECURITY_GUARDS_MENU) 
void crewMenu(Flight* flight); // Crew menu (main > CREW_MENU)
void addCustomerNoSit(Flight* flight); // Add customer with no sit (main > CUSTOMERS_MENU > ADD_CUSTOMERS_MENU > add customer without seat)
void addCustomerWithSit(Flight* flight); // Add customer with sit (main > CUSTOMERS_MENU > ADD_CUSTOMERS_MENU > add customer with seat) 
void addCustomerMenu(Flight* flight); // Add customer menu (main > CUSTOMERS_MENU > ADD_CUSTOMERS_MENU)
void removeCustomerByName(Flight* flight); // Remove customer by name (main > CUSTOMERS_MENU > REMOVE_CUSTOMERS_MENU > REMOVE_CUSTOMER_BY_NAME)
void removeCustomerBySeat(Flight* flight); // Remove customer by seat (main > CUSTOMERS_MENU > REMOVE_CUSTOMERS_MENU > REMOVE_CUSTOMER_BY_SEAT)
void removeCustomerMenu(Flight* flight); // Remove customer menu (main > CUSTOMERS_MENU > REMOVE_CUSTOMERS_MENU) 
void resitCustomerByName(Flight* flight); // Resit customer by name (main > CUSTOMERS_MENU > RESIT_CUSTOMERS_MENU > RESIT_CUSTOMER_BY_NAME) 
void resitCustomerBySeat(Flight* flight); // Resit customer by seat (main > CUSTOMERS_MENU > RESIT_CUSTOMERS_MENU > RESIT_CUSTOMER_BY_SEAT)
void resitCustomerMenu(Flight* flight); // Resit customer menu (main > CUSTOMERS_MENU > RESIT_CUSTOMERS_MENU)
void changeCustomerLuggage(Flight* flight); // Change customer luggage (main > CUSTOMERS_MENU > CHANGE_CUSTOMER_LUGGAGE)
void customerMenu(Flight* flight); // Customer menu (main > CUSTOMERS_MENU)
void setSourceAirport(Flight* flight); // Set source airport (main > DETAILS_MENU >> AIRPORT > set source)
void setDestinationAirport(Flight* flight); // Set destination airport (main > DETAILS_MENU >> AIRPORT > set Destination)
void airportsMenu(Flight* flight); // Airports menu (main > DETAILS_MENU >> AIRPORT)
void setTime(Flight* flight, int designation); // Set time
void timesMenu(Flight* flight); // Times menu (main > DETAILS_MENU > TIME_MENU)
void getStatusByTime(Flight* flight); // Get status by time (main > DETAILS_MENU > get status by time)
void flightDetailsMenu(Flight* flight); // Flight details menu (main > DETAILS_MENU)

// Main
int main()
{
	int choice = 0, numOfAttendants = 3;
	Flight* flight = getANewFlight();
	flight->addMainPilot(getANewPilot());
	flight->addCoPilot(getANewPilot());
	flight->addSecurityGuard1(getANewSecurityGuard());
	flight->addSecurityGuard2(getANewSecurityGuard());
	for (int i = 0; i < numOfAttendants; i++)
		flight->addAttendant(getANewAttendant());

	do
	{
		cout << "\nFlight Management: (enter the num of the option you want) \n"
			<< "\t 1) Crew \n"
			<< "\t 2) Customers \n"
			<< "\t 3) Flight details \n"
			<< "\t-1) Exit \n";
		choice = getUserIntegerInput(-1, 3);
		switch (choice)
		{
		case CREW_MENU:
			crewMenu(flight);
			break;
		case CUSTOMERS_MENU:
			customerMenu(flight);
			break;
		case DETAILS_MENU:
			flightDetailsMenu(flight);
			break;
		default:
			break;
		}
	} while (choice != EXIT);
}

// Clean buffer
void cleanBuffer()
{
	int c;
	do
	{
		c = getchar();
	} while ((c != EOF) && (c != '\n'));
}

// Get integer from user
int getUserIntegerInput(int min, int max)
{
	int input = 0;
	cin >> input;
	cleanBuffer();
	while ((input < min) || (input > max))
	{
		cout << "invalid input, please enter a valid number between " << min << " and " << max << ": ";
		cin >> input;
		cleanBuffer();
	}
	return input;
}

// Generate luggage
Luggage* getNewLuggage()
{
	return new Luggage((rand() % 10000) / 100.0, (rand() % 10000) / 100.0);
}

// Generate pilot
Pilot* getANewPilot()
{
	const char* pilotNames[] = { "Name1", "Name2", "Name3", "Name4", "Name5", "Name6", "Name7", "Name8", "Name9", "Name10" };
	int placeInNames = rand() % (end(pilotNames) - begin(pilotNames));
	int licenseNum = rand() % 10000;
	return new Pilot(employeeID++, pilotNames[placeInNames], licenseNum);
}

// Generate attendant
Attendant* getANewAttendant()
{
	const char* attendantNames[] = { "Name1", "Name2", "Name3", "Name4", "Name5", "Name6", "Name7", "Name8", "Name9", "Name10" };
	int placeInNames = rand() % (end(attendantNames) - begin(attendantNames));
	int AidKnowledge = 1 + (rand() % 10);
	return new Attendant(employeeID++, attendantNames[placeInNames], AidKnowledge, getNewLuggage());
}

// Generate security guard
SecurityGuard* getANewSecurityGuard()
{
	const char* guardsNames[] = { "Name1", "Name2", "Name3", "Name4", "Name5", "Name6", "Name7", "Name8", "Name9", "Name10" };
	const char* weaponNames[] = { "Name1", "Name2", "Name3", "Name4", "Name5", "Name6", "Name7", "Name8", "Name9", "Name10" };
	int placeInGuardsNames = rand() % (end(guardsNames) - begin(guardsNames));
	int placeInWeaponNames = rand() % (end(weaponNames) - begin(weaponNames));
	return new SecurityGuard("SpecialTicket", guardsNames[placeInGuardsNames], getNewLuggage(), employeeID++, weaponNames[placeInWeaponNames]);
}

// Generate plane
Plane* makeNewPlane()
{
	const char* planeModels[] = { "Model1", "Model2", "Model3", "Model4", "Model5", "Model6", "Model7", "Model8", "Model9", "Model10" };
	int placeInModels = rand() % (end(planeModels) - begin(planeModels));
	return new Plane(planeModels[placeInModels]);
}

// Generate airport
Airport* getNewAirport()
{
	const char* IATAList[] = { "IATA1", "IATA2", "IATA3", "IATA4", "IATA5", "IATA6", "IATA7", "IATA8", "IATA9", "IATA10" };
	const char* countryList[] = { "Country1", "Country2", "Country3", "Country4", "Country5", "Country6", "Country7", "Country8", "Country9", "Country10" };

	int placeInIATA = rand() % (end(IATAList) - begin(IATAList));
	int placeInCountry = rand() % (end(countryList) - begin(countryList));
	return new Airport(IATAList[placeInIATA], countryList[placeInCountry]);
}

// Generate flight
Flight* getANewFlight()
{
	return new Flight(getNewAirport(), getNewAirport());
}

// Add pilot
void addPilot(Flight* flight, int designation) // main > CREW_MENU > PILOT_MENU > addPilot
{
	char name[100];
	cout << "Enter the pilot's name: ";
	cin >> name;
	Pilot* pilot = new Pilot(employeeID++, name, licenseID++);
	if (designation == 1) // Want to add main pilot
		flight->addMainPilot(pilot);
	else // Want to add co pilot
		flight->addCoPilot(pilot);
}

// Pilots menu
void pilotsMenu(Flight* flight) // main > CREW_MENU > PILOT_MENU
{
	int choice = 0;
	do
	{
		cout << "\nPilots:(enter the num of the option you want) \n"
			<< "\t 1) Add main pilot \n"
			<< "\t 2) Remove main pilot \n"
			<< "\t 3) Add co-pilot \n"
			<< "\t 4) Remove co-pilot \n"
			<< "\t-1) : Back \n";
		choice = getUserIntegerInput(-1, 4);
		switch (choice)
		{
		case 1: // Add main pilot
			addPilot(flight, 1);
			break;
		case 2: // Remove main pilot
			flight->removeMainPilot();
			break;
		case 3: // Add co pilot
			addPilot(flight, 2);
			break;
		case 4: // Remove co pilot
			flight->removeCoPilot();
			break;
		default:
			break;
		}
	} while (choice != -1);
}

// Show attendants list
void showAttendantsList(Flight* flight) // main > CREW_MENU > ATTENDANTS_MENU > showAttendantsList
{
	int numofAttendants = flight->getCurrentNumberOfAttendants();
	Attendant** allAttendants = flight->getAttendantsList();
	if (numofAttendants == 0)
	{
		cout << "All attendants: There are no attendants\n";
		return;
	}
	cout << "All attendants:\n";
	for (int i = 0; i < numofAttendants; i++)
		cout << "\t" << (i+1) << ") " << *(allAttendants[i]);
}

// Add attendant
void addAttendant(Flight* flight) // main > CREW_MENU > ATTENDANTS_MENU > addAttendant
{
	char name[100];
	int firstAidKnowledge;
	double luggageWeight = 0, luggageVolume = 0;
	cout << "Enter the attendant's name: ";
	cin >> name;
	cout << "Enter the attendant's first aid knowledge (1-10): ";
	cin >> firstAidKnowledge;
	cleanBuffer();
	cout << "Enter Luggage weight: ";
	cin >> luggageWeight;
	cleanBuffer();
	cout << "Enter Luggage volume: ";
	cin >> luggageVolume;
	cleanBuffer();
	flight->addAttendant(new Attendant(employeeID++, name, firstAidKnowledge, new Luggage(luggageWeight, luggageVolume)));
}

// Remove attendant
void removeAttendant(Flight* flight)// main > CREW_MENU > ATTENDANTS_MENU > removeAttendant
{
	int attendantOffset = 0, numOfAttendants = flight->getCurrentNumberOfAttendants();
	cout << "Enter the attendant's pos to remove (1-" << numOfAttendants << "): ";
	while (attendantOffset < 1 || attendantOffset > numOfAttendants)
		attendantOffset = getUserIntegerInput(0, numOfAttendants);
	flight->removeAttendantAtPos(attendantOffset);
}

// Attendant menu
void attendantMenu(Flight* flight) // main > CREW_MENU > ATTENDANTS_MENU
{
	int choice = 0;
	do
	{
		cout << "\nAttendants: (enter the num of the option you want) \n"
			<< "\t 1) Show attendants list \n"
			<< "\t 2) Add attendant \n"
			<< "\t 3) Remove attendant \n"
			<< "\t 4) Clear all \n"
			<< "\t-1) Back \n";
		choice = getUserIntegerInput(-1, 4);
		switch (choice)
		{
		case 1:
			showAttendantsList(flight);
			break;
		case 2:
			addAttendant(flight);
			break;
		case 3:
			removeAttendant(flight);
			break;
		case 4:
			flight->removeAllAttendants();
			break;
		default:
			break;
		}
	} while (choice != -1);
}

// Add security guard
void addSecurityGuard(Flight* flight, int designation) // main > CREW_MENU > SECURITY_GUARDS_MENU > addGuard
{
	char name[100], weapon[100];
	double luggageWeight = 0, luggageVolume = 0;
	cout << "Enter the guard's name: ";
	cin >> name;
	cout << "Enter Luggage weight: ";
	cin >> luggageWeight;
	cleanBuffer();
	cout << "Enter Luggage volume: ";
	cin >> luggageVolume;
	cleanBuffer();
	cout << "Enter the guard's weapon: ";
	cin >> weapon;
	SecurityGuard* securityGuard = new SecurityGuard("SpecialTicket", name, new Luggage(luggageWeight, luggageVolume), employeeID++, weapon);
	if (designation == 1) // Want to add security guard1
		flight->addSecurityGuard1(securityGuard);
	else // Want to add security guard1
		flight->addSecurityGuard2(securityGuard);
}

// Guards menu
void guardsMenu(Flight* flight) // main > CREW_MENU > SECURITY_GUARDS_MENU
{
	int choice = 0;
	do
	{
		cout << "\nSecurity Guards: (enter the num of the option you want) \n"
			<< "\t 1) Add guard 1 \n"
			<< "\t 2) Remove guard 1 \n"
			<< "\t 3) Add guard 2 \n"
			<< "\t 4) Remove guard 2 \n"
			<< "\t-1) Back \n";
		choice = getUserIntegerInput(-1, 4);
		switch (choice)
		{
		case 1:
			addSecurityGuard(flight, 1);
			break;
		case 2:
			flight->removeSecurityGuard1();
			break;
		case 3:
			addSecurityGuard(flight, 2);
			break;
		case 4:
			flight->removeSecurityGuard2();
			break;
		default:
			break;
		}
	} while (choice != -1);
}

// Crew menu
void crewMenu(Flight* flight) // main > CREW_MENU
{
	int choice = 0;
	do
	{
		cout << "\nCrew: (enter the num of the option you want) \n"
			<< "\t 1) Pilots \n"
			<< "\t 2) Attendants \n"
			<< "\t 3) Security Guards \n"
			<< "\t-1) Back \n";
		choice = getUserIntegerInput(-1, 3);
		switch (choice)
		{
		case PILOT_MENU:
			pilotsMenu(flight);
			break;
		case ATTENDANTS_MENU:
			attendantMenu(flight);
			break;
		case SECURITY_GUARDS_MENU:
			guardsMenu(flight);
			break;
		default:
			break;
		}
	} while (choice != -1);
}

// Add customer with no sit
void addCustomerNoSit(Flight* flight) // main > CUSTOMERS_MENU > ADD_CUSTOMERS_MENU > add customer without seat
{
	char name[100], ticketNum[100];
	double luggageWeight = 0, luggageVolume = 0;
	cout << "Enter the customer's name: ";
	cin >> name;
	cout << "Enter the ticket number: ";
	cin >> ticketNum;
	cout << "Enter Luggage weight: ";
	cin >> luggageWeight;
	cleanBuffer();
	cout << "Enter Luggage volume: ";
	cin >> luggageVolume;
	cleanBuffer();
	*flight += *(new Customer(ticketNum, name, new Luggage(luggageWeight, luggageVolume)));
}

// Add customer with sit
void addCustomerWithSit(Flight* flight) // main > CUSTOMERS_MENU > ADD_CUSTOMERS_MENU > add customer with seat
{
	char name[100], ticketNum[100];
	double luggageWeight = 0, luggageVolume = 0;
	int seatRow, seatColumn;
	cout << "Enter the customer's name: ";
	cin >> name;
	cout << "Enter the ticket number: ";
	cin >> ticketNum;
	cout << "Enter Luggage weight: ";
	cin >> luggageWeight;
	cleanBuffer();
	cout << "Enter Luggage volume: ";
	cin >> luggageVolume;
	cleanBuffer();
	cout << "Enter a seat number:\n";
	cout << "Row: ";
	seatRow = getUserIntegerInput(1, ROWS_IN_PLANE);
	cout << "Column: ";
	seatColumn = getUserIntegerInput(1, SEATS_PER_ROW);
	flight->addCustomer(new Customer(ticketNum, name, new Luggage(luggageWeight, luggageVolume)), seatRow, seatColumn);
}

// Add customer menu
void addCustomerMenu(Flight* flight) // main > CUSTOMERS_MENU > ADD_CUSTOMERS_MENU
{
	int choice = 0;
	do
	{
		cout << "\nAdd customers: (enter the num of the option you want) \n"
			<< "\t 1) Add customer without sitting \n"
			<< "\t 2) Add new customer with sitting \n"
			<< "\t-1) Back \n";
		choice = getUserIntegerInput(-1, 2);
		switch (choice)
		{
		case 1:
			addCustomerNoSit(flight);
			break;
		case 2:
			addCustomerWithSit(flight);
			break;
		default:
			break;
		}
	} while (choice != -1);
}

// Remove customer by name
void removeCustomerByName(Flight* flight) // main > CUSTOMERS_MENU > REMOVE_CUSTOMERS_MENU > REMOVE_CUSTOMER_BY_NAME
{
	char name[100];
	cout << "Enter the customer's name: ";
	cin >> name;
	flight->removeCustomerByName(name);
}

// Remove customer by seat
void removeCustomerBySeat(Flight* flight) // main > CUSTOMERS_MENU > REMOVE_CUSTOMERS_MENU > REMOVE_CUSTOMER_BY_SEAT
{
	int seatRow, seatColumn;
	cout << "Enter a seat number:\n";
	cout << "Row: ";
	seatRow = getUserIntegerInput(1, ROWS_IN_PLANE);
	cout << "Column: ";
	seatColumn = getUserIntegerInput(1, SEATS_PER_ROW);
	flight->removeCustomerBySeat(seatRow, seatColumn);
}

// Remove customer menu
void removeCustomerMenu(Flight* flight) // main > CUSTOMERS_MENU > REMOVE_CUSTOMERS_MENU
{
	int choice = 0;
	do
	{
		cout << "\nRemove customer: (enter the num of the option you want) \n"
			<< "\t 1) Remove customer by name \n"
			<< "\t 2) Remove customer by seat \n"
			<< "\t-1) Back \n";
		choice = getUserIntegerInput(-1, 2);
		switch (choice)
		{
		case 1:
			removeCustomerByName(flight);
			break;
		case 2:
			removeCustomerBySeat(flight);
			break;
		default:
			break;
		}
	} while (choice != -1);
}

// Resit customer by name
void resitCustomerByName(Flight* flight) // main > CUSTOMERS_MENU > RESIT_CUSTOMERS_MENU > RESIT_CUSTOMER_BY_NAME
{
	char name[100];
	int newSeatRow, newSeatColumn;
	cout << "Enter a customer's name: ";
	cin >> name;
	cout << "Enter a new seat number:\n";
	cout << "Row: ";
	newSeatRow = getUserIntegerInput(1, ROWS_IN_PLANE);
	cout << "Column: ";
	newSeatColumn = getUserIntegerInput(1, SEATS_PER_ROW);
	flight->resitCustomerByName(name, newSeatRow, newSeatColumn);
}

// Resit customer by seat
void resitCustomerBySeat(Flight* flight) // main > CUSTOMERS_MENU > RESIT_CUSTOMERS_MENU > RESIT_CUSTOMER_BY_SEAT
{
	int oldSeatRow, oldSeatColumn, newSeatRow, newSeatColumn;
	cout << "Enter a seat number:\n";
	cout << "Row: ";
	oldSeatRow = getUserIntegerInput(1, ROWS_IN_PLANE);
	cout << "Column: ";
	oldSeatColumn = getUserIntegerInput(1, SEATS_PER_ROW);
	cout << "Enter a new seat number:\n";
	cout << "Row: ";
	newSeatRow = getUserIntegerInput(1, ROWS_IN_PLANE);
	cout << "Column: ";
	newSeatColumn = getUserIntegerInput(1, SEATS_PER_ROW);
	flight->resitCustomerBySeat(oldSeatRow, oldSeatColumn, newSeatRow, newSeatColumn);
}

// Resit customer menu
void resitCustomerMenu(Flight* flight) // main > CUSTOMERS_MENU > RESIT_CUSTOMERS_MENU
{
	int choice = 0;
	do
	{
		cout << "\nResit customer: (enter the num of the option you want) \n"
			<< "\t 1) Pick customer by name \n"
			<< "\t 2) Pick customer by seat \n"
			<< "\t-1) Back \n";
		choice = getUserIntegerInput(-1, 2);
		switch (choice)
		{
		case 1:
			resitCustomerByName(flight);
			break;
		case 2:
			resitCustomerBySeat(flight);
			break;
		default:
			break;
		}
	} while (choice != -1);
}

// Change customer luggage
void changeCustomerLuggage(Flight* flight) // main > CUSTOMERS_MENU > CHANGE_CUSTOMER_LUGGAGE
{
	char name[100];
	double luggageWeight = 0, luggageVolume = 0;
	cout << "Enter a customer's name: ";
	cin >> name;
	cout << "Enter Luggage weight: ";
	cin >> luggageWeight;
	cleanBuffer();
	cout << "Enter Luggage volume: ";
	cin >> luggageVolume;
	cleanBuffer();
	flight->changeCustomerLuggageByName(name, new Luggage(luggageWeight, luggageVolume));
}

// Customer menu
void customerMenu(Flight* flight) // main > CUSTOMERS_MENU
{
	int choice = 0;

	do
	{
		cout << "\nCustomers: (enter the num of the option you want) \n"
			<< "\t 1) Add customer \n"
			<< "\t 2) Remove customer \n"
			<< "\t 3) Re-sit customer \n"
			<< "\t 4) Change customer's luggage \n"
			<< "\t-1) Back \n";
		choice = getUserIntegerInput(-1, 4);
		switch (choice)
		{
		case 1:
			addCustomerMenu(flight);
			break;
		case 2:
			removeCustomerMenu(flight);
			break;
		case 3:
			resitCustomerMenu(flight);
			break;
		case 4:
			changeCustomerLuggage(flight);
		default:
			break;
		}
	} while (choice != -1);
}

// Set source airport
void setSourceAirport(Flight* flight) // main > DETAILS_MENU >> AIRPORT > set source
{
	char IATA[100], countryName[100];
	cout << "Enter the airport's IATA code: ";
	cin >> IATA;
	cout << "Enter the airport's country name: ";
	cin >> countryName;
	flight->setSourceAirport(new Airport(IATA, countryName));
}

// Set destination airport
void setDestinationAirport(Flight* flight) // main > DETAILS_MENU >> AIRPORT > set Destination
{
	char IATA[100], countryName[100];
	cout << "Enter the airport's IATA code: ";
	cin >> IATA;
	cout << "Enter the airport's country name: ";
	cin >> countryName;
	flight->setDestinationAirport(new Airport(IATA, countryName));
}

// Airports menu
void airportsMenu(Flight* flight) // main > DETAILS_MENU >> AIRPORT
{
	int choice = 0;
	do
	{
		cout << "\nAirports: (enter the num of the option you want) \n"
			<< "\t 1) Set Source Airport \n"
			<< "\t 2) Set Destination Airport \n"
			<< "\t-1) Back \n";
		choice = getUserIntegerInput(-1, 2);
		switch (choice)
		{
		case 1: 
			setSourceAirport(flight);
			break;
		case 2: 
			setDestinationAirport(flight);
			break;
		default:
			break;
		}
	} while (choice != -1);
}

// Set time
void setTime(Flight* flight, int designation)
{
	tm time;
	if (designation == 1) 
	{
		cout << "Enter takeoff hour: ";
		cin >> time.tm_hour;
		cleanBuffer();
		cout << "Enter takeoff minute: ";
		cin >> time.tm_min;
		cleanBuffer();
	}
	else
	{
		cout << "Enter landing hour: ";
		cin >> time.tm_hour;
		cleanBuffer();
		cout << "Enter landing minute: ";
		cin >> time.tm_min;
		cleanBuffer();
	}
	if (designation == 1) // Want to set take off time
		flight->setTakeoffTime(&time);
	else // Want to set landing time
		flight->setLandingTime(&time);
}

// Times menu
void timesMenu(Flight* flight) // main > DETAILS_MENU > TIME_MENU
{
	int choice = 0;
	do
	{
		cout << "\nAirports: (enter the num of the option you want) \n"
			<< "\t 1) Set Takeoff Time \n"
			<< "\t 2) Set Landing Time \n"
			<< "\t-1) Back \n";
		choice = getUserIntegerInput(-1, 2);
		switch (choice)
		{
		case 1: setTime(flight, 1);
			break;
		case 2: setTime(flight, 2);
			break;
		default:
			break;
		}
	} while (choice != -1);
}

// Get status by time
void getStatusByTime(Flight* flight) // main > DETAILS_MENU > get status by time
{
	tm time;
	cout << "Enter status hour: ";
	cin >> time.tm_hour;
	cleanBuffer();
	cout << "Enter status minute: ";
	cin >> time.tm_min;
	cleanBuffer();
	cout << flight->getStatusAt(time) << "\n";
}

// Flight details menu
void flightDetailsMenu(Flight* flight) // main > DETAILS_MENU
{
	int choice = 0;
	do
	{
		cout << "\nDetails: (enter the num of the option you want) \n"
			<< "\t 1) Show Details \n"
			<< "\t 2) Show plane \n"
			<< "\t 3) Status By Time: \n"
			<< "\t 4) Airports \n"
			<< "\t 5) Times \n"
			<< "\t-1) Back \n";
		choice = getUserIntegerInput(-1, 5);
		switch (choice)
		{
		case 1:
			cout << *flight;
			break;
		case 2:
			flight->getPlane()->showSeats();
			break;
		case 3:
			getStatusByTime(flight);
			break;
		case 4:
			airportsMenu(flight);
			break;
		case 5:
			timesMenu(flight);
			break;
		default:
			break;
		}
	} while (choice != -1);
}