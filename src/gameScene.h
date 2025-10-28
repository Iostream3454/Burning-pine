#pragma once

#include "sceneInterface.h"
#include "window.h"
#include "character.h"

class GameScene : public IScene {
public:
	void ready() override;
	void handlerEvent(const sf::Event& ev) override;
	void update(float& dt) override;
	void render(sf::RenderWindow& win) override;
private:
	tgui::Gui		mGuiLayer{ Window::instance() };
	MainCharacter	mCharacter;
};
