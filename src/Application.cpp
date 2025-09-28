#include"Application.h"

Application::Application() : window_(sf::VideoMode({ 200, 200 }), "SFML Works"), gui_(window_)//подключение gui к окну
{
	window_.setVerticalSyncEnabled(true);//вертикальная синхронизация
	window_.setFramerateLimit(60);
}

void Application::runApplication()
{
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Cyan);
	IScene* tScene = new MenuScene();
	IScene* tGScene = new GameScene();
	sceneManager_.changeScene(tScene);
	while (window_.isOpen()) {//основной цикл
		timeManager_.updateTime();
		while (const std::optional<sf::Event> ev = window_.pollEvent())
		{
			gui_.handleEvent(*ev);

			if (ev->is<sf::Event::Closed>())
			{
				window_.close(); 
			}
			else if (const auto * key = ev->getIf<sf::Event::KeyPressed>())
			{
				if(key->scancode == sf::Keyboard::Scancode::Q)
				{
					if (sceneManager_.getCurrScene() == tScene)  sceneManager_.changeScene(tGScene);
					else if (sceneManager_.getCurrScene() == tGScene)  sceneManager_.changeScene(tScene);
				}else if(key->scancode == sf::Keyboard::Scancode::Escape) window_.close();
					
			}
		}
		float dt = timeManager_.getDeltaTime();
		sceneManager_.updateScene(dt);
	}
	delete tScene; delete tGScene;
}