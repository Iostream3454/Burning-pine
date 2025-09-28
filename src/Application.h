#pragma once
#include<SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class Application {
public:
	Application();

	void runApplication();

private:
	sf::RenderWindow window_;
	tgui::Gui gui_;
};