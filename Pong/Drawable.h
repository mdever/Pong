#ifndef DRAWABLE_H
#define DRAWABLE_H

#include<SFML/Graphics.hpp>

class Drawable {

public:
	virtual void doDraw(sf::RenderTarget & window, sf::RenderStates states) = 0;
};

#endif