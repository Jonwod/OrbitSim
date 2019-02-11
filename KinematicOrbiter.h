#pragma once
#include "Body.h"
#include <SFML/Graphics.hpp>


class KinematicOrbiter: public Body
{
public:
	KinematicOrbiter(float radius, float mass);
	virtual void step(float delta) override;
	// Will maintain initial radius
	void setOrbitTarget(const Body * newOrbitTarget, bool clockwise);
private:
	// Returns what the current position should be in world space based on 
	// the current angular position and radius, relative to the orbit target.
	sf::Vector2f calcTargetPosition();
	const Body * orbitTarget;
	float radius = 0.f;
	float angular_position = 0.f;
	bool clockwise = true;
};
