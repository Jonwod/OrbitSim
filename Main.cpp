#include <SFML/Graphics.hpp>
#include "Body.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 400), "SFML works!");
	
	Body planet(50.f);
	planet.setPosition({ 0.f, 0.f });
	planet.setVelocity({20.f, 10.f});

	constexpr float framerate = 60.f;
	window.setFramerateLimit(framerate);
	sf::Clock framerateClock;
	sf::Time deltaT = sf::seconds(1.0f / framerate);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		planet.step(deltaT.asSeconds());

		window.clear();
		planet.draw(window);
		window.display();

		deltaT = framerateClock.restart();
	}

	return 0;
}
