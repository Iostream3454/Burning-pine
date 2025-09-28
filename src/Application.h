#pragma once
#include<SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "TimeManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ScenesRealizations.h"

class Application {//этот класс является точкой создания оконного приложения 
public:
	Application();

	void runApplication();

private:
	sf::RenderWindow window_; //переменная окна
	tgui::Gui gui_;//переменная для подключения TGUI
	TimeManager timeManager_;
	SceneManager sceneManager_;//менеджер по переключению сцен
};