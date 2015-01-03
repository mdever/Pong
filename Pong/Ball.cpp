#include "Ball.h"
#include <iostream>

Ball::Ball(sf::Vector2f pos, float radius) : shape(sf::CircleShape(20))
{
	this->position = pos;
	this->velocity.x = 0;
	this->velocity.y = 0;
	this->acceleration.x = 0;
	this->acceleration.y = 0;

	this->acceleration_decay = 4 / 5;
	this->resistance = 0.9;
	this->speed_factor = 1.5;
	this->shape.setPosition(50, 50);
	this->shape.setRadius(radius);
	this->bounce_dampener = 0.9;
}

void Ball::impulse(Direction direction)
{
	switch (direction) {
	case UP:
		this->acceleration.y -= IMPULSE;
		std::cout << "Y Acceleration is now " << acceleration.x << std::endl;
		break;
	case DOWN:
		this->acceleration.y += IMPULSE;
		std::cout << "Y Acceleration is now " << acceleration.x << std::endl;
		break;
	case RIGHT:
		this->acceleration.x += IMPULSE;
		std::cout << "X Acceleration is now " << acceleration.x << std::endl;
		break;
	case LEFT:
		this->acceleration.x -= IMPULSE;
		std::cout << "X Acceleration is now " << acceleration.x << std::endl;
		break;
	}
}

void Ball::integrate(sf::Time dt)
{
	this->velocity.x += ((dt.asMilliseconds()/10) * this->acceleration.x) * this->speed_factor;
	this->velocity.y += ((dt.asMilliseconds()/10) * this->acceleration.y) * this->speed_factor;

	this->velocity.x *= this->resistance;
	this->velocity.y *= this->resistance;

	this->position.x += ((dt.asMilliseconds()/10) * this->velocity.x);
	this->position.y += ((dt.asMilliseconds()/10) * this->velocity.y);

	this->acceleration.x = (this->acceleration_decay) * this->acceleration.x;
	this->acceleration.y = (this->acceleration_decay) * this->acceleration.y;

	if ((this->position.x < 0 && this->velocity.x < 0) || (this->position.x > (800 - 40) && this->velocity.x > 0)) {
		this->velocity.x *= (-1 * this->bounce_dampener);
		if (this->position.x < 0)
			this->position.x = 0;
		if (this->position.x > (800 - 40))
			this->position.x = (800 - 40);
	}
	if ((this->position.y < 0 && this->velocity.y < 0) || (this->position.y > (600 - 40)) && this->velocity.y > 0) {
		this->velocity.y *= (-1 * this->bounce_dampener);
		if (this->position.y < 0)
			this->position.y = 0;
		if (this->position.y >(600 - 40))
			this->position.y = (600 - 40);
	}
}

void Ball::doUpdate(sf::Time dt) {
	for (Force *force : forces) {
		force->apply_force(*this);
	}
	this->integrate(dt);
	this->shape.setPosition(this->position);
}

void Ball::doDraw(sf::RenderTarget & window, sf::RenderStates states)
{
	window.draw(this->shape);
}

Ball::~Ball()
{

}

void Ball::register_force(Force * frce)
{
	this->forces.push_back(frce);
}

sf::Vector2f Ball::get_center() const
{
	float rad = this->shape.getRadius();
	return sf::Vector2f(position.x + rad, position.y + rad);
}

void Ball::handle_input(const sf::Event& event)
{
	switch (event.key.code) {
	case sf::Keyboard::Down:
		impulse(Ball::DOWN);
		std::cout << "Down" << std::endl;
		break;
	case sf::Keyboard::Up:
		impulse(Ball::UP);
		std::cout << "Up" << std::endl;
		break;
	case sf::Keyboard::Right:
		impulse(Ball::RIGHT);
		std::cout << "Right" << std::endl;
		break;
	case sf::Keyboard::Left:
		impulse(Ball::LEFT);
		std::cout << "Left" << std::endl;
		break;
	}
}