#include "mainMenuScene.h"
#include "gameScene.h"
#include "sceneManager.h"


void GameScene::ready() {
	tgui::Button::Ptr butt = tgui::Button::create("MainMenu");
	butt->setHeight(50);
	butt->setWidth(150);
	mGuiLayer.add(butt, "mainMenu");
	mCharacter.setPosition({ 200.f, 200.f });
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
	}
}

void GameScene::render(sf::RenderWindow& win) {
	mGuiLayer.draw();
	win.draw(mCharacter);
	win.display();
}

void GameScene::update(float& dt) {
	if (mCharacter.getHasGoal()) {
		mCharacter.move();
	}
}