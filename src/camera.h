#pragma once

#include <SFML/Graphics.hpp>

class Camera {
public:

	Camera(sf::Vector2f cameraCenter, sf::Vector2f cameraSize);

	void cameraMove(sf::Vector2f& target);

	sf::View getCamera() const;

	void setCameraCenter(const sf::Vector2f& position);

	void zoomCamera(const float wheelDelta);


private:
	sf::View		mCameraViewport;			//	камера
	const float		mMaxZoom			= 2.0f; //	приближение камеры
	const float		mMinZoom			= 0.5f; //	удаление камеры
	short			mSteps				= 0;	//	текущее приближение
	const short		mMaxStep = 3, mMinStep = -3;//	границы приближения
};