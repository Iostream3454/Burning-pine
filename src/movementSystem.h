#pragma once
#include <SFML/Graphics.hpp>
#include "shapeTypes.h"
//класс отвечает за перемещение объекта
class MovementSystem {
public:

	MovementSystem(sf::Vector2f&& objectStartPosition);

	bool move(float& dt, ShapeType& moveAbleObject);

	sf::Vector2f& getTargetObjPosition();

	sf::Vector2f& getGoalTargetPosition();

	void setGoalTargetPosition(sf::Vector2f targetValue);

	bool isMoving() const;
	bool hasGoal() const;

	void startMove();
	void stopMove();
private:
	sf::Vector2f	mTargetObjPosition = { 0.f, 0.f };				// позиция объекта 
	sf::Vector2f	mGoalTargetPosition = { 0.f, 0.f };				// позиция цели
	const float		mBaseCharacterSpeed = 300.0f;					// базовая скорость
	float			mCurrentCharacterSpeed = mBaseCharacterSpeed * 1;	// скорость с модификаторами

	bool			mHasGoal = false;					// поставлена ли точка, куда надо идти
	bool			mIsMoving = false;					// идет ли игрок
};