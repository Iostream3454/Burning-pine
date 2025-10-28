#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include "window.h"

class MainCharacter : public sf::Drawable, public sf::Transformable
{
public:

	MainCharacter() : mCurrentCharacterSpeed(mBaseCharacterSpeed * 1.3f), mTexture("../gfx/character.png"), mCharacterCircle(50) {
		mCharacterCircle.setTexture(&mTexture); mCharacterCircle.setTextureRect(sf::IntRect({ 50, 50 }, { 100, 100 }));
	}

	void move() {

	}
	//void updateNeeds();

	void setPositionGoal(sf::Event& event) {
		if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>())
		{
			if (mouseButtonPressed->button == sf::Mouse::Button::Left)
			{
				sf::Vector2i pixelPos = sf::Mouse::getPosition(Window::instance());//забираем коорд курсора
				mPositionGoal = Window::instance().mapPixelToCoords(pixelPos);//переводим их в игровые (уходим от коорд окна)
				mPositionGoal = { mouseButtonPressed->position.x ,mouseButtonPressed->position.y };
				mHasGoal = true;
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

	bool			mHasGoal					= false;
	bool			mIs_Moving					= false;
};