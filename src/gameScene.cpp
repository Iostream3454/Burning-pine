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
	mNeedsLable = tgui::Label::create("1");
	mGuiLayer.add(mNeedsLable, "needsLable");
	mNeedsLable.get()->setAutoLayout(tgui::AutoLayout::Top);
	mNeedsLable.get()->setAutoLayoutUpdateEnabled(true);
	mNeedsLable.get()->setHorizontalAlignment(tgui::HorizontalAlignment::Center);
	l.get()->setAutoLayout(tgui::AutoLayout::Bottom);
	l.get()->setAutoLayoutUpdateEnabled(true);
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
	if (mCharacter.getHasGoal()) {
		mCharacter.move(dt);
		if (mCharacter.getIsMoving()) {
			if (mTimeSystem.increaseByMinutes(dt)) 
			{
				this->mCharacter.updateNeeds();
				mNeedsLable.get()->setText(this->mCharacter.showNeeds());
			}
			l.get()->setText(mTimeSystem.show());
		}
	}
}