#pragma once
#include<SFML/Graphics.hpp>

class TimeManager {
public:
	TimeManager() : deltaTime_(0.f) {}

	inline void updateTime() {
		deltaTime_ = sfCloack_.restart().asSeconds();
	}

	inline float getDeltaTime() { return deltaTime_; }
private:
	sf::Clock sfCloack_;
	float deltaTime_;
};