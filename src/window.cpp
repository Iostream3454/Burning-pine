#include "window.h"

//create window with title
Window::Window(uint16_t width, uint16_t height, std::string title): window_({ sf::VideoMode({ width, height }), title }) {}

void Window::run()
{
	while (window_.isOpen()) //window main loop
	{
		while (const std::optional<sf::Event> ev = window_.pollEvent())//sfml catch events
		{
			if (ev->is<sf::Event::Closed>())//sfml close evnt(nessesary)
			{
				window_.close();
			}
		}
	}
}