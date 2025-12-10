#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
//класс графического(фигура) представления объекта(немного неясна логика)
class ShapeType : public sf::Drawable, public sf::Transformable {
public:
	void setNewPosition(sf::Vector2f position) {
		mBaseShape->setPosition(position);
	}
protected:
	ShapeType(std::unique_ptr<sf::Shape> form) : mBaseShape(std::move(form)) {}


	std::unique_ptr<sf::Shape> mBaseShape;
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		// apply the entity's transform -- combine it with the one that was passed by the caller
		states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

		// you may also override states.shader or states.blendMode if you want
		// draw the vertex array
		target.draw(*mBaseShape.get(), states);
	}
};

class CircleType final : public ShapeType {
public:
	CircleType(std::unique_ptr<sf::CircleShape> form, sf::Vector2f startPosition = { 0.f, 0.f }, float radius = 25.f, sf::Color shapeColor = sf::Color::Black) :
		ShapeType(std::move(form)),
		mCircleRadius(radius)
	{
		sf::CircleShape* temp = dynamic_cast<sf::CircleShape*>(mBaseShape.get());
		temp->setRadius(radius);
		temp->setOrigin({ mCircleRadius, mCircleRadius });
		temp->setFillColor(shapeColor);
		temp->setPosition(startPosition);
		temp = nullptr;
	}
private:
	float		mCircleRadius;					//размер круга, обозначающий игрока
};