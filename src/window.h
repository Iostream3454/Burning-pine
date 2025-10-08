#pragma once
//std includes
#include <iostream>
//sfml Tgui includes
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class Window 
{
public:
	Window(uint16_t wight, uint16_t hight, std::string title);

	void run();
private:
	sf::RenderWindow window_;
};