#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include "Body.h"
#include "VectorMath.h"


constexpr float gravityStrength = 2.f;


// Returns the scalar speed for body to orbit other_body in a circle
float speedForCircularOrbit(const Body& body, const Body& otherBody) {
	const float r = VMath::magnitude(body.getPosition() - otherBody.getPosition());
	const float orbital_v = sqrt((gravityStrength * otherBody.getMass()) / r);
	return orbital_v;
}


// Gravitates body towards b
void gravitate(Body& a, const Body& b, float delta) {
	const float dis = VMath::magnitude(a.getPosition() - b.getPosition());
	if (dis != 0.f) {
		const float force_due_to_gravity = (gravityStrength * a.getMass() * b.getMass()) / pow(dis, 2);
		const Vec2 a_to_b = VMath::normal(b.getPosition() - a.getPosition());
		a.applyImpulse(a_to_b * force_due_to_gravity * delta);
	}
}


// ~~~~~~~~~HUD~~~~~~~~~~~~

class HUD {
public:
	HUD(const Body& orbiter, const Body& centerBody) 
		:_startRadius(VMath::magnitude(orbiter.getPosition() - centerBody.getPosition()))
	{
		if (!_font.loadFromFile("arial.ttf"))
			std::cout << "Error. arial.ttf not found\n";

		startRadiusText.setCharacterSize(14);
		currentRadiusText.setCharacterSize(14);
		errorText.setCharacterSize(14);

		startRadiusText.setPosition({10.f, 0.f});
		currentRadiusText.setPosition({ 10.f, 20.f});
		errorText.setPosition({10.f, 40.f});

		startRadiusText.setString("start radius: " + std::to_string(_startRadius));
	}


	void update(const Body& orbiter, const Body& centerBody) {
		const float radius = VMath::magnitude(orbiter.getPosition() - centerBody.getPosition());
		currentRadiusText.setString("current radius: " + std::to_string(radius));
		errorText.setString("error : " + std::to_string(radius - _startRadius));
	}


	void draw(sf::RenderWindow& window) {
		window.draw(startRadiusText);
		window.draw(currentRadiusText);
		window.draw(errorText);
	}

	sf::Text startRadiusText{"start radius: ", _font};
	sf::Text currentRadiusText{"current radius: ", _font};
	sf::Text errorText{"error: ", _font};
private:
	sf::Font _font;
	const float _startRadius;
};

//


int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
	
	Body planet(50.f, 125000000);
	planet.setPosition({ 500.f, 500.f });

	constexpr float framerate = 60.f;
	window.setFramerateLimit(framerate);
	sf::Clock framerateClock;
	
	Body moon(10.f, 1000.f);
	moon.setPosition({ 500.f, 250.f });

	moon.setVelocity({ speedForCircularOrbit(moon, planet), 0.f});
	//planet.setVelocity({ -speedForCircularOrbit(planet, moon), 0.f });

	HUD hud(moon, planet);

	const float timeStep = 1.0f / framerate;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		gravitate(moon, planet, timeStep);
		//gravitate(planet, moon, timeStep);

		planet.step(timeStep);
		moon.step(timeStep);

		window.clear();
		planet.draw(window);
		moon.draw(window);
		hud.update(moon, planet);
		hud.draw(window);
		window.display();

		framerateClock.restart();
	}

	return 0;
}
