#ifndef HAS_VELOCITY_H
#define HAS_VELOCITY_H

#include<SFML/Graphics.hpp>
#include "Force.h"
#include "Entity.h"

class Force;

class PhysicalObject : public Entity {
	
public:
	friend class Gravity;
	friend class MouseForce;
	virtual void register_force(Force * frce) = 0;

protected:
	sf::Vector2f velocity;
	sf::Vector2f acceleration;

	virtual void integrate(sf::Time dt) = 0;

	float acceleration_decay;
	float resistance;
	float impulse_factor;
};

#endif