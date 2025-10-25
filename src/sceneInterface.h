#pragma once
#include<TGUI/Backend/SFML-Graphics.hpp>

class IScene {
public:
	virtual void ready() = 0;
	virtual void handlerEvent(const sf::Event& ev) = 0;
	virtual void update(float& dt) = 0;
	virtual void render(sf::RenderWindow& win) = 0;
	~IScene() = default;
};
