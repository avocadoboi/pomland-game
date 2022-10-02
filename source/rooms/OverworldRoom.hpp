#pragma once
#include "Room.hpp"
#include "../component/geometry.hpp"

//-------------------------------------------------------------

class OverworldRoom : public Room {
private:
	RoomObject* getRoomObject(const std::string& p_filename);

	//std::vector<ConvexShape> triangles;

protected:
	// The characters that are being drawn in this room.
	std::vector<Character*> characters = { Game::player.get() };

	void loadScene(const nlohmann::json& p_json);
	void drawScene();

public:
	virtual ~OverworldRoom() {}

	sf::Vector2u sceneSize;

	std::vector<std::vector<sf::Sprite>> tiles;

	std::vector<Triangle> collisionTriangles;
	std::vector<sf::FloatRect> collisionRectangles;

	RoomObjects roomObjects;
	std::vector<sf::Sprite> sprites;
};