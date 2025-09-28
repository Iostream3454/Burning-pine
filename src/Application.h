#pragma once
#include<SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "TimeManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ScenesRealizations.h"

class Application {//���� ����� �������� ������ �������� �������� ���������� 
public:
	Application();

	void runApplication();

private:
	sf::RenderWindow window_; //���������� ����
	tgui::Gui gui_;//���������� ��� ����������� TGUI
	TimeManager timeManager_;
	SceneManager sceneManager_;//�������� �� ������������ ����
};