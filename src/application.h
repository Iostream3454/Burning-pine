#pragma once
//local .h
#include "window.h"

class Application {
public:
	void run();
private:
	sf::RenderWindow& mWindow = Window::instance();
};
