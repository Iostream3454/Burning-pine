#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


class Map : public sf::Drawable, public sf::Transformable {
public:

	Map() {
		mVertices.setPrimitiveType(sf::PrimitiveType::Triangles);
		mVertices.resize(static_cast<size_t>(mTileSize.x) * mTileSize.y * 6);
	}

	sf::FloatRect getFloatRectOfBounds() {
		return mVertices.getBounds();
		
	}

	sf::Vector2f getSizeOfMap() { return mMapSizePixel; }

	void load() {
		sf::Color rainbowColor = {150, 0 , 0};
		for (unsigned i = 0; i < mMapSize.x; i++)
		{
			for (unsigned j = 0; j < mMapSize.y; j++) {
				sf::Vertex* triangles = &mVertices[(i + static_cast<size_t>(j) * mTileSize.x) * 6];

				triangles[0].position = sf::Vector2f(i * mTileSize.x, j * mTileSize.y);
				triangles[1].position = sf::Vector2f((i + 1) * mTileSize.x, j * mTileSize.y);
				triangles[2].position = sf::Vector2f(i * mTileSize.x, (j + 1) * mTileSize.y);
				triangles[3].position = sf::Vector2f(i * mTileSize.x, (j + 1) * mTileSize.y);
				triangles[4].position = sf::Vector2f((i + 1) * mTileSize.x, j * mTileSize.y);
				triangles[5].position = sf::Vector2f((i + 1) * mTileSize.x, (j + 1) * mTileSize.y);


				triangles[0].texCoords = sf::Vector2f(i * mTileSize.x, j * mTileSize.y);
				triangles[1].texCoords = sf::Vector2f((i + 1) * mTileSize.x, j * mTileSize.y);
				triangles[2].texCoords = sf::Vector2f(i * mTileSize.x, (j + 1) * mTileSize.y);
				triangles[3].texCoords = sf::Vector2f(i * mTileSize.x, (j + 1) * mTileSize.y);
				triangles[4].texCoords = sf::Vector2f((i + 1) * mTileSize.x, j * mTileSize.y);
				triangles[5].texCoords = sf::Vector2f((i + 1) * mTileSize.x, (j + 1) * mTileSize.y);

				for (unsigned x = 0; x < 6; x++)
				{
					triangles[x].color = rainbowColor;
				}

				if (rainbowColor == sf::Color({ 150, 255, 255 })) {
					rainbowColor = sf::Color{ 150, 0 , 0 };
				}
				rainbowColor += {0, 5, 5};
			}
		}
		mMapSizePixel = mVertices.getBounds().size;
	}

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		states.transform *= getTransform();

		//states.texture;

		target.draw(mVertices);
	}

	const sf::Vector2u mMapSize = { 50, 50 };
	const sf::Vector2u mTileSize = { 64 * 3 , 64 * 3 };
	sf::Vector2f mMapSizePixel;
	sf::VertexArray mVertices;
};

class World : public sf::Drawable, public sf::Transformable {
public:
	World(): mWorldMap() {
		mWorldMap.load();
	}

	bool checkPointOnOutOfBounds(sf::Vector2f& position) {
		return mWorldMap.getFloatRectOfBounds().contains(position);
	}

	sf::Vector2f getMapSize() { return mWorldMap.getSizeOfMap(); }

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		states.transform *= getTransform();

		//states.texture;

		target.draw(mWorldMap);
	}
	Map mWorldMap;
};

