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

	Ball(sf::Vector2f pos, float radius);
	~Ball();

	void impulse(Direction direction);

	// Todo - Refactor this in to the PhysicalObject baseclass. No reason this is unique to the Ball.
	void register_force(Force * frce);
	virtual sf::Vector2f get_center() const;
protected:
	virtual void integrate(sf::Time dt);
	float speed_factor;
	float bounce_dampener;

	// TODO - Refactor this in to the PhysicalObject base class. Replace std::vector<Force*> with std::vector<std::unique_ptr<Force>>. The same force
	// could be shared between multiple PhysicalObject's so we need some sort of ownership semantics. I'd rather not deal with this and just make it a shared_ptr so that
	// the force will destroy itself when it's reference count goes to 0.
	std::vector<Force*> forces;
	const float IMPULSE = 0.2;
	float radius;

};


#endif