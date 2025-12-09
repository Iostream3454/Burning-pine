#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "window.h"
#include "camera.h"
#include "body.h"

class MovementSystem {
public:

	MovementSystem(sf::Vector2f&& objectStartPosition ) : mTargetObjPosition(objectStartPosition) {}

	bool move(float& dt, sf::Shape& moveAbleObject, sf::Vector2f& goalPosition) {
		mTargetObjPosition = moveAbleObject.getPosition();

		float distance = sqrt(
			(goalPosition.x - mTargetObjPosition.x) * (goalPosition.x - mTargetObjPosition.x) +
			(goalPosition.y - mTargetObjPosition.y) * (goalPosition.y - mTargetObjPosition.y)
		);//считаем дистанцию (длину от точки А до точки Б). формула длины вектора

		if (distance > 4.f) {//этим условием убираем дергание во время конечной позиции спрайта
			mTargetObjPosition.x += dt * mBaseCharacterSpeed * (goalPosition.x - mTargetObjPosition.x) / distance;//идем по иксу с помощью вектора нормали
			mTargetObjPosition.y += dt * mBaseCharacterSpeed * (goalPosition.y - mTargetObjPosition.y) / distance;//идем по игреку так же
			moveAbleObject.setPosition(mTargetObjPosition);
			//
			//mPlayerCamera.cameraMove(mCharacterPosition);
			return true;
		}
		else {
			return false;
		}//говорим что уже никуда не идем 

	}

	sf::Vector2f& getTargetObjPosition() { return mTargetObjPosition; }


private:
	sf::Vector2f	mTargetObjPosition = { 0.f, 0.f };													// позиция игрока 
	const float		mBaseCharacterSpeed = 300.0f;										//базовая скорость
	float			mCurrentCharacterSpeed = mBaseCharacterSpeed * 1;					// скорость с модификаторами
};


class ArrowLine : public sf::Drawable, public sf::Transformable {
public:
	ArrowLine(sf::Vector2f targetObjPosition = { 0.f, 0.f }, sf::Color lineColor = sf::Color::Blue) :
		mLineToGoal(sf::PrimitiveType::Lines, 2),
		mArrowToGoal(sf::PrimitiveType::LineStrip, 3)
	{
 		mLineToGoal[int(mLinePos::START)].position = targetObjPosition;
		mLineToGoal[int(mLinePos::START)].color = mLineToGoal[int(mLinePos::END)].color = lineColor;
		mArrowToGoal[int(mArrowPos::START)].color = mArrowToGoal[int(mArrowPos::CENTER)].color = mArrowToGoal[int(mArrowPos::END)].color = lineColor;
	}

	void buildArrowLine(sf::Vector2f& goalPosition, sf::Vector2f& objectPosition) {
		mLineToGoal[int(mLinePos::END)].position = goalPosition;

		mArrowToGoal[int(mArrowPos::CENTER)].position = goalPosition;
		mArrowToGoal[int(mArrowPos::START)].position = { goalPosition.x - 15.f, goalPosition.y - 15.f };
		mArrowToGoal[int(mArrowPos::END)].position = { goalPosition.x - 15.f, goalPosition.y + 15.f };


		float rotation = (std::atan2f(
			goalPosition.y - (objectPosition.y)
			, goalPosition.x - (objectPosition.x)
		));

		for (uint8_t i = 0; i < 3; i += 2) {

			// Вычисление смещенных координат
			float translatedX = mArrowToGoal[i].position.x - mArrowToGoal[int(mArrowPos::CENTER)].position.x;
			float translatedY = mArrowToGoal[i].position.y - mArrowToGoal[int(mArrowPos::CENTER)].position.y;

			// Поворот в начале координат
			float rotatedX = translatedX * std::cos(rotation) - translatedY * std::sin(rotation);
			float rotatedY = translatedX * std::sin(rotation) + translatedY * std::cos(rotation);

			// Сдвиг обратно
			mArrowToGoal[i].position = sf::Vector2f(
				rotatedX + mArrowToGoal[int(mArrowPos::CENTER)].position.x,
				rotatedY + mArrowToGoal[int(mArrowPos::CENTER)].position.y
			);
		}


		mLineToGoal[int(mLinePos::START)].position = objectPosition;
	}

