#pragma once
//local .h
#include "window.h"

class Application {
public:
	void run();
private:
	sf::RenderWindow& mWindow = Window::instance();
	sf::Clock mClock; 
	double mTargetFps = 60.0;
	sf::Time mTargetTps = sf::seconds((1.f / mTargetFps));
};
