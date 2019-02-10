#pragma once
#include <SFML/Graphics.hpp>
#include "Body.h"

// ~~~~~~~~~HUD~~~~~~~~~~~~

class HUD {
public:
	HUD(const Body& orbiter, const Body& centerBody);

	void update(const Body& orbiter, const Body& centerBody);

	void draw(sf::RenderWindow& window) const;
private:
	sf::Font _font;
	const float _startRadius;
	float _maxError = 0.f;

	sf::Text startRadiusText{ "start radius: ", _font };
	sf::Text currentRadiusText{ "current radius: ", _font };
	sf::Text errorText{ "error: ", _font };
	sf::Text maxErrorText{ "max error: ", _font };
};

//