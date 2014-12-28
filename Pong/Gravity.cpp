#include "Gravity.h"

Gravity::Gravity(sf::Vector2f mag_and_direction)
{
	this->direction = mag_and_direction;
}

void Gravity::apply_force(PhysicalObject & entity)
{
	entity.acceleration += this->direction;
}