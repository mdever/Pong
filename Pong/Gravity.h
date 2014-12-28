#ifndef GRAVITY_H
#define GRAVITY_H

#include "Force.h"

class Gravity : public Force
{
public:
	Gravity(sf::Vector2f mag_and_direction);
	virtual void apply_force(PhysicalObject & entity);
private:
	sf::Vector2f direction;
};

#endif