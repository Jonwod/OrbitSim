#include "Body.h"

Body::Body(float radius, float mass)
	:_visual(radius),
	_mass(mass)
{
	_visual.setFillColor(sf::Color::Green);
	_visual.setOrigin({ radius, radius});
}


void Body::step(float dt) {
	setPosition(getPosition() + _velocity * dt);
}
