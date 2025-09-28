#pragma once
#include "Scene.h"
#include<memory>

class SceneManager {
public:

	void changeScene(IScene& newScene) {
		currentScene_ = std::make_unique<IScene>(newScene);
	}

private:
	std::unique_ptr<IScene> currentScene_;
};