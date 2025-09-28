#pragma once
#include"Scene.h"
#include<iostream>

class MenuScene : public IScene{
public:
	void ready_() override {
		std::cerr << "You are in menu scene!\n";
	}

	void update_(float deltaTime) override {
		std::cerr << deltaTime << "\r\033[0K";
	}
};

class GameScene : public IScene {
public:
	void ready_() override {
		std::cerr << "You are in game scene!\n";
	}

	void update_(float deltaTime) override {
		std::cerr << deltaTime << "\r\033[0K";
	}
};