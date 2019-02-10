#include "HUD.h"
#include <iostream>
#include "VectorMath.h"


HUD::HUD(const Body& orbiter, const Body& centerBody)
	:_startRadius(VMath::magnitude(orbiter.getPosition() - centerBody.getPosition()))
{
	if (!_font.loadFromFile("arial.ttf"))
		std::cout << "Error. arial.ttf not found\n";

	startRadiusText.setCharacterSize(14);
	currentRadiusText.setCharacterSize(14);
	errorText.setCharacterSize(14);
	maxErrorText.setCharacterSize(14);

	startRadiusText.setPosition({ 10.f, 0.f });
	currentRadiusText.setPosition({ 10.f, 20.f });
	errorText.setPosition({ 10.f, 40.f });
	maxErrorText.setPosition({ 10.f, 60.f });

	startRadiusText.setString("start radius: " + std::to_string(_startRadius));
}


void HUD::update(const Body& orbiter, const Body& centerBody) {
	const float radius = VMath::magnitude(orbiter.getPosition() - centerBody.getPosition());
	const float error = radius - _startRadius;
	_maxError = std::max(std::fabs(error), _maxError);
	currentRadiusText.setString("current radius: " + std::to_string(radius));
	errorText.setString("error : " + std::to_string(error));
	maxErrorText.setString("max error: " + std::to_string(_maxError));
}


void HUD::draw(sf::RenderWindow& window) const {
	window.draw(startRadiusText);
	window.draw(currentRadiusText);
	window.draw(errorText);
	window.draw(maxErrorText);
}