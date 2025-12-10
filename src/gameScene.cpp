#include "mainMenuScene.h"
#include "gameScene.h"
#include "sceneManager.h"
#include "timeSystem.h"


void GameScene::ready() {
	mThirstyLabel = IconTextWidget::create();
	mIsSleepLabel = tgui::Label::create("You are sleep... Press any button to cancel");
	mHungryLabel = IconTextWidget::create();
	mRadiationLabel = IconTextWidget::create();
	mStaminaLabel = IconTextWidget::create();
	mBleadingLabel = IconTextWidget::create();
	mExhaustionLabel = IconTextWidget::create();
	mTopPanel = tgui::Panel::create({ "100%", "6%" });
	mBottomPanel = tgui::Panel::create({"100%", "6%"}); mBottomPanel->setAutoLayout(tgui::AutoLayout::Bottom);
	mBottomPanel->getRenderer()->setBackgroundColor(tgui::Color::Green);
	tgui::HorizontalLayout::Ptr row = tgui::HorizontalLayout::create({ "100%", "100%" });
	mMainMenuButtton = tgui::Button::create("Main\nmenu");
	mTimeLabel = tgui::Label::create(this->mTimeSystem.show());
	mIsSleepLabel->setVisible(false);
	mTimeLabel->setOrigin({ 0.5f, 0.5f });
	mIsSleepLabel->setOrigin({ 0.5f, 0.5f });
	mIsSleepLabel->setPosition({ "50%", "50%" });
	mIsSleepLabel->getRenderer()->setBackgroundColor(tgui::Color::applyOpacity(tgui::Color::Black, 0.3f));
	mIsSleepLabel->getRenderer()->setTextColor(tgui::Color::White);



	mTimeLabelPic = tgui::Picture::create(tgui::Texture("gfx/televizor.jpg"));
	mTimeLabelPic->setOrigin({ 0.5f, 0.5f });
	mBottomPanel->add(mTimeLabelPic, "TELIK");
	mTimeLabelPic->setPosition({"50%", "45%"});
	mBottomPanel->add(mTimeLabel, "TIME_TEXT");
	mBottomPanel->getRenderer()->setTextureBackground(tgui::Texture({ "gfx/bottom.png" }));

	mTimeLabel->setPosition({ "50%", "50%" });

	mTimeLabel->getRenderer()->setTextColor(tgui::Color(145, 250, 159));

	auto seterForTextLebelNeed = [&](IconTextWidget::Ptr& label, 
		const std::string&& fon, 
		const std::string&& icon,
		int value
		) {
		label->getRenderer()->setTextureBackground(tgui::Texture({ fon }));
		label->mIcon = tgui::Picture::create(tgui::Texture({ icon }));
		label->mIcon->setOrigin({ 0.5f, 0.5f });
		label->mIcon->setPosition({ "20%", "50%" });
		label->add(label->mIcon, "ICON");
		label->mText = tgui::Label::create(std::to_string(value));
		label->add(label->mText, "TEXT");
		label->mText->getRenderer()->setTextColor(tgui::Color::Green);
		label->mText->setOrigin({ 0.5f, 0.5f });
		label->mText->setPosition(label->mIcon->getPositionLayout().x + 70, label->mIcon->getPositionLayout().y);
	};
	
	row->add(mExhaustionLabel, "EXHUSTION");
	row->add(mThirstyLabel, "THIRST");
	row->add(mHungryLabel, "HUNGRY");
	row->add(mStaminaLabel, "STAMINA");
	row->add(mRadiationLabel, "RADIATION");
	row->add(mBleadingLabel, "BLEADING");
	row->add(mMainMenuButtton, "MAIN_MENU_BUTTON");

	mTopPanel->add(row, "ROW");
	mTopPanel->getRenderer()->setBackgroundColor(tgui::Color(25, 26, 25, 125));

	mGuiLayer.add(mTopPanel, "PANEL");
	mGuiLayer.add(mIsSleepLabel,"SLEEP_LABLE");
	mGuiLayer.add(mBottomPanel, "BOTTOM");

	seterForTextLebelNeed(mExhaustionLabel, "gfx/fon.png", "gfx/skull.png", this->mCharacter.getBody().getExhaustionLevel());
	seterForTextLebelNeed(mThirstyLabel, "gfx/fon.png", "gfx/drink_water.png", this->mCharacter.getBody().getThirstLevel());
	seterForTextLebelNeed(mStaminaLabel, "gfx/fon.png", "gfx/stamina.png", this->mCharacter.getBody().getStaminaLevel());
	seterForTextLebelNeed(mHungryLabel, "gfx/fon.png", "gfx/hungry.png", this->mCharacter.getBody().getHungryLevel());
	seterForTextLebelNeed(mRadiationLabel, "gfx/fon.png", "gfx/radioactive.png", this->mCharacter.getBody().getRadiationLevel());
	seterForTextLebelNeed(mBleadingLabel, "gfx/fon.png", "gfx/blood.png", this->mCharacter.getBody().getBleadingLevel());
}

void GameScene::handlerEvent(const sf::Event& ev) {
	bool guiClick = mGuiLayer.handleEvent(ev);
	
	if (mGuiLayer.get("MAIN_MENU_BUTTON").get()->isMouseDown()) {
		mGuiLayer.removeAllWidgets();
		SceneManager::push(std::move(std::make_unique<MainMenuScene>()));
	}
	if(!guiClick)
	{
		if (const auto* mouseButtonPressed = ev.getIf<sf::Event::MouseButtonPressed>())//нажатия мыши
		{
			if (mouseButtonPressed->button == sf::Mouse::Button::Left)
			{
 				mCharacter.setPositionGoal(ev);
			}
		}

		if (const auto* keyboardButtonPressed = ev.getIf<sf::Event::KeyPressed>())//нажатия клавы
		{

			if(keyboardButtonPressed->scancode == sf::Keyboard::Scancode::Space)
			{
				if(mCharacter.hasGoal())
				{
					mCharacter.setIsMoving();
					std::cout << mCharacter.getIsDoSomthing() << std::endl;
				}
			}
			else if (keyboardButtonPressed->scancode == sf::Keyboard::Scancode::L) {
				mCharacter.trySleep();
				mIsSleepLabel->setVisible(mCharacter.getBody().isSleep()? true : false);
			}

			if (keyboardButtonPressed->scancode != sf::Keyboard::Scancode::L && mCharacter.getBody().isSleep()) {//выход из сна при действиях
				mCharacter.trySleep();
				mIsSleepLabel->setVisible(false);
			}
		}

		if (const auto* mouseScrolledEvent = ev.getIf<sf::Event::MouseWheelScrolled>()) {//прокрутка колесиком мыши
			mCharacter.zoomCamera(mouseScrolledEvent->delta);
		}
	}
}

void GameScene::render(sf::RenderWindow& win) {
	win.draw(mCharacter);
	mGuiLayer.draw();
	win.display();
}

void GameScene::update(float& dt) {
	if (mCharacter.getIsDoSomthing()) {
		if (mCharacter.isMoving()) {
			mCharacter.move(dt);
		}
		if (mTimeSystem.increaseByMinutes(dt))
		{
			if (mCharacter.getBody().getStaminaLevel() > 98 || mCharacter.getBody().getThirstLevel() > 98 || mCharacter.getBody().getHungryLevel() > 98) {
				mCharacter.trySleep();
				mIsSleepLabel->setVisible(false);
			}
			this->mCharacter.updateNeeds();
			this->updateNeedsText();
		}
		this->mTimeLabel.get()->setText(mTimeSystem.show());
	}
}

void GameScene::updateNeedsText() {
	this->mExhaustionLabel->mText->setText(std::to_string(this->mCharacter.getBody().getExhaustionLevel()));
	this->mThirstyLabel->mText->setText(std::to_string(this->mCharacter.getBody().getThirstLevel()));
	this->mHungryLabel->mText->setText(std::to_string(this->mCharacter.getBody().getHungryLevel()));
	this->mRadiationLabel->mText->setText(std::to_string(this->mCharacter.getBody().getRadiationLevel()));
	this->mBleadingLabel->mText->setText(std::to_string(this->mCharacter.getBody().getBleadingLevel()));
	this->mStaminaLabel->mText->setText(std::to_string(this->mCharacter.getBody().getStaminaLevel()));
}