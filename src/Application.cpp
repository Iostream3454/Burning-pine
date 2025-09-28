#include"Application.h"

Application::Application() : window_(sf::VideoMode({ 200, 200 }), "SFML Works"), gui_(window_)//подключение gui к окну
{
	window_.setVerticalSyncEnabled(true);//вертикальная синхронизация
}

void Application::runApplication()
{
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Cyan);

	while (window_.isOpen()) {//основной цикл
		timeManager_.updateTime();
		while (const std::optional event = window_.pollEvent())
		{
			gui_.handleEvent(*event);

			if (event->is<sf::Event::Closed>())
				window_.close();
		}
	}
}