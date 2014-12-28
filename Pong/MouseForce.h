#pragma once

#include "Force.h"
class MouseForce :
	public Force
{
public:
	MouseForce(sf::Window & wndw, float mult);
	~MouseForce();
	void apply_force(PhysicalObject & entity);
private:
	sf::Window & window;
	float mult;
};

