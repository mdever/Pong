#include "MouseForce.h"
#include <iostream>


MouseForce::MouseForce(sf::Window & wndw, float mag) : window(wndw), mult(mag)
{
}

void MouseForce::apply_force(PhysicalObject & entity)
{
	sf::Vector2i pos = sf::Mouse::getPosition(window);
	sf::Vector2f mouse_position(pos);

	sf::Vector2f ball_position = entity.get_center();

	sf::Vector2f difference = mouse_position - ball_position;

	float magnitude = sqrt(pow(difference.x, 2) + pow(difference.y, 2));

	sf::Vector2f unit_difference(difference.x / magnitude, difference.y / magnitude);

	entity.acceleration += (unit_difference * mult);

	std::cout << "Applying force " << unit_difference.x << " " << unit_difference.y;
}

MouseForce::~MouseForce()
{
}
