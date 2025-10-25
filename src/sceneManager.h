#pragma once

#include<stack>

#include "sceneInterface.h"
#include "mainMenuScene.h"

class SceneManager {
public:

	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	SceneManager(SceneManager&&) = delete;
	SceneManager& operator=(SceneManager&&) = delete;

	static void push(std::unique_ptr<IScene> scene) {
		if (!mSceneStack.empty()) mSceneStack.pop();;
		mSceneStack.push(std::move(scene));
		mSceneStack.top()->ready();
	}

	static void pop() {
		if (mSceneStack.empty()) return;
		mSceneStack.pop();
		mSceneStack.top()->ready();
	}

	static void ready() {
		if (mSceneStack.empty()) return;
		mSceneStack.top()->ready();
	}

	static void handlerEvent(const sf::Event& ev) {
		if (mSceneStack.empty()) return;
		mSceneStack.top()->handlerEvent(ev);
	}

	static void update(float& dt) {
		if (mSceneStack.empty()) return;
		mSceneStack.top()->update(dt);
	}

	static void render(sf::RenderWindow& win) {
		if (mSceneStack.empty()) return;
		mSceneStack.top()->render(win);
	}

private:
	SceneManager() {};

	~SceneManager() = default;
	static std::stack<std::unique_ptr<IScene>> mSceneStack;
};

