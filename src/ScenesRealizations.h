#pragma once
#include"Scene.h"
#include<iostream>

class MenuScene : public IScene{
public:
	void _ready() override {
		std::cerr << "You are in menu scene!\n";
	}

	void _update(float deltaTime) override {
		std::cerr << deltaTime << "\r\033[0K";
	}
};

class GameScene : public IScene {
public:
	void _ready() override {
		std::cerr << "You are in game scene!\n";
	}

	void _update(float deltaTime) override {
		std::cerr << deltaTime << "\r\033[0K";
	}
};