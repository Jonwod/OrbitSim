#pragma once
#include <SFML/Graphics.hpp>

typedef sf::Vector2f Vec2;


class Body: public sf::Transformable {
public:
	Body(float radius, float mass, sf::Color color = sf::Color::Green);
	//Steps this body forward by dt seconds
	virtual void step(float dt);
	inline const float& getMass() const { return _mass; };
	inline void setVelocity(const Vec2& newVelocity) { _velocity = newVelocity; }
	inline const Vec2& getVelocity() const { return _velocity; }
	inline void draw(sf::RenderWindow& window) { 
		_visual.setPosition(getPosition());
		window.draw(_visual); 
	}
	inline void applyImpulse(const Vec2& impulse) { _velocity += impulse / getMass(); }
private:
	sf::CircleShape _visual;
	Vec2 _velocity{ 0.f, 0.f };
	float _mass;
};