	void updateStartOfLine(sf::Vector2f& objectPosition) {
		mLineToGoal[int(mLinePos::START)].position = objectPosition;
	}

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		// apply the entity's transform -- combine it with the one that was passed by the caller
		states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

		// you may also override states.shader or states.blendMode if you want
		// draw the vertex array

		target.draw(mLineToGoal);
		target.draw(mArrowToGoal);
	}

	sf::VertexArray mLineToGoal;							// линия от игрока к цели
	sf::VertexArray mArrowToGoal;							// стрека к цели

	enum class		mLinePos : uint8_t { START = 0, END };			 //точки в линии до цели
	enum class		mArrowPos : uint8_t { START = 0, CENTER, END }; //точки в стрелке до цели
};

class MainCharacter : public sf::Drawable, public sf::Transformable
{
public:

	MainCharacter() : 
		mCharacterCircle(mCircleRadius),
		mMovement(sf::Vector2f({ 120.f, 230.f })),
		mLineBuilder(mMovement.getTargetObjPosition())
	{
		mCharacterCircle.setOrigin(sf::Vector2f{ mCircleRadius, mCircleRadius });
		mCharacterCircle.setFillColor(sf::Color::Black);
		mCharacterCircle.setPosition(mCharacterPosition);
		mPlayerCamera.setCameraCenter(mCharacterPosition);
	}

	bool getHasGoal() const { return mHasGoal; }
	void setHasGoal(bool value) {  mHasGoal = value; }

	bool getIsMoving() const { return mIs_Moving; }
	bool getIsDoSomthing() const { return mIs_doSomthing; }
	void setIsMoving(bool value) { mIs_Moving = value; mIs_Moving? mIs_doSomthing = true : mIs_doSomthing = false; }
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

	void move(float& dt) {
		if(mIs_doSomthing)
		{
			mIs_doSomthing = mMovement.move(dt, mCharacterCircle, mPositionGoal);
			mLineBuilder.updateStartOfLine(mMovement.getTargetObjPosition());
		}
	}


	void setPositionGoal(const sf::Event& event) {
		
		sf::Vector2i pixelPos = sf::Mouse::getPosition(Window::instance());//забираем коорд курсора
		mPositionGoal = Window::instance().mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)

		mHasGoal = true;

		mLineBuilder.buildArrowLine(mPositionGoal, mMovement.getTargetObjPosition());
	}

	void zoomIn() {
		mPlayerCamera.zoomIn();
	}

	void zoomOut() {
		mPlayerCamera.zoomOut();
	}

	sf::View getView() const {
		return this->mPlayerCamera.getCamera();
	}

	void updateNeeds() {
		this->mPersonBody.updateNeeds();
	}

	std::string showNeeds() {
		return this->mPersonBody.toString();
	}

	Body& getBody() { return mPersonBody; }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override 
	{
		// apply the entity's transform -- combine it with the one that was passed by the caller
		states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

		// apply the texture


		// you may also override states.shader or states.blendMode if you want
		// draw the vertex array
		target.setView(mPlayerCamera.getCamera());
		if (mHasGoal)
		{
			target.draw(mLineBuilder);
		}
		target.draw(mCharacterCircle, states);
	}

private:
	const float		mCircleRadius				= 25.f;		//размер круга, обозначающий игрока

	sf::CircleShape	mCharacterCircle;						// фигура круга для обозначения игрока
	Camera			mPlayerCamera;							//камера игрока
	sf::Vector2f	mCharacterPosition;						// позиция игрока 
	
	sf::Vector2f	mPositionGoal;							// вектор позиции цели
	
	MovementSystem mMovement;
	ArrowLine mLineBuilder;
	Body mPersonBody;										//тело персонажа


	bool			mHasGoal					= false;	//поставлена ли точка, куда надо идти
	bool			mIs_Moving					= false;	//идет ли игрок
	bool			mIs_doSomthing				= false;

};