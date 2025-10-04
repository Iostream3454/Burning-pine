#pragma once
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
class IScene {
public:
	virtual void handleEvent_(const sf::Event&) = 0;
	virtual void ready_() = 0;
	virtual void update_(float deltaTime) = 0;
	virtual ~IScene() = default;
};