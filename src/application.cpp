#include "application.h"

void Application::run() {

	while (mWindow.isOpen()) {
		while (const std::optional<sf::Event> event = mWindow.pollEvent()) {
			if (event->is<sf::Event::Closed>()) Window::close(); //close window in singleton
		}

	}

}