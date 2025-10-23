#include "sceneManager.h"

std::stack<std::unique_ptr<IScene>> SceneManager::mSceneStack = {};