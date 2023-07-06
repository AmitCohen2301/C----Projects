#include "Luggage.h"

// Constructor
Luggage::Luggage(const double weight, const double volume) noexcept(false)
{
	if (setWeight(weight) == false)
		throw "Failed to set weight";
	if (setVolume(volume) == false)
		throw "Failed to set volume";
}

// Gets
double Luggage::getVolume() const // Get volume
{
	return this->volume;
}
double Luggage::getWeight() const // Get weight
{
	return this->weight;
}

// Sets
bool Luggage::setVolume(const double volume) // Set volume
{
	if (volume < MIN_LUGGAGE_VOLUME)
		return false;
	this->volume = volume;
	return true;
}

bool Luggage::setWeight(const double weight) // Set weight
{
	if (weight < MIN_LUGGAGE_WEIGHT)
		return false;
	this->weight = weight;
	return true;
}