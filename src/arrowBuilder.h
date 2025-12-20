#pragma once
#include <SFML/Graphics.hpp>

//класс отвечает за построение линии сос стрелкой на конце от центра объекта до цели
class ArrowLineSystem : public sf::Drawable, public sf::Transformable {
public:
	ArrowLineSystem(sf::Vector2f targetObjPosition = { 0.f, 0.f }, sf::Color lineColor = sf::Color::Blue);

	void buildArrowLine(sf::Vector2f& goalPosition, sf::Vector2f& objectPosition);

	void updateStartOfLine(sf::Vector2f& objectPosition);

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::VertexArray mLineToGoal;							// линия от игрока к цели
	sf::VertexArray mArrowToGoal;							// стрека к цели

	enum class		mLinePos : uint8_t { START = 0, END };			 //точки в линии до цели
	enum class		mArrowPos : uint8_t { START = 0, CENTER, END }; //точки в стрелке до цели
};