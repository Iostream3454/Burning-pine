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

	const sf::Vector2u mMapSize = { 50, 50 };
	const sf::Vector2u mTileSize = { 64 * 3 , 64 * 3 };
	sf::Vector2f mMapSizePixel;
	sf::VertexArray mVertices;
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

