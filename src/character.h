#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include "window.h"

class MainCharacter : public sf::Drawable, public sf::Transformable
{
public:

	MainCharacter() : 
		mLineToGoal(sf::PrimitiveType::Lines, 2),
		mArrowToGoal(sf::PrimitiveType::LineStrip, 3),
		mCurrentCharacterSpeed(mBaseCharacterSpeed * 1.3f),
		mTexture("gfx/character.png", false, sf::IntRect({10, 10}, {32, 32}))
	{
		mCharacterCircle.setRadius(mCircleRadius);
		mCharacterPosition = {120.f, 230.f};
		mCharacterCircle.setFillColor(sf::Color::Black);
		mCharacterCircle.setPosition(mCharacterPosition);
		mLineToGoal[int(mLinePos::START)].color = mLineToGoal[int(mLinePos::END)].color = sf::Color::Blue;
		mArrowToGoal[int(mArrowPos::START)].color = mArrowToGoal[int(mArrowPos::CENTER)].color =  mArrowToGoal[int(mArrowPos::END)].color = sf::Color::Blue;		
	}

	bool getHasGoal() { return mHasGoal; }

	void move() {
		if (this->mHasGoal) {
			float distance = sqrt(
				(mPositionGoal.x - mCharacterCircle.getPosition().x) * (mPositionGoal.x - mCharacterCircle.getPosition().x) + 
				(mPositionGoal.y - mCharacterCircle.getPosition().y) * (mPositionGoal.y - mCharacterCircle.getPosition().y));//������� ��������� (����� �� ����� � �� ����� �). ������� ����� �������

			if (distance > 2.f) {//���� �������� ������� �������� �� ����� �������� ������� �������

				mCharacterPosition.x += 0.1f  * (mPositionGoal.x - mCharacterCircle.getPosition().x) / distance;//���� �� ���� � ������� ������� �������
				mCharacterPosition.y += 0.1f  * (mPositionGoal.y - mCharacterCircle.getPosition().y) / distance;//���� �� ������ ��� ��
				mCharacterCircle.setPosition(mCharacterPosition);
				mLineToGoal[int(mLinePos::START)].position = { 
					mCharacterCircle.getPosition().x + mCircleRadius , 
					mCharacterCircle.getPosition().y + mCircleRadius 
				};
			}
			else { 
				this->mHasGoal = this->mIs_Moving = false; 
				std::cout << "priehali\n"; 
			}//������� ��� ��� ������ �� ���� � ������� ������� ��������� � �������
		}
	}


	void setPositionGoal(const sf::Event& event) {
		if (const auto* mouseButtonPressed = event.getIf<sf::Event::MouseButtonPressed>())
		{
			if (mouseButtonPressed->button == sf::Mouse::Button::Left)
			{
				sf::Vector2i pixelPos = sf::Mouse::getPosition(Window::instance());//�������� ����� �������
				mPositionGoal = Window::instance().mapPixelToCoords(pixelPos);//��������� �� � ������� (������ �� ����� ����)

				mHasGoal = true;

				mLineToGoal[int(mLinePos::END)].position = mPositionGoal; 

				mArrowToGoal[int(mArrowPos::CENTER)].position = mPositionGoal;
				mArrowToGoal[int(mArrowPos::START)].position = { mPositionGoal.x - 15.f, mPositionGoal.y + 15.f };
				mArrowToGoal[int(mArrowPos::END)].position = { mPositionGoal.x + 15.f, mPositionGoal.y + 15.f };

				mPositionGoal -= {mCircleRadius, mCircleRadius};

				float rotation = (std::atan2f(
					mPositionGoal.y - (mCharacterCircle.getPosition().y + mCircleRadius)
					, mPositionGoal.x - (mCharacterCircle.getPosition().x + mCircleRadius)
				));
				//std::cout << rotation << std::endl;
				for (uint8_t i = 0; i < 3; i += 2) {

					// ���������� ��������� ���������
					float translatedX = mArrowToGoal[i].position.x - mArrowToGoal[int(mArrowPos::CENTER)].position.x;
					float translatedY = mArrowToGoal[i].position.y - mArrowToGoal[int(mArrowPos::CENTER)].position.y;

					// ������� � ������ ���������
					float rotatedX = translatedX * std::cos(rotation - 3.14156f / 2.f) - translatedY * std::sin(rotation + 3.14156f/2.f);
					float rotatedY = translatedX * std::sin(rotation + 3.14156f / 2.f) + translatedY * std::cos(rotation - 3.14156f / 2.f);

					// ����� �������
					mArrowToGoal[i].position = sf::Vector2f(
						rotatedX + mArrowToGoal[int(mArrowPos::CENTER)].position.x,
						rotatedY + mArrowToGoal[int(mArrowPos::CENTER)].position.y
					);
				}

				//mArrowToGoalTransform.rotate(sf::degrees(rotation), mPositionGoal);
				

				mLineToGoal[int(mLinePos::START)].position = { mCharacterCircle.getPosition().x + mCircleRadius , mCharacterCircle.getPosition().y + mCircleRadius };
				/*mCharacterPosition = mPositionGoal; mCharacterCircle.setPosition(
					{ mPositionGoal.x - mCharacterCircle.getRadius(), mPositionGoal.y - mCharacterCircle.getRadius() }
				);
				std::cout << "mouse x/y: " << mPositionGoal.x << "/" << mPositionGoal.y << std::endl;
				std::cout << "Line poses: {" << mLineToGoal[int(mLinePos::START)].position.x << " , " << mLineToGoal[int(mLinePos::START)].position.y << "} -> "
					<< "{" << mLineToGoal[int(mLinePos::END)].position.x << " , " << mLineToGoal[int(mLinePos::END)].position.y << "}"
					<<std::endl;*/
			}
			else
			{ 
				mHasGoal = false; 
			}
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
		if (mHasGoal)
		{
			target.draw(mLineToGoal);
			target.draw(mArrowToGoal);
		}
		target.draw(mCharacterCircle, states);
	}

private:

	sf::Vector2f	mCharacterPosition;						// ������� ������ 
	sf::CircleShape	mCharacterCircle;						// ������ ����� ��� ����������� ������
	sf::Texture		mTexture;								// �������� ������

	sf::VertexArray mLineToGoal;							// ����� �� ������ � ����
	sf::VertexArray mArrowToGoal;							// ������ � ����
	sf::Transform	mArrowToGoalTransform;					// ������������� ��� �������
	sf::Vector2f	mPositionGoal;							// ������ ������� ����

	const float		mBaseCharacterSpeed			= 300.0f;	//������� ��������
	float			mCurrentCharacterSpeed;					// �������� � ��������������
	const float		mCircleRadius				= 25.f;		//������ �����, ������������ ������

	bool			mHasGoal					= false;	//���������� �� �����, ���� ���� ����
	bool			mIs_Moving					= false;	//���� �� �����
	enum class mLinePos : uint8_t {START = 0, END};
	enum class mArrowPos : uint8_t { START = 0, CENTER,  END };
};