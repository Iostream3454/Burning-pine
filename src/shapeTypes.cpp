#include "shapeTypes.h"


void ShapeType::setNewPosition(sf::Vector2f position) {
	mBaseShape->setPosition(position);
}

void ShapeType::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the entity's transform -- combine it with the one that was passed by the caller
	states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

	// you may also override states.shader or states.blendMode if you want
	// draw the vertex array
	target.draw(*mBaseShape.get(), states);
}

ShapeType::ShapeType(std::unique_ptr<sf::Shape> form) : mBaseShape(std::move(form)) {}

CircleType::CircleType(std::unique_ptr<sf::CircleShape> form, sf::Vector2f startPosition, float radius, sf::Color shapeColor) :
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

RectangleType::RectangleType(std::unique_ptr<sf::RectangleShape> form, sf::Vector2f startPosition, sf::Vector2f size, sf::Color shapeColor) :
	ShapeType(std::move(form)),
	mRectangleSize(size)
{
	sf::RectangleShape* temp = dynamic_cast<sf::RectangleShape*>(mBaseShape.get());
	temp->setSize(mRectangleSize);
	temp->setOrigin({ mRectangleSize.x / 2, mRectangleSize.y / 2 });
	temp->setFillColor(shapeColor);
	temp->setPosition(startPosition);
	temp = nullptr;
}