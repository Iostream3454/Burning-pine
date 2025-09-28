#pragma once
#include "Scene.h"
#include<memory>

class SceneManager {
public:

	void changeScene(IScene*& newScene) {
		currentScene_ = newScene;
		currentScene_->ready_();
	}

	inline void updateScene(float& deltaTime) {
		currentScene_->update_(deltaTime);
	}

	inline IScene* getCurrScene() { return currentScene_; }


private:
	IScene* currentScene_ = nullptr;
};