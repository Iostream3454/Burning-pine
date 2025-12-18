#pragma once
#include <SFML/Graphics.hpp>
#include "window.h"

sf::Vector2f getMouseCursorClick() {
	sf::Vector2i pixelPos = sf::Mouse::getPosition(Window::instance());//забираем коорд курсора
	return Window::instance().mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)
}