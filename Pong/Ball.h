#ifndef BALL_H
#define BALL_H

#include "PhysicalObject.h"
#include "Entity.h"
#include "Drawable.h"

#include "Force.h"
#include<memory>
#include<vector>

class Ball : PhysicalObject, Drawable {

public:
	virtual void doUpdate(sf::Time dt);
	virtual void doDraw(sf::RenderTarget & window, sf::RenderStates states);


	sf::CircleShape shape;

	enum Direction {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	Ball(sf::Vector2f pos);
	~Ball();

	void impulse(Direction direction);

	void register_force(Force * frce);
protected:
	virtual void integrate(sf::Time dt);
	float speed_factor;
	float bounce_dampener;
	std::vector<Force*> forces;
	const float IMPULSE = 0.2;

};


#endif