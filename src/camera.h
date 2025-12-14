#pragma once

#include <SFML/Graphics.hpp>
#include "window.h"

class Camera {
public:

	Camera(sf::Vector2f cameraCenter, sf::Vector2f cameraSize) : mCameraViewport(cameraCenter, cameraSize) { }

	void cameraMove(sf::Vector2f& target) {
		mCameraViewport.setCenter(target);
	}

	sf::View getCamera() const {
		return mCameraViewport;
	}

	void setCameraCenter(const sf::Vector2f& position) {
		mCameraViewport.setCenter(position);
	} 

	void zoomCamera(const float wheelDelta) {
		if(wheelDelta < 0.f)
		{
			if (mSteps < mMaxStep)
			{
				++mSteps;
				mCameraViewport.zoom(mMaxZoom);
			}
		}
		else 
		{
			if (mSteps > mMinStep)
			{
				--mSteps;
				mCameraViewport.zoom(mMinZoom);
			}
		}
		Window::instance().setView(mCameraViewport);
	}


private:
	sf::View		mCameraViewport;			//	камера
	const float		mMaxZoom			= 2.0f; //	приближение камеры
	const float		mMinZoom			= 0.5f; //	удаление камеры
	short			mSteps				= 0;	//	текущее приближение
	const short		mMaxStep = 3, mMinStep = -3;//	границы приближения
};