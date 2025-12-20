#pragma once
//local .h
#include "window.h"

class Application {
public:
	void run();
private:
	sf::RenderWindow&	mWindow = Window::instance();					//ссылка на окно рендера
	sf::Clock			mClock;											//технические часы
	float				mTargetFps = 60.0;								//целевой ФПС
	sf::Time			mTargetTps = sf::seconds((1.f / mTargetFps));	//целевой ТПС
};
