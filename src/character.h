#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include "window.h"
#include "camera.h"
#include "needs.h"
#include "needsManager.h"
#include "movementSystem.h"
#include "arrowBuilder.h"
#include "shapeTypes.h"



class MainCharacter final : public sf::Drawable, public sf::Transformable
{
public:

	MainCharacter() : 
		mMovement(sf::Vector2f({ 120.f, 230.f })),
		mLineBuilder(mMovement.getTargetObjPosition()),
		mPlayerCamera(mMovement.getTargetObjPosition(), sf::Vector2f(Window::instance().getSize())),
		mCirclePresent(std::move(std::make_unique<sf::CircleShape>()), mMovement.getTargetObjPosition())
	{ 
		mPersonBody.addNeed(std::move(std::make_unique<Hungry>(0)));
		mPersonBody.addNeed(std::move(std::make_unique<Thirst>(0)));
		mPersonBody.addNeed(std::move(std::make_unique<Stamina>(0)));
	}

	
	bool getIsDoSomthing() const { return mIs_doSomthing; }
	void commandToMove() {
		if(mMovement.hasGoal())
		{
			(mIs_doSomthing = !mIs_doSomthing) ? mMovement.startMove() : mMovement.stopMove();
		}
		std::cout << mIs_doSomthing << std::endl;
	}

	void trySleep() {
		if(!mIs_doSomthing)
		{
			this->mPersonBody.goToSleep();
			mIs_doSomthing = true;
			return;
		}
		mIs_doSomthing = false;
		this->mPersonBody.breakSleep();
	}

	void updateState(float& dt, bool timeStepIsPass) {
		if (mMovement.isMoving())
		{
			mIs_doSomthing = mMovement.move(dt, mCirclePresent);
			mPlayerCamera.cameraMove(mMovement.getTargetObjPosition());
			mLineBuilder.updateStartOfLine(mMovement.getTargetObjPosition());
		}

		if (timeStepIsPass) {
			//mPersonBody.updateNeeds();
		}
	}

	void setPositionGoal(sf::Vector2f& goalPosition) {
		mMovement.setGoalTargetPosition(goalPosition);
		mLineBuilder.buildArrowLine(goalPosition, mMovement.getTargetObjPosition());
	}

	void zoomCamera(const float wheelDelta) {
		mPlayerCamera.zoomCamera(wheelDelta);
	}

	NeedsManager& getBody() { return mPersonBody; }

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		// apply the entity's transform -- combine it with the one that was passed by the caller
		states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

		// you may also override states.shader or states.blendMode if you want
		// draw the vertex array
		target.setView(mPlayerCamera.getCamera());

		if (mMovement.hasGoal()) target.draw(mLineBuilder);

		target.draw(mCirclePresent, states);
	}

	MovementSystem	mMovement;								//модуль дл€ передвижени€ объекта
	CircleType		mCirclePresent;
	ArrowLineSystem mLineBuilder;							//строитель линий со стрелкой
	Camera			mPlayerCamera;							//камера игрока
	NeedsManager	mPersonBody;							//тело персонажа

	bool			mIs_doSomthing				= false;
};