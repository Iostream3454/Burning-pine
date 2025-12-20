#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


class Map : public sf::Drawable, public sf::Transformable {
public:

	Map();

	sf::FloatRect getFloatRectOfBounds();

	sf::Vector2f getSizeOfMap();

	void load();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	const sf::Vector2u	mMapSize	= { 50, 50 };			//размер карты(в €чейках)
	const sf::Vector2u	mTileSize	= { 64 * 3 , 64 * 3 };	//размер клетки
	sf::Vector2f		mMapSizePixel;						//размер карты в пиксел€х
	sf::VertexArray		mVertices;							//вертексы(треугольники) клеток
};

class World : public sf::Drawable, public sf::Transformable {
public:
	World();

	bool checkPointOnOutOfBounds(sf::Vector2f& position);

	sf::Vector2f getMapSize();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	Map mWorldMap;
};

