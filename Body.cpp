#include "Body.h"

Body::Body(float radius, float mass, sf::Color color)
	:_visual(radius),
	_mass(mass)
{
	_visual.setFillColor(color);
	_visual.setOrigin({ radius, radius});
}


void Body::step(float dt) {
	setPosition(getPosition() + _velocity * dt);
}
