#pragma once
//std includes
#include <iostream>
//sfml Tgui includes
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class Window
{
public:
	static sf::RenderWindow& instance() {
		static Window singleton;
		return singleton.mWindow_;
	}

	Window(const Window&)				= delete;
	Window& operator=(const Window&)	= delete;
	Window(Window&&)					= delete;
	Window& operator=(Window&&)			= delete;
	static void close() {
		instance().close();
	}
private:
	Window() : mWindow_(sf::VideoMode({1200, 800}), "Burning pine") {};

	~Window()			= default;
	sf::RenderWindow	mWindow_;
};