#include <SFML/Graphics.hpp>
#include "Body.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
	
	Body planet(50.f, 125000);
	planet.setPosition({ 500.f, 500.f });

	constexpr float framerate = 60.f;
	window.setFramerateLimit(framerate);
	sf::Clock framerateClock;
	sf::Time deltaT = sf::seconds(1.0f / framerate);

	Body moon(10.f, 1000.f);
	moon.setPosition({ 500.f, 250.f });

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		planet.step(deltaT.asSeconds());
		moon.step(deltaT.asSeconds());

		window.clear();
		planet.draw(window);
		moon.draw(window);
		window.display();

		deltaT = framerateClock.restart();
	}

	return 0;
}
