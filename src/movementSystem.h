#pragma once
#include <SFML/Graphics.hpp>

//класс отвечает за перемещение объекта
class MovementSystem {
public:

	MovementSystem(sf::Vector2f&& objectStartPosition) : mTargetObjPosition(objectStartPosition) {}

	bool move(float& dt, sf::Shape& moveAbleObject) {
		mTargetObjPosition = moveAbleObject.getPosition();

		float distance = sqrt(
			(mGoalTargetPosition.x - mTargetObjPosition.x) * (mGoalTargetPosition.x - mTargetObjPosition.x) +
			(mGoalTargetPosition.y - mTargetObjPosition.y) * (mGoalTargetPosition.y - mTargetObjPosition.y)
		);//считаем дистанцию (длину от точки ј до точки Ѕ). формула длины вектора

		if (distance > 4.f) {//этим условием убираем дергание во врем€ конечной позиции спрайта
			mTargetObjPosition.x += dt * mBaseCharacterSpeed * (mGoalTargetPosition.x - mTargetObjPosition.x) / distance;//идем по иксу с помощью вектора нормали
			mTargetObjPosition.y += dt * mBaseCharacterSpeed * (mGoalTargetPosition.y - mTargetObjPosition.y) / distance;//идем по игреку так же
			moveAbleObject.setPosition(mTargetObjPosition);
			return mHasGoal = mIsMoving = true;
		}
		else {
			return mHasGoal = mIsMoving = false;
		}//говорим что уже никуда не идем 

	}

	sf::Vector2f& getTargetObjPosition() { return mTargetObjPosition; }

	sf::Vector2f& getGoalTargetPosition() { return mGoalTargetPosition; }

	void setGoalTargetPosition(sf::Vector2f targetValue) { mGoalTargetPosition = targetValue; mHasGoal = true; }

	bool isMoving() const { return mIsMoving; }
	bool hasGoal() const { return mHasGoal; }

	void startMove() { mIsMoving = true; }
	void stopMove() { mIsMoving = false; }
private:
	sf::Vector2f	mTargetObjPosition = { 0.f, 0.f };				// позици€ объекта 
	sf::Vector2f	mGoalTargetPosition = { 0.f, 0.f };				// позици€ цели
	const float		mBaseCharacterSpeed = 300.0f;					// базова€ скорость
	float			mCurrentCharacterSpeed = mBaseCharacterSpeed * 1;	// скорость с модификаторами

	bool			mHasGoal = false;					// поставлена ли точка, куда надо идти
	bool			mIsMoving = false;					// идет ли игрок
};