#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include "window.h"
#include "camera.h"
#include "body.h"

class MainCharacter : public sf::Drawable, public sf::Transformable
{
public:

	MainCharacter() : 
		mLineToGoal(sf::PrimitiveType::Lines, 2),
		mArrowToGoal(sf::PrimitiveType::LineStrip, 3),
		mCurrentCharacterSpeed(mBaseCharacterSpeed * 1.3f),
		mCharacterPosition({ 120.f, 230.f }),
		mTexture("gfx/character.png", false, sf::IntRect({10, 10}, {32, 32})) 

	{

		mCharacterCircle.setRadius(mCircleRadius);
		mCharacterCircle.setFillColor(sf::Color::Black);
		mCharacterCircle.setPosition(mCharacterPosition);
		mCharacterCircle.setOrigin(sf::Vector2f{ mCircleRadius, mCircleRadius });
		mPlayerCamera.setCameraCenter(mCharacterPosition);

		mLineToGoal[int(mLinePos::START)].color = mLineToGoal[int(mLinePos::END)].color = sf::Color::Blue;
		mArrowToGoal[int(mArrowPos::START)].color = mArrowToGoal[int(mArrowPos::CENTER)].color =  mArrowToGoal[int(mArrowPos::END)].color = sf::Color::Blue;	

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
		if (this->mIs_Moving) {
			float distance = sqrt(
				(mPositionGoal.x - mCharacterPosition.x) * (mPositionGoal.x - mCharacterPosition.x) + 
				(mPositionGoal.y - mCharacterPosition.y) * (mPositionGoal.y - mCharacterPosition.y));//считаем дистанцию (длину от точки А до точки Б). формула длины вектора

			if (distance > 4.f) {//этим условием убираем дергание во время конечной позиции спрайта

				mCharacterPosition.x += dt * mBaseCharacterSpeed * (mPositionGoal.x - mCharacterPosition.x) / distance ;//идем по иксу с помощью вектора нормали
				mCharacterPosition.y += dt * mBaseCharacterSpeed * (mPositionGoal.y - mCharacterPosition.y) / distance ;//идем по игреку так же
				mCharacterCircle.setPosition(mCharacterPosition);
				mLineToGoal[int(mLinePos::START)].position = mCharacterPosition;
				mPlayerCamera.cameraMove(mCharacterPosition);
			}
			else { 
				this->mHasGoal = this->mIs_Moving = mIs_doSomthing = false;
				std::cout << "priehali\r"; 
			}//говорим что уже никуда не идем и выводим веселое сообщение в консоль
		}
	}


	void setPositionGoal(const sf::Event& event) {
		
		sf::Vector2i pixelPos = sf::Mouse::getPosition(Window::instance());//забираем коорд курсора
		mPositionGoal = Window::instance().mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)

		mHasGoal = true;

		mLineToGoal[int(mLinePos::END)].position = mPositionGoal; 

		mArrowToGoal[int(mArrowPos::CENTER)].position = mPositionGoal;
		mArrowToGoal[int(mArrowPos::START)].position = { mPositionGoal.x - 15.f, mPositionGoal.y - 15.f };
		mArrowToGoal[int(mArrowPos::END)].position = { mPositionGoal.x - 15.f, mPositionGoal.y + 15.f };


		float rotation = (std::atan2f(
			mPositionGoal.y - (mCharacterPosition.y)
			, mPositionGoal.x - (mCharacterPosition.x)
		));
		//std::cout << rotation << std::endl;
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
				

		mLineToGoal[int(mLinePos::START)].position = mCharacterPosition;
		/*mCharacterPosition = mPositionGoal; mCharacterCircle.setPosition(
			{ mPositionGoal.x - mCharacterCircle.getRadius(), mPositionGoal.y - mCharacterCircle.getRadius() }
		);
		std::cout << "mouse x/y: " << mPositionGoal.x << "/" << mPositionGoal.y << std::endl;
		std::cout << "Line poses: {" << mLineToGoal[int(mLinePos::START)].position.x << " , " << mLineToGoal[int(mLinePos::START)].position.y << "} -> "
			<< "{" << mLineToGoal[int(mLinePos::END)].position.x << " , " << mLineToGoal[int(mLinePos::END)].position.y << "}"
			<<std::endl;*/
	
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
		states.texture = &mTexture;

		// you may also override states.shader or states.blendMode if you want
		// draw the vertex array
		target.setView(mPlayerCamera.getCamera());
		if (mHasGoal)
		{
			target.draw(mLineToGoal);
			target.draw(mArrowToGoal);
		}
		target.draw(mCharacterCircle, states);
	}

private:

	sf::CircleShape	mCharacterCircle;						// фигура круга для обозначения игрока
	Camera			mPlayerCamera;							//камера игрока
	sf::Vector2f	mCharacterPosition;						// позиция игрока 
	sf::Texture		mTexture;								// текстура игрока
	
	sf::VertexArray mLineToGoal;							// линия от игрока к цели
	sf::VertexArray mArrowToGoal;							// стрека к цели
	sf::Transform	mArrowToGoalTransform;					// трансформация для стрелки
	sf::Vector2f	mPositionGoal;							// вектор позиции цели
	
	Body mPersonBody;										//тело персонажа


	const float		mBaseCharacterSpeed			= 300.0f;	//базовая скорость
	float			mCurrentCharacterSpeed;					// скорость с модификаторами
	const float		mCircleRadius				= 25.f;		//размер круга, обозначающий игрока

	bool			mHasGoal					= false;	//поставлена ли точка, куда надо идти
	bool			mIs_Moving					= false;	//идет ли игрок
	bool			mIs_doSomthing				= false;

	enum class		mLinePos  :	uint8_t			{ START = 0, END };			 //точки в линии до цели
	enum class		mArrowPos : uint8_t			{ START = 0, CENTER,  END }; //точки в стрелке до цели
};