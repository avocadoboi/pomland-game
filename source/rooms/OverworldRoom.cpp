#include "OverworldRoom.hpp"

//
// Private
//

RoomObject* OverworldRoom::getRoomObject(const std::string& p_filename) {
	RoomObject* result = nullptr;
	if (getIsEndOfStringEqualTo(p_filename, "object_house_aon_0.png")) {
		result = new RoomObject(TextureRects::object_house_aon_0, 0);
		result->setOrigin(0, 94);
	}
	else if (getIsEndOfStringEqualTo(p_filename, "object_house_aon_1.png")) {
		result = new RoomObject(TextureRects::object_house_aon_1, 0);
		result->setOrigin(0, 82);
	}
	return result;
}

//
// Protected
//

void OverworldRoom::loadScene(const nlohmann::json& p_json) {
	for (int a = 0; a < (int)p_json["layers"].size(); a++) {
		nlohmann::json layerData = p_json["layers"][a];

		if (layerData["type"] == "tilelayer") {
			// Add a new tile layer and fill it with tiles.
			tiles.push_back(std::vector<sf::Sprite>());
			nlohmann::json layerTileData = layerData["data"];
			sf::Vector2f layerSize(layerData["width"], layerData["height"]);
			sf::Vector2f layerPosition(layerData["x"], layerData["y"]);

			for (int b = 0; b < (int)layerTileData.size(); b++) {
				// Add a new tile.
				int indexInTileset = (int)layerTileData[b] - 1;
				tiles.back().push_back(sf::Sprite());
				sf::Sprite& sprite = tiles.back().back();

				if (indexInTileset < 0 || indexInTileset >= TILESET_SIZE.x*TILESET_SIZE.y) {
					sprite.setTextureRect(sf::IntRect(0, 0, TILE_WIDTH, TILE_WIDTH));
					sprite.setColor(sf::Color::Transparent);
					return;
				}
				else {
					sf::Vector2<int> positionInTileset(getPositionFromIndex((sf::Vector2u)TILESET_SIZE, indexInTileset));
					sprite.setTexture(*texture_tileset);
					sprite.setTextureRect(sf::IntRect(
						TILESET_MARGIN + (TILE_WIDTH + TILESET_SPACING)*positionInTileset.x,
						TILESET_MARGIN + (TILE_WIDTH + TILESET_SPACING)*positionInTileset.y,
						TILE_WIDTH, TILE_WIDTH
					));
				}

				sf::Vector2<int> tilePosition(getPositionFromIndex((sf::Vector2u)layerSize, b));
				sprite.setPosition(
					layerPosition.x + TILE_WIDTH*tilePosition.x,
					layerPosition.y + TILE_WIDTH*tilePosition.y
				);
			}
		}
		else if (layerData["type"] == "imagelayer") {
			// Add a new room object.
			RoomObject* newRoomObject = getRoomObject(layerData["image"]);
			if (newRoomObject != nullptr) {
				newRoomObject->setPosition(
					(layerData["offsetx"].is_number() ? std::round((float)layerData["offsetx"]) : 0.f) + std::round((float)layerData["x"]) + newRoomObject->getOrigin().x,
					(layerData["offsety"].is_number() ? std::round((float)layerData["offsety"]) : 0.f) + std::round((float)layerData["y"]) + newRoomObject->getOrigin().y
				);
				roomObjects.add(newRoomObject);
			}
			else {
				std::string name = layerData["image"];
				name.erase(name.size() - 4, 4);
				for (int a = (int)name.size() - 1; a >= 0; a--) {
					if (name[a] == '\\' || name[a] == '/') {
						name.erase(0, a+1);
					}
				}

				sf::IntRect rect = TextureRects::getTextureRectFromName(name);
				if (rect.width || rect.height) {
					sprites.push_back(sf::Sprite(*texture, rect));
					sprites.back().setPosition(
						(layerData["offsetx"].is_number() ? std::round((float)layerData["offsetx"]) : 0.f) + std::round((float)layerData["x"]),
						(layerData["offsety"].is_number() ? std::round((float)layerData["offsety"]) : 0.f) + std::round((float)layerData["y"])
					);
				}
			}
		}
		else if (layerData["type"] == "objectgroup") {
			for (int b = 0; b < (int)layerData["objects"].size(); b++) {
				nlohmann::json objectData = layerData["objects"][b];
				if ((int)layerData["objects"][b]["width"] == 0) {
					// Add a new collison polygon.
					std::vector<sf::Vector2f> points;
					for (int c = 0; c < (int)objectData["polygon"].size(); c++) {
						points.push_back(sf::Vector2f(
							std::round((float)objectData["polygon"][c]["x"]) + std::round((float)objectData["x"]),
							std::round((float)objectData["polygon"][c]["y"]) + std::round((float)objectData["y"])
						));
					}
					std::vector<Triangle> triangles = getTrianglesFromPolygon(points);
					collisionTriangles.insert(collisionTriangles.end(), triangles.begin(), triangles.end());
				}
				else {
					// Add a new collision rectangle.
					collisionRectangles.push_back(sf::FloatRect(
						std::round((float)objectData["x"]), std::round((float)objectData["y"]),
						std::round((float)objectData["width"]), std::round((float)objectData["height"])
					));
				}
			}
		}
	}
	sceneSize.x = (int)p_json["width"] * (int)p_json["tilewidth"];
	sceneSize.y = (int)p_json["height"] * (int)p_json["tileheight"];

	//for (int a = 0; a < collisionTriangles.size(); a++) {
	//	triangles.push_back(ConvexShape(3));
	//	triangles.back().setFillColor(sf::Color::Red);
	//	triangles.back().setOutlineColor(sf::Color::Black);
	//	triangles.back().setOutlineThickness(0.3);
	//	triangles.back().setPoint(0, collisionTriangles[a].points[0]);
	//	triangles.back().setPoint(1, collisionTriangles[a].points[1]);
	//	triangles.back().setPoint(2, collisionTriangles[a].points[2]);
	//}
}
void OverworldRoom::drawScene() {
	// Draw every tile of every layer.
	for (int a = 0; a < (int)tiles.size(); a++) {
		for (int b = 0; b < (int)tiles[a].size(); b++) {
			window->draw(tiles[a][b]);
		}
	}

	for (int a = 0; a < (int)sprites.size(); a++) {
		window->draw(sprites[a]);
	}

	// Draw the room objects, if there are any. Otherwise just draw the characters.
	if (roomObjects.getNumberOfRoomObjects() > 0) {
		if ((int)characters.size() > 0) {
			roomObjects.draw(characters);
		}
		else {
			roomObjects.draw();
		}
	}
	else {
		for (auto const character : characters) {
			window->draw(character->sprite);
		}
	}

	//for (int a = 0; a < triangles.size(); a++) {
	//	window->draw(triangles[a]);
	//}
}
