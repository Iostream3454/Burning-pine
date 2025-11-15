#include "mainMenuScene.h"
#include "gameScene.h"
#include "sceneManager.h"
#include "timeSystem.h"


void GameScene::ready() {
	mThirstyLabel = IconTextWidget::create();
	mHungryLabel = IconTextWidget::create();
	mRadiationLabel = IconTextWidget::create();
	mStaminaLabel = IconTextWidget::create();
	mBleadingLabel = IconTextWidget::create();
	mExhaustionLabel = IconTextWidget::create();
	mTopPanel = tgui::Panel::create({ "100%", "8%" });
	tgui::HorizontalLayout::Ptr row = tgui::HorizontalLayout::create({ "100%", "100%" });
	mMainMenuButtton = tgui::Button::create("Main\nmenu");
	mTimeLabel = tgui::Label::create(this->mTimeSystem.show());
	
	mTimeLabel->getRenderer()->setTextureBackground(tgui::Texture({"gfx/televizor.jpg"}));
	mTimeLabel->getRenderer()->setTextColor(tgui::Color(75, 130, 72));

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
	mTopPanel->getRenderer()->setBackgroundColor(tgui::Color::Black);

	mGuiLayer.add(mTopPanel, "PANEL");

	seterForTextLebelNeed(mExhaustionLabel, "gfx/fon.png", "gfx/skull.png", this->mCharacter.getBody().getExhaustionLevel());
	seterForTextLebelNeed(mThirstyLabel, "gfx/fon.png", "gfx/drink_water.png", this->mCharacter.getBody().getThirstLevel());
	seterForTextLebelNeed(mStaminaLabel, "gfx/fon.png", "gfx/stamina.png", this->mCharacter.getBody().getStaminaLevel());
	seterForTextLebelNeed(mHungryLabel, "gfx/fon.png", "gfx/hungry.png", this->mCharacter.getBody().getHungryLevel());
	seterForTextLebelNeed(mRadiationLabel, "gfx/fon.png", "gfx/radioactive.png", this->mCharacter.getBody().getRadiationLevel());
	seterForTextLebelNeed(mBleadingLabel, "gfx/fon.png", "gfx/blood.png", this->mCharacter.getBody().getBleadingLevel());

	mGuiLayer.add(mTimeLabel, "TIME");
	mTimeLabel.get()->setAutoLayout(tgui::AutoLayout::Bottom);
	mTimeLabel.get()->setHorizontalAlignment(tgui::HorizontalAlignment::Center);
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
				mCharacter.setIsMoving(!mCharacter.getIsMoving());
			}
		}

		if (const auto* mouseScrolledEvent = ev.getIf<sf::Event::MouseWheelScrolled>()) {//прокрутка колесиком мыши
			if (mouseScrolledEvent->delta < 0.f) { //колесико вперед
				this->mCharacter.zoomIn();
			}
			else if (mouseScrolledEvent->delta > 0.f) {//колесико назад
				this->mCharacter.zoomOut();
			}
			Window::instance().setView(this->mCharacter.getView());
		}
	}
}

void GameScene::render(sf::RenderWindow& win) {
	win.draw(mCharacter);
	mGuiLayer.draw();
	win.display();
}

void GameScene::update(float& dt) {
	if (this->mCharacter.getHasGoal()) {
		this->mCharacter.move(dt);
		if (this->mCharacter.getIsMoving()) {
			if (this->mTimeSystem.increaseByMinutes(dt))
			{
				this->mCharacter.updateNeeds();
				this->mExhaustionLabel->mText->setText(std::to_string(this->mCharacter.getBody().getExhaustionLevel()));
				this->mThirstyLabel->mText->setText(std::to_string(this->mCharacter.getBody().getThirstLevel()));
				this->mHungryLabel->mText->setText(std::to_string(this->mCharacter.getBody().getHungryLevel()));
				this->mRadiationLabel->mText->setText(std::to_string(this->mCharacter.getBody().getRadiationLevel()));
				this->mBleadingLabel->mText->setText(std::to_string(this->mCharacter.getBody().getBleadingLevel()));
				this->mStaminaLabel->mText->setText(std::to_string(this->mCharacter.getBody().getStaminaLevel()));
			}
			this->mTimeLabel.get()->setText(mTimeSystem.show());
		}
	}
}