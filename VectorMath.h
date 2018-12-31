#pragma once
#include "SFML\System\Vector2.hpp"

namespace VMath {

	//returns clampee clamped between min and max
	template <class T> T clamp(T clampee, T min, T max) {
		if (clampee < min) {
			clampee = min;
		}
		else if (clampee > max) {
			clampee = max;
		}
		return clampee;
	}

	template <class T> inline T magnitude(sf::Vector2<T> vec) {
		return sqrt(vec.x * vec.x + vec.y * vec.y);
	}

	//does not check for length 0
	template <class T> sf::Vector2<T> normal(sf::Vector2<T> vec) {
		return vec / magnitude(vec);
	}

	template <class T> sf::Vector2<T> safeNormal(sf::Vector2<T> vec) {
		const float mag = magnitude(vec);
		if (mag > 0.001f) {
			return vec / mag;
		}
		return sf::Vector2<T>{};
	}

}
