#pragma once
#include <SFML/Graphics.hpp>

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

			// ¬ычисление смещенных координат
			float translatedX = mArrowToGoal[i].position.x - mArrowToGoal[int(mArrowPos::CENTER)].position.x;
			float translatedY = mArrowToGoal[i].position.y - mArrowToGoal[int(mArrowPos::CENTER)].position.y;

			// ѕоворот в начале координат
			float rotatedX = translatedX * std::cos(rotation) - translatedY * std::sin(rotation);
			float rotatedY = translatedX * std::sin(rotation) + translatedY * std::cos(rotation);

			// —двиг обратно
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

	sf::VertexArray mLineToGoal;							// лини€ от игрока к цели
	sf::VertexArray mArrowToGoal;							// стрека к цели

	enum class		mLinePos : uint8_t { START = 0, END };			 //точки в линии до цели
	enum class		mArrowPos : uint8_t { START = 0, CENTER, END }; //точки в стрелке до цели
};