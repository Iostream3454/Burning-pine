#include "camera.h"
#include "window.h"

Camera::Camera(sf::Vector2f cameraCenter, sf::Vector2f cameraSize) : mCameraViewport(cameraCenter, cameraSize) {}

void Camera::cameraMove(const sf::Vector2f& target) {
	mCameraViewport.setCenter(target);
}

sf::View Camera::getCamera() const {
	return mCameraViewport;
}

void Camera::zoomCamera(const float wheelDelta) {
	if (wheelDelta < 0.f)
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