#include"Application.h"

Application::Application() : window_(sf::VideoMode({ 200, 200 }), "SFML Works"), gui_(window_)//����������� gui � ����
{
	window_.setVerticalSyncEnabled(true);//������������ �������������
}

void Application::runApplication()
{
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Cyan);
	IScene* tScene = new MenuScene;
	IScene* tGScene = new GameScene;
	sceneManager_.changeScene(*tScene);
	while (window_.isOpen()) {//�������� ����
		timeManager_.updateTime();
		while (const std::optional event = window_.pollEvent())
		{
			gui_.handleEvent(*event);

			if (event->is<sf::Event::Closed>())
				window_.close();
		}
		float dt = timeManager_.getDeltaTime();
		sceneManager_.updateScene(dt);
	}
}