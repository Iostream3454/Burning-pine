#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include "window.h"
#include "camera.h"
#include "body.h"
#include "movementSystem.h"
#include "arrowBuilder.h"

//класс графического(фигура) представления объекта(немного неясна логика)
//class ShapeType  {
//protected:
//	ShapeType(std::unique_ptr<sf::Shape> form) : mBaseShape(std::move(form)) {}
//
//	std::unique_ptr<sf::Shape> mBaseShape;
//};
//
//class CircleType final : protected ShapeType {
//public:
//	CircleType(std::unique_ptr<sf::CircleShape> form, sf::Vector2f startPosition = {0.f, 0.f}, float radius = 25.f,  sf::Color shapeColor = sf::Color::Black ) :
//		ShapeType(std::move(form)),
//		mCircleRadius(radius)
//		{ 
//
//		}
//private:
//	float		mCircleRadius;					//размер круга, обозначающий игрока
//};


class MainCharacter final : public sf::Drawable, public sf::Transformable
{
public:

	MainCharacter() : 
		mCharacterCircle(mCircleRadius),
		mMovement(sf::Vector2f({ 120.f, 230.f })),
		mLineBuilder(mMovement.getTargetObjPosition()),
		mPlayerCamera(mMovement.getTargetObjPosition(), sf::Vector2f(Window::instance().getSize()))
		//mCirclePresent(std::move(std::make_unique<sf::CircleShape>(new sf::CircleShape())), mMovement.getTargetObjPosition())
	{
		mCharacterCircle.setOrigin(sf::Vector2f{ mCircleRadius, mCircleRadius });
		mCharacterCircle.setFillColor(sf::Color::Black);
		mCharacterCircle.setPosition(mMovement.getTargetObjPosition());
	}

	
	bool getIsDoSomthing() const { return mIs_doSomthing; }
	void setIsMoving() {  (mIs_doSomthing = !mIs_doSomthing) ? mMovement.startMove() : mMovement.stopMove(); }

	bool isMoving() { return mMovement.isMoving(); }
	bool hasGoal() { return mMovement.hasGoal(); }
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
		if(mMovement.isMoving())
		{
			mIs_doSomthing = mMovement.move(dt, mCharacterCircle);
			mPlayerCamera.cameraMove(mMovement.getTargetObjPosition());
			mLineBuilder.updateStartOfLine(mMovement.getTargetObjPosition());
		}
	}

	void setPositionGoal(const sf::Event& event) {
		sf::Vector2i pixelPos = sf::Mouse::getPosition(Window::instance());//забираем коорд курсора
		sf::Vector2f GoalPositon = Window::instance().mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)
		mMovement.setGoalTargetPosition(GoalPositon);
		mLineBuilder.buildArrowLine(GoalPositon, mMovement.getTargetObjPosition());
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
		mPersonBody.updateNeeds();
	}

	Body& getBody() { return mPersonBody; }

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		// apply the entity's transform -- combine it with the one that was passed by the caller
		states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

		// you may also override states.shader or states.blendMode if you want
		// draw the vertex array
		target.setView(mPlayerCamera.getCamera());

		if (mMovement.hasGoal()) target.draw(mLineBuilder);

		target.draw(mCharacterCircle, states);
	}

	const float		mCircleRadius				= 25.f;		//размер круга, обозначающий игрока

	sf::CircleShape	mCharacterCircle;						// фигура круга для обозначения игрока
	//CircleType		mCirclePresent;
	MovementSystem	mMovement;								//модуль для передвижения объекта
	ArrowLineSystem mLineBuilder;							//строитель линий со стрелкой
	Camera			mPlayerCamera;							//камера игрока
	Body			mPersonBody;							//тело персонажа

	bool			mIs_doSomthing				= false;
};