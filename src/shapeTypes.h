#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
//класс графического(фигура) представления объекта(немного неясна логика)
class ShapeType : public sf::Drawable, public sf::Transformable {
public:
	void setNewPosition(sf::Vector2f position);
protected:
	ShapeType(std::unique_ptr<sf::Shape> form);


	std::unique_ptr<sf::Shape> mBaseShape;
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

class CircleType final : public ShapeType {
public:
	CircleType(std::unique_ptr<sf::CircleShape> form, sf::Vector2f startPosition = { 0.f, 0.f }, float radius = 25.f, sf::Color shapeColor = sf::Color::Black);
private:
	float		mCircleRadius;					//размер круга, обозначающий игрока
};

class RectangleType final : public ShapeType {
public:
	RectangleType(std::unique_ptr<sf::RectangleShape> form, sf::Vector2f startPosition = { 0.f, 0.f }, sf::Vector2f size = { 25.f, 25.f }, sf::Color shapeColor = sf::Color::Black);
private:
	sf::Vector2f	mRectangleSize;					//размер прямоугольника, обозначающий игрока
};