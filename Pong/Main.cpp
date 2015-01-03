#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Network.hpp>

#include <iostream>
#include <memory>
#include <regex>

#include "Ball.h"
#include "Gravity.h"
#include "ResourceManager.h"
#include "MouseForce.h"
#include "Entity.h"

int main()
{
	std::shared_ptr<ResourceManager> resource_manager(ResourceManager::getResourceManager("properties.xml"));

	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	std::vector<Entity *> entities;
	std::vector<Drawable *> drawables;

	Ball ball(sf::Vector2f(50, 50), 20);
	ball.register_force(new MouseForce(window, 0.25));
	
	Ball gravity_ball(sf::Vector2f(100, 100), 20);
	gravity_ball.register_force(new Gravity(sf::Vector2f(0, 0.05)));
	ball.register_force(new Gravity(sf::Vector2f(0,0.1)));

	entities.push_back((Entity*) &ball);
	drawables.push_back((Drawable*) &ball);

	entities.push_back((Entity*) &gravity_ball);
	drawables.push_back((Drawable *) &gravity_ball);

	sf::Clock clock;
	bool clock_started = false;
	window.setVerticalSyncEnabled(true);
	int num_loops = 0;

	// run the program as long as the window is open
	while (window.isOpen())
	{
		if (!clock_started) {
			clock.restart();
			clock_started = true;
		}

		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
			case sf::Event::KeyPressed:
				for (Entity *entity : entities) {
					entity->handle_input(event);
				}
			}
		}

		if (clock.getElapsedTime().asMilliseconds() > 30) {
			sf::Time dt = clock.restart();
			std::cout << "Executed " << num_loops++ << " loops. Elapsed time: " << dt.asMilliseconds() << " milliseconds" << std::endl;
			for (Entity *entity : entities) {
				entity->doUpdate(dt);
			}
			
			window.clear(sf::Color::Black);
			
			for (Drawable *drawable : drawables) {
				drawable->doDraw(window);
			}

			window.display();
		}
	}

	return 0;
}