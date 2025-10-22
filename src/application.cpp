#include "application.h"
#include "mainMenuScene.h"
#include<memory>

void Application::run() {
	//MainMenuScene mmScene;
	std::unique_ptr<IScene> mm = std::make_unique<MainMenuScene>();
	mm->ready(); float dt = float(1.0 / 60);
	while (mWindow.isOpen()) {
		while (const std::optional<sf::Event> event = mWindow.pollEvent()) {
			if (event->is<sf::Event::Closed>()) Window::close(); //close window in singleton

			mm->handlerEvent(*event);
		}
		mm->update(dt);
		mWindow.clear(sf::Color::White);
		mm->render(mWindow);

	}

}