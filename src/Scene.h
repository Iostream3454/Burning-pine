#pragma once

__interface IScene {
	void _ready() = 0;
	void _update(float deltaTime) = 0;
};