#include "world.h"

Map::Map() {
	mVertices.setPrimitiveType(sf::PrimitiveType::Triangles);
	mVertices.resize(static_cast<size_t>(mTileSize.x) * mTileSize.y * 6);
}

sf::FloatRect Map::getFloatRectOfBounds() {
	return mVertices.getBounds();

}

sf::Vector2f Map::getSizeOfMap() { return mMapSizePixel; }

void Map::load() {
	sf::Texture pp("gfx/testMap.bmp");
	sf::Image im = pp.copyToImage();
	const float floatTileSizeX = static_cast<float>(mTileSize.x);
	const float floatTileSizeY = static_cast<float>(mTileSize.y);
	for (unsigned i = 0; i < mMapSize.x; i++)
	{
		for (unsigned j = 0; j < mMapSize.y; j++) {
			const sf::Color tileNumber = im.getPixel(sf::Vector2u{ i, j });

			sf::Vertex* triangles = &mVertices[(i + static_cast<size_t>(j) * mTileSize.x) * 6];

			triangles[0].position = sf::Vector2f(i * floatTileSizeX, j * floatTileSizeY);
			triangles[1].position = sf::Vector2f((i + 1) * floatTileSizeX, j * floatTileSizeY);
			triangles[2].position = sf::Vector2f(i * floatTileSizeX, (j + 1) * floatTileSizeY);
			triangles[3].position = sf::Vector2f(i * floatTileSizeX, (j + 1) * floatTileSizeY);
			triangles[4].position = sf::Vector2f((i + 1) * floatTileSizeX, j * floatTileSizeY);
			triangles[5].position = sf::Vector2f((i + 1) * floatTileSizeX, (j + 1) * floatTileSizeY);


			triangles[0].texCoords = sf::Vector2f(i * floatTileSizeX, j * floatTileSizeY);
			triangles[1].texCoords = sf::Vector2f((i + 1) * floatTileSizeX, j * floatTileSizeY);
			triangles[2].texCoords = sf::Vector2f(i * floatTileSizeX, (j + 1) * floatTileSizeY);
			triangles[3].texCoords = sf::Vector2f(i * floatTileSizeX, (j + 1) * floatTileSizeY);
			triangles[4].texCoords = sf::Vector2f((i + 1) * floatTileSizeX, j * floatTileSizeY);
			triangles[5].texCoords = sf::Vector2f((i + 1) * floatTileSizeX, (j + 1) * floatTileSizeY);

			for (unsigned x = 0; x < 6; x++)
			{
				triangles[x].color = tileNumber;
			}
		}
	}
	mMapSizePixel = mVertices.getBounds().size;
}

	void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= getTransform();

		//states.texture;

		target.draw(mVertices);
	}


	World::World() : mWorldMap() {
		mWorldMap.load();
	}

	bool World::checkPointOnOutOfBounds(sf::Vector2f& position) {
		return mWorldMap.getFloatRectOfBounds().contains(position);
	}

	sf::Vector2f World::getMapSize() { return mWorldMap.getSizeOfMap(); }

	void World::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= getTransform();

		//states.texture;

		target.draw(mWorldMap);
	}