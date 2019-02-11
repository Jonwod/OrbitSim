#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include "Body.h"
#include "KinematicOrbiter.h"
#include "HUD.h"
#include "Constants.h"
#include "VectorMath.h"



// Returns the scalar speed for body to orbit other_body in a circle
float speedForCircularOrbit(const Body& body, const Body& otherBody) {
	const float r = VMath::magnitude(body.getPosition() - otherBody.getPosition());
	const float orbital_v = sqrt((G * otherBody.getMass()) / r);
	return orbital_v;
}


// Gravitates body towards b
void gravitate(Body& a, const Body& b, float delta) {
	const float dis = VMath::magnitude(a.getPosition() - b.getPosition());
	if (dis != 0.f) {
		const float force_due_to_gravity = (G * a.getMass() * b.getMass()) / pow(dis, 2);
		const Vec2 a_to_b = VMath::normal(b.getPosition() - a.getPosition());
		a.applyImpulse(a_to_b * force_due_to_gravity * delta);
	}
}


/*
	NOTES:
	Using this 2nd Order method, the orbiting body seems to spiral into the other body...
	This is not the expected result. This approximation should still produce a force slightly less than necessary to sustain a perfect circular orbit
*/
void gravitate_2ndOrder(Body& a, const Body& b, float delta) {
	const float dis = VMath::magnitude(a.getPosition() - b.getPosition());
	if (dis != 0.f) {
		const float force_due_to_gravity = (G * a.getMass() * b.getMass()) / pow(dis, 2);

		const Vec2 a_to_b = VMath::normal(b.getPosition() - a.getPosition());
		const Vec2 startForce = a_to_b * force_due_to_gravity;
		const Vec2 startVelocity = a.getVelocity() + (startForce * delta) / a.getMass();

		const Vec2 projectedPosition = a.getPosition() + startVelocity * delta;
		const Vec2 projected_a_to_b = VMath::safeNormal(b.getPosition() - projectedPosition);

		const Vec2 endForce = projected_a_to_b * force_due_to_gravity;

		const Vec2 averageForce = (startForce + endForce) / 2.f;
		a.applyImpulse(averageForce * delta);
	}
}



int main()
{
	sf::RenderWindow window(sf::VideoMode(1800, 1000), "SFML works!");
	
	Body planet(50.f, 125000000);
	planet.setPosition({ 500.f, 500.f });

	constexpr float framerate = 60.f;
	window.setFramerateLimit(unsigned int(framerate));
	sf::Clock framerateClock;
	
	Body moon(10.f, 10.f);
	moon.setPosition({ 500.f, 250.f });

	moon.setVelocity({ speedForCircularOrbit(moon, planet), 0.f});
	//planet.setVelocity({ -speedForCircularOrbit(planet, moon), 0.f });
	//planet.setVelocity( -(moon.getVelocity() * moon.getMass()) / planet.getMass() );

	KinematicOrbiter kinematicMoon{10.f, 10.f};
	kinematicMoon.setPosition(moon.getPosition());
	kinematicMoon.setOrbitTarget(&planet, true);

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

		// NOTE: Putting step before gravitate doesn't seem to make much difference...

		gravitate(moon, planet, timeStep);
		gravitate(planet, moon, timeStep);

		planet.step(timeStep);
		moon.step(timeStep);
		kinematicMoon.step(timeStep);

		window.clear();
		planet.draw(window);
		moon.draw(window);
		kinematicMoon.draw(window);
		hud.update(moon, planet);
		hud.draw(window);
		window.display();

		framerateClock.restart();
	}

	return 0;
}
