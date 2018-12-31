#pragma once
#include <SFML/Graphics.hpp>

typedef sf::Vector2f Vec2;


class Body {
public:
	Body(float radius, float mass);
	//Steps this body forward by dt seconds
	void step(float dt);
	inline void setPosition(const Vec2& newPosition) { _visual.setPosition(newPosition); }
	inline const Vec2& getPosition() const { return _visual.getPosition(); };
	inline const float& getMass() const { return _mass; };
	inline void setVelocity(const Vec2& newVelocity) { _velocity = newVelocity; }
	inline const Vec2& getVelocity() const { return _velocity; }
	inline void draw(sf::RenderWindow& window) { window.draw(_visual); }
	inline void applyImpulse(const Vec2& impulse) { _velocity += impulse / getMass(); }
private:
	sf::CircleShape _visual;
	Vec2 _velocity{ 0.f, 0.f };
	float _mass;
};
