#include "mainMenuScene.h"
#include "gameScene.h"
#include "sceneManager.h"


void GameScene::ready() {
	tgui::Button::Ptr butt = tgui::Button::create("MainMenu");
	butt->setHeight(50);
	butt->setWidth(150);
	mGuiLayer.add(butt, "mainMenu");
}

void GameScene::handlerEvent(const sf::Event& ev) {
	mGuiLayer.handleEvent(ev);
	if (mGuiLayer.get("mainMenu").get()->isMouseDown()) {
		mGuiLayer.removeAllWidgets();
		SceneManager::push(std::move(std::make_unique<MainMenuScene>()));
	}
}

void GameScene::render(sf::RenderWindow& win) {
	mGuiLayer.draw();
	win.display();
}

void GameScene::update(float& dt) {

}