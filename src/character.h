#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <memory>
#include "window.h"
#include "camera.h"
#include "body.h"

//класс отвечает за перемещение объекта
class MovementSystem {
public:

	MovementSystem(sf::Vector2f&& objectStartPosition ) : mTargetObjPosition(objectStartPosition) {}

	bool move(float& dt, sf::Shape& moveAbleObject) {
		mTargetObjPosition = moveAbleObject.getPosition();

		float distance = sqrt(
			(mGoalTargetPosition.x - mTargetObjPosition.x) * (mGoalTargetPosition.x - mTargetObjPosition.x) +
			(mGoalTargetPosition.y - mTargetObjPosition.y) * (mGoalTargetPosition.y - mTargetObjPosition.y)
		);//считаем дистанцию (длину от точки А до точки Б). формула длины вектора

		if (distance > 4.f) {//этим условием убираем дергание во время конечной позиции спрайта
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
	sf::Vector2f	mTargetObjPosition		= { 0.f, 0.f };				// позиция объекта 
	sf::Vector2f	mGoalTargetPosition		= { 0.f, 0.f };				// позиция цели
	const float		mBaseCharacterSpeed		= 300.0f;					// базовая скорость
	float			mCurrentCharacterSpeed	= mBaseCharacterSpeed * 1;	// скорость с модификаторами

	bool			mHasGoal				= false;					// поставлена ли точка, куда надо идти
	bool			mIsMoving				= false;					// идет ли игрок
};

//класс отвечает за построение линии сос стрелкой на конце от центра объекта до цели
class ArrowLineSystem : public sf::Drawable, public sf::Transformable { 
public:
	ArrowLineSystem(sf::Vector2f targetObjPosition = { 0.f, 0.f }, sf::Color lineColor = sf::Color::Blue) :
		mLineToGoal(sf::PrimitiveType::Lines, 2),
		mArrowToGoal(sf::PrimitiveType::LineStrip, 3)
	{
 		mLineToGoal[int(mLinePos::START)].position = targetObjPosition;
		mLineToGoal[int(mLinePos::START)].color = mLineToGoal[int(mLinePos::END)].color = lineColor;
		mArrowToGoal[int(mArrowPos::START)].color = mArrowToGoal[int(mArrowPos::CENTER)].color = mArrowToGoal[int(mArrowPos::END)].color = lineColor;
	}

	void buildArrowLine(sf::Vector2f& goalPosition, sf::Vector2f& objectPosition) {
		mLineToGoal[int(mLinePos::START)].position = objectPosition;

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

		mLineToGoal[int(mLinePos::END)].position = goalPosition;
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

//класс графического(фигура) представления объекта(немного неясна логика)
//class ShapeType  {
//public:
//	ShapeType(std::unique_ptr<sf::Shape> form) : mBaseShape(std::move(form)) {}
//protected:
//	std::unique_ptr<sf::Shape> mBaseShape;
//};
//
//class CircleType : private ShapeType {
//public:
//	CircleType(std::unique_ptr<sf::CircleShape> form, sf::Vector2f startPosition = {0.f, 0.f}, float radius = 25.f,  sf::Color shapeColor = sf::Color::Black ) :
//		ShapeType(std::move(form)),
//		mCircleRadius(radius)
//	{ 
//		/*dynamic_cast<sf::CircleShape*>(mBaseShape.get())->setRadius(mCircleRadius);
//		dynamic_cast<sf::CircleShape*>(mBaseShape.get())->setOrigin(sf::Vector2f(mCircleRadius, mCircleRadius));
//		dynamic_cast<sf::CircleShape*>(mBaseShape.get())->setPosition(startPosition);
//		dynamic_cast<sf::CircleShape*>(mBaseShape.get())->setFillColor(shapeColor);*/
//	}
//private:
//	float		mCircleRadius;					//размер круга, обозначающий игрока
//};
//
//class ObjectPresentationSystem {
//public:
//
//private:
//
//};

class MainCharacter : public sf::Drawable, public sf::Transformable
{
public:

	MainCharacter() : 
		mCharacterCircle(mCircleRadius),
		mMovement(sf::Vector2f({ 120.f, 230.f })),
		mLineBuilder(mMovement.getTargetObjPosition()),
		mPlayerCamera(mMovement.getTargetObjPosition(), sf::Vector2f(Window::instance().getSize()))
		//mCirclePresent(std::make_unique<sf::CircleShape>(new sf::CircleShape()), mMovement.getTargetObjPosition())
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
		this->mPersonBody.updateNeeds();
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

	sf::CircleShape	mCharacterCircle;						
	//CircleType	mCirclePresent;						// фигура круга для обозначения игрока
	
	MovementSystem	mMovement;								//модуль для передвижения объекта
	ArrowLineSystem mLineBuilder;							//строитель линий со стрелкой
	Camera			mPlayerCamera;							//камера игрока
	Body			mPersonBody;							//тело персонажа

	bool			mIs_doSomthing				= false;
};