#include "application.h"
#include "mainMenuScene.h"
#include<memory>

void Application::run() {
	MainMenuScene mmScene;
	mmScene.ready(); float dt = float(1.0 / 60);
	while (mWindow.isOpen()) {
		while (const std::optional<sf::Event> event = mWindow.pollEvent()) {
			if (event->is<sf::Event::Closed>()) Window::close(); //close window in singleton

			mmScene.handlerEvent(*event);
		}
		mmScene.update(dt);
		mWindow.clear(sf::Color::White);
		mmScene.render(mWindow);

	}

}