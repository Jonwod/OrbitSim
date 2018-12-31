#include "Body.h"

Body::Body(float radius)
	:_visual(radius)
{
	_visual.setFillColor(sf::Color::Green);
	_visual.setOrigin({ radius / 2.f, radius / 2.f });
}


void Body::step(float dt) {
	setPosition(getPosition() + _velocity * dt);
}
