#include"Application.h"

Application::Application() : window_(sf::VideoMode({ 200, 200 }), "SFML Works"), gui_(window_)
{
	window_.setVerticalSyncEnabled(true);
}

void Application::runApplication()
{
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Cyan);

	while (window_.isOpen()) {
		while (const std::optional event = window_.pollEvent())
		{
			gui_.handleEvent(*event);

			if (event->is<sf::Event::Closed>())
				window_.close();
		}
	}
}