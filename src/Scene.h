#pragma once

class IScene {
public:
	virtual void ready_() = 0;
	virtual void update_(float deltaTime) = 0;
	virtual ~IScene() = default;
};