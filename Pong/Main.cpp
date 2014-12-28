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

int main()
{
	std::shared_ptr<ResourceManager> resource_manager = std::shared_ptr<ResourceManager>(ResourceManager::getResourceManager("properties.xml"));

	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

	Ball ball(sf::Vector2f(50, 50));
	ball.register_force(new MouseForce(window, 0.25));
	ball.register_force(new Gravity(sf::Vector2f(0,0.1)));

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
				switch (event.key.code) {
				case sf::Keyboard::Down:
					ball.impulse(Ball::DOWN);
					std::cout << "Down" << std::endl;
					break;
				case sf::Keyboard::Up:
					ball.impulse(Ball::UP);
					std::cout << "Up" << std::endl;
					break;
				case sf::Keyboard::Right:
					ball.impulse(Ball::RIGHT);
					std::cout << "Right" << std::endl;
					break;
				case sf::Keyboard::Left:
					ball.impulse(Ball::LEFT);
					std::cout << "Left" << std::endl;
					break;
				}

			}
		}

		if (clock.getElapsedTime().asMilliseconds() > 30) {
			sf::Time dt = clock.restart();
			std::cout << "Executed " << num_loops++ << " loops. Elapsed time: " << dt.asMilliseconds() << " milliseconds" << std::endl;
			ball.doUpdate(dt);
			window.clear(sf::Color::Black);
			window.draw(ball.shape);
			window.display();
		}
	}

	return 0;
}