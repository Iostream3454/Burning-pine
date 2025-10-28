#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include "window.h"

class MainCharacter : public sf::Drawable, public sf::Transformable
{
public:

	MainCharacter() :  mCurrentCharacterSpeed(mBaseCharacterSpeed * 1.3f), mTexture("gfx/character.png", false, sf::IntRect({ 10, 10 }, { 32, 32 })) {
		mCharacterCircle.setRadius(mCircleRadius);
		mCharacterPosition = {120.f, 230.f};
		mCharacterCircle.setFillColor(sf::Color::Black);
		mCharacterCircle.setPosition(mCharacterPosition);
	}

	bool getHasGoal() { return mHasGoal; }

	void move() {
		if (this->mHasGoal) {
			float distance = sqrt(
				(mPositionGoal.x - mCharacterCircle.getPosition().x) * (mPositionGoal.x - mCharacterCircle.getPosition().x) + 
				(mPositionGoal.y - mCharacterCircle.getPosition().y) * (mPositionGoal.y - mCharacterCircle.getPosition().y));//считаем дистанцию (длину от точки А до точки Б). формула длины вектора

			if (distance > 2.f) {//этим условием убираем дергание во время конечной позиции спрайта

				mCharacterPosition.x += 0.1f  * (mPositionGoal.x - mCharacterCircle.getPosition().x) / distance;//идем по иксу с помощью вектора нормали
				mCharacterPosition.y += 0.1f  * (mPositionGoal.y - mCharacterCircle.getPosition().y) / distance;//идем по игреку так же
				mCharacterCircle.setPosition(mCharacterPosition);
			}
			else { this->mHasGoal = this->mIs_Moving = false; std::cout << "priehali\n"; }//говорим что уже никуда не идем и выводим веселое сообщение в консоль
		}
	}
	//void updateNeeds();

	void setPositionGoal(const sf::Event& event) {
		if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>())
		{
			if (mouseButtonPressed->button == sf::Mouse::Button::Left)
			{
				sf::Vector2i pixelPos = sf::Mouse::getPosition(Window::instance());//забираем коорд курсора
				mPositionGoal = Window::instance().mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)
				mHasGoal = true;
				mPositionGoal.x -= mCircleRadius;
				mPositionGoal.y -= mCircleRadius;
				/*mCharacterPosition = mPositionGoal; mCharacterCircle.setPosition(
					{ mPositionGoal.x - mCharacterCircle.getRadius(), mPositionGoal.y - mCharacterCircle.getRadius() }
				);*/
				std::cout << "mouse x: " << mPositionGoal.x << std::endl;
				std::cout << "mouse y: " << mPositionGoal.y << std::endl;
			}else{ mHasGoal = false; }
		}
	}


	void draw(sf::RenderTarget& target, sf::RenderStates states) const override 
	{
		// apply the entity's transform -- combine it with the one that was passed by the caller
		states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

		// apply the texture
		states.texture = &mTexture;

		// you may also override states.shader or states.blendMode if you want

		// draw the vertex array
		target.draw(mCharacterCircle, states);
	}

private:

	sf::Vector2f	mCharacterPosition;
	sf::CircleShape	mCharacterCircle;
	sf::Texture		mTexture;

	sf::VertexArray mLineToGoal;
	sf::Vector2f	mPositionGoal;

	const float		mBaseCharacterSpeed			= 300.0f;
	float			mCurrentCharacterSpeed;
	const float		mCircleRadius				= 25.f;

	bool			mHasGoal					= false;
	bool			mIs_Moving					= false;
};