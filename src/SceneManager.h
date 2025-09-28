#pragma once
#include "Scene.h"
#include<memory>

class SceneManager {
public:

	void changeScene(IScene& newScene) {
		newScene._ready();
		currentScene_ = std::make_unique<IScene>(newScene);
	}

	inline void updateScene(float& deltaTime) {
		currentScene_.get()->_update(deltaTime);
	}

private:
	std::unique_ptr<IScene> currentScene_;
};