#ifndef LUGGAGE_H
#define LUGGAGE_H

#pragma warning (disable : 4996)

#define MIN_LUGGAGE_VOLUME 0
#define MIN_LUGGAGE_WEIGHT 0

using namespace std;

class Luggage
{
private:
	double volume;
	double weight;

public:
	// Constructor
	Luggage(const double weight, const double volume) noexcept(false);

	// Gets
	double getVolume() const; // Get volume
	double getWeight() const; // Get weight

	// Sets
	bool setVolume(const double volume); // Set volume
	bool setWeight(const double weight); // Set weight
};

#endif // !LUGGAGE_H