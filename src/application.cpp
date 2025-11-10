#include <memory>
#include <chrono>

#include "application.h"
#include "mainMenuScene.h"
#include "sceneManager.h"

void Application::run() {
	SceneManager::push(std::move(std::make_unique<MainMenuScene>()));
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (mWindow.isOpen()) {

		while (const std::optional<sf::Event> event = mWindow.pollEvent()) {
			if (event->is<sf::Event::Closed>()) Window::close(); //close window in singleton
			SceneManager::handlerEvent(*event);
		}
		timeSinceLastUpdate += mClock.restart();
		while (timeSinceLastUpdate > mTargetTps)
		{
			while (const std::optional<sf::Event> event = mWindow.pollEvent()) {
				if (event->is<sf::Event::Closed>()) Window::close(); //close window in singleton
				SceneManager::handlerEvent(*event);
			}
			timeSinceLastUpdate -= mTargetTps;
			SceneManager::update(mTargetTps.asSeconds());
		}
		
		mWindow.clear(sf::Color::White);
		SceneManager::render(mWindow);

	}

}