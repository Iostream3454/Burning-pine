#pragma once

#include "sceneInterface.h"
#include "window.h"
#include "character.h"
#include "timeSystem.h"
#include "tguiUtils.h"

class GameScene : public IScene {
public:
	void ready() override;
	void handlerEvent(const sf::Event& ev) override;
	void update(float& dt) override;
	void render(sf::RenderWindow& win) override;
private:
	tgui::Button::Ptr	mMainMenuButtton;
	tgui::Label::Ptr	mTimeLabel;
	tgui::Label::Ptr	mIsSleepLabel;

	tgui::Panel::Ptr	mTopPanel;
	tgui::Panel::Ptr	mBottomPanel;

	tgui::Picture::Ptr	mTimeLabelPic;
	IconTextWidget::Ptr mThirstyLabel;
	IconTextWidget::Ptr mHungryLabel;
	IconTextWidget::Ptr mBleadingLabel;
	IconTextWidget::Ptr mStaminaLabel;
	IconTextWidget::Ptr mRadiationLabel;
	IconTextWidget::Ptr mExhaustionLabel;
	MainCharacter		mCharacter;
	tgui::Gui			mGuiLayer{ Window::instance() };
	TimeSystem			mTimeSystem;

};
