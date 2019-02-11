#include "KinematicOrbiter.h"
#include <iostream>
#include <cmath>
#include "Constants.h"
#include "VectorMath.h"

KinematicOrbiter::KinematicOrbiter(float radius, float mass)
	:Body(radius, mass, sf::Color::Red)
{
}


// Returns an angle in radians in the range 0<2pi where (0, 1) is 0 radians
// Tested and working for values between 0 and 2pi in increments of pi/2
// Also for vectors (1, 1) and (-1, -1)
float vectorAngle(const sf::Vector2f & vec) {
	const float first_quadrant_angle = fabs(vec.y) > 0.f ? atan(fabs(vec.x / vec.y)) : pi / 2.f;
	if (vec.x >= 0.f) {
		if (vec.y >= 0.f) {	// 1st quadrant
			return first_quadrant_angle;
		}
		else { // 2nd quadrant
			return pi - first_quadrant_angle;
		}
	}
	else {
		if (vec.y < 0.f) {  // 3rd quadrant
			return pi + first_quadrant_angle;
		}
		else {
			return 2 * pi - first_quadrant_angle;
		}
	}
}


// Formats the input angle in the range 0 - 2pi radians
// Tested and working for values 0, 2pi, 2pi + 1, -2pi -1, pi
float angleTo2pi(float angle) {
	// In 'onedians', a whole circal is equal to 1 degrees
	const float angle_in_onedians = angle / (2.f * pi);
	const int int_part = int(angle_in_onedians);
	const float normalized_angle_in_onedians = angle_in_onedians - int_part;
	// This is the angle in radians in the range 0-pi
	const float normalized_angle = normalized_angle_in_onedians * 2.f * pi;
	return normalized_angle >= 0.f ? normalized_angle : normalized_angle + 2.f * pi;
}


// Takes an angle, in radians and returns a unit vector representing the direction of the angle,
// starting at (0, 1) for 0 radians
sf::Vector2f angleToUnitVector(float angle) {
	return sf::Vector2f(sin(angle), cos(angle));
}


void KinematicOrbiter::step(float delta){
	if (orbitTarget) {
		const float orbitalPeriod = (2 * pi) / sqrt((G * orbitTarget->getMass()) / pow(radius, 3));
		const float angular_displacement = 2 * pi * (delta / orbitalPeriod);
		angular_position -= clockwise ? angular_displacement : -angular_displacement;
		setPosition(calcTargetPosition());
	}
}


void KinematicOrbiter::setOrbitTarget(const Body * newOrbitTarget, bool clockwise_in){
	orbitTarget = newOrbitTarget;
	const sf::Vector2f selfToTarget = getPosition() - newOrbitTarget->getPosition();
	radius = newOrbitTarget ? VMath::magnitude(selfToTarget) : 0.f;
	angular_position = vectorAngle(selfToTarget);
	clockwise = clockwise_in;
}


sf::Vector2f KinematicOrbiter::calcTargetPosition(){
	if (orbitTarget) {
		return orbitTarget->getPosition() + angleToUnitVector(angular_position) * radius;
	}
	return sf::Vector2f(0.f, 0.f);
}
