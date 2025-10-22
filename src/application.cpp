#include "application.h"
#include "mainMenuScene.h"
#include "sceneManager.h"
#include<memory>

void Application::run() {
	SceneManager::push(std::move(std::make_unique<MainMenuScene>()));
	float dt = float(1.0 / 60);
	while (mWindow.isOpen()) {
		while (const std::optional<sf::Event> event = mWindow.pollEvent()) {
			if (event->is<sf::Event::Closed>()) Window::close(); //close window in singleton

			SceneManager::handlerEvent(*event);
		}
		SceneManager::update(dt);
		mWindow.clear(sf::Color::White);
		SceneManager::render(mWindow);

	}

}