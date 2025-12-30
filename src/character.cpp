#include "character.h"
#include "window.h"
#include "needs.h"

#include <memory>
#include <string>

MainCharacter::MainCharacter() :
	mMovement(sf::Vector2f({ 120.f, 230.f })),
	mLineBuilder(mMovement.getTargetObjPosition()),
	mPlayerCamera(mMovement.getTargetObjPosition(), sf::Vector2f(Window::instance().getSize())),
	mCirclePresent(std::move(std::make_unique<sf::CircleShape>()), mMovement.getTargetObjPosition())
{
	mPersonBody.addNeed(std::string("Hungry"), std::move(std::make_unique<Hungry>(0)));
	mPersonBody.addNeed(std::string("Thirst"), std::move(std::make_unique<Thirst>(0)));
	mPersonBody.addNeed(std::string("Stamina"), std::move(std::make_unique<Stamina>(0)));
}


bool MainCharacter::getIsDoSomthing() const { return mIs_doSomthing; }
void MainCharacter::commandToMove() {
	if (mMovement.hasGoal())
	{
		(mIs_doSomthing = !mIs_doSomthing) ? mMovement.startMove() : mMovement.stopMove();
	}
	std::cout << mIs_doSomthing << std::endl;
}

void MainCharacter::trySleep() {
	if (!mIs_doSomthing)
	{
		this->mPersonBody.goToSleep();
		mIs_doSomthing = true;
		return;
	}
	mIs_doSomthing = false;
	this->mPersonBody.breakSleep();
}

void MainCharacter::updateState(float& dt, bool timeStepIsPass) {
	if (mMovement.isMoving())
	{
		mIs_doSomthing = mMovement.move(dt, mCirclePresent);
		mPlayerCamera.cameraMove(mMovement.getTargetObjPosition());
		mLineBuilder.updateStartOfLine(mMovement.getTargetObjPosition());
	}

	if (timeStepIsPass) {
		mPersonBody.update();
	}
}

void MainCharacter::setPositionGoal(sf::Vector2f& goalPosition) {
	mMovement.setGoalTargetPosition(goalPosition);
	mLineBuilder.buildArrowLine(goalPosition, mMovement.getTargetObjPosition());
}

void MainCharacter::zoomCamera(const float wheelDelta) {
	mPlayerCamera.zoomCamera(wheelDelta);
}

NeedsManager& MainCharacter::getBody() { return mPersonBody; }

void MainCharacter::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	// apply the entity's transform -- combine it with the one that was passed by the caller
	states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

	// you may also override states.shader or states.blendMode if you want
	// draw the vertex array
	target.setView(mPlayerCamera.getCamera());

	if (mMovement.hasGoal()) target.draw(mLineBuilder);

	target.draw(mCirclePresent, states);
}