#include "movementSystem.h"


MovementSystem::MovementSystem(sf::Vector2f&& objectStartPosition) : mTargetObjPosition(objectStartPosition) {}

bool MovementSystem::move(float& dt, ShapeType& moveAbleObject) {
	//mTargetObjPosition = moveAbleObject.getPosition();

	float distance = sqrt(
		(mGoalTargetPosition.x - mTargetObjPosition.x) * (mGoalTargetPosition.x - mTargetObjPosition.x) +
		(mGoalTargetPosition.y - mTargetObjPosition.y) * (mGoalTargetPosition.y - mTargetObjPosition.y)
	);//считаем дистанцию (длину от точки А до точки Б). формула длины вектора

	if (distance > 4.f) {//этим условием убираем дергание во время конечной позиции спрайта
		mTargetObjPosition.x += dt * mBaseCharacterSpeed * (mGoalTargetPosition.x - mTargetObjPosition.x) / distance;//идем по иксу с помощью вектора нормали
		mTargetObjPosition.y += dt * mBaseCharacterSpeed * (mGoalTargetPosition.y - mTargetObjPosition.y) / distance;//идем по игреку так же
		moveAbleObject.setNewPosition(mTargetObjPosition);
		return mHasGoal = mIsMoving = true;
	}
	else {
		return mHasGoal = mIsMoving = false;
	}//говорим что уже никуда не идем 

}

sf::Vector2f& MovementSystem::getTargetObjPosition() { return mTargetObjPosition; }

sf::Vector2f& MovementSystem::getGoalTargetPosition() { return mGoalTargetPosition; }

void MovementSystem::setGoalTargetPosition(sf::Vector2f targetValue) { mGoalTargetPosition = targetValue; mHasGoal = true; }

bool MovementSystem::isMoving() const { return mIsMoving; }
bool MovementSystem::hasGoal() const { return mHasGoal; }

void MovementSystem::startMove() { mIsMoving = true; }
void MovementSystem::stopMove() { mIsMoving = false; }