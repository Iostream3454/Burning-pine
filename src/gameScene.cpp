#include "mainMenuScene.h"
#include "gameScene.h"
#include "sceneManager.h"
#include "timeSystem.h"


void GameScene::ready() {
	tgui::Button::Ptr butt = tgui::Button::create("MainMenu");
	butt->setHeight(50);
	butt->setWidth(150);
	l = tgui::Label::create("1");
	mGuiLayer.add(butt, "mainMenu");
	mGuiLayer.add(l, "lable");
	l.get()->setAutoSize(true);
	l.get()->setAutoLayout(tgui::AutoLayout::Bottom);
	l.get()->setHorizontalAlignment(tgui::HorizontalAlignment::Center);
}

void GameScene::handlerEvent(const sf::Event& ev) {
	bool guiClick = mGuiLayer.handleEvent(ev);
	
	if (mGuiLayer.get("mainMenu").get()->isMouseDown()) {
		mGuiLayer.removeAllWidgets();
		SceneManager::push(std::move(std::make_unique<MainMenuScene>()));
	}
	if(!guiClick)
	{
		mCharacter.setPositionGoal(ev);
		if (const auto* keyboardButtonPressed = ev.getIf<sf::Event::KeyPressed>())
		{
			if(keyboardButtonPressed->scancode == sf::Keyboard::Scancode::Space)
			{
				mCharacter.setIsMoving(!mCharacter.getIsMoving());
			}
		}
	}
}

void GameScene::render(sf::RenderWindow& win) {
	mGuiLayer.draw();
	win.draw(mCharacter);
	win.display();
}

void GameScene::update(float& dt) {
	if (mCharacter.getHasGoal()) {
		mCharacter.move(dt);
		if (mCharacter.getIsMoving()) {
			mTimeSystem.increaseByMinutes(dt);
			l.get()->setText(mTimeSystem.show());
		}
	}
}