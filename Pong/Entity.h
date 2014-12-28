#ifndef ENTITY_H
#define ENTITY_H

#include<SFML/Graphics.hpp>


class Entity {

public:
	virtual void doUpdate(sf::Time dt) = 0;
	virtual sf::Vector2f get_center() const = 0;

protected:
	sf::Vector2f position;
};

#endif