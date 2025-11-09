#pragma once

#include "sceneInterface.h"
#include "window.h"
#include "character.h"
#include "timeSystem.h"

class GameScene : public IScene {
public:
	void ready() override;
	void handlerEvent(const sf::Event& ev) override;
	void update(float& dt) override;
	void render(sf::RenderWindow& win) override;
private:
	tgui::Label::Ptr	l;
	tgui::Label::Ptr	mNeedsLable;
	tgui::Gui			mGuiLayer{ Window::instance() };
	MainCharacter		mCharacter;
	TimeSystem			mTimeSystem;

};
