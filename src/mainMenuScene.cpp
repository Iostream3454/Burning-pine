#include "mainMenuScene.h"
#include "gameScene.h"
#include "sceneManager.h"

void MainMenuScene::ready() {
	tgui::Label::Ptr gameName = tgui::Label::create("Burning pine");
	gameName->setHeight(50);  gameName->setTextSize(24);
	tgui::Button::Ptr butt = tgui::Button::create("Play");
	butt->setHeight(50);
	butt->setWidth(150);
	tgui::Button::Ptr butt2 = tgui::Button::create("Quit");
	butt2->setHeight(50);
	butt2->setWidth(150);
	butt2->onClick([] { Window::close(); });
	tgui::GrowVerticalLayout::Ptr vert = tgui::GrowVerticalLayout::create();
	vert->setWidth(250); vert->setHeight(300); //vert->setAutoLayout(tgui::AutoLayout::Top);
	vert.get()->add(gameName); vert.get()->add(butt, "Play"); vert.get()->add(butt2);
	vert->setPosition("50%", "50%"); vert->setOrigin(0.5f, 0.5f);
	gameName->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
	mGuiLayer.add(vert);
	//gameName->setPosition("50%", "50%");
	vert->getRenderer()->setSpaceBetweenWidgets(10);
	
}

void MainMenuScene::handlerEvent(const sf::Event& ev) {
	mGuiLayer.handleEvent(ev);
	if (mGuiLayer.get("Play").get()->isMouseDown()) {
		mGuiLayer.removeAllWidgets(); 
		SceneManager::push(std::move(std::make_unique<GameScene>()));
	}
}

void MainMenuScene::render(sf::RenderWindow& win) {
	mGuiLayer.draw();
	win.display();
}

void MainMenuScene::update(float& dt) {

}