#pragma once
#include "RoomObject.hpp"
#include "../character/Character.hpp"

class RoomObjects{
private:
	std::vector<RoomObject*> roomObjects;

public:
	RoomObjects();
	~RoomObjects();

	void draw();
	void draw(std::vector<Character*> characters);
	void draw(std::vector<Character>& characters);

	void add(sf::IntRect textureRect, int bottomWidth);
	void add(RoomObject* roomObject);
	
	std::vector<sf::FloatRect> getCollisionRects();
	unsigned int getNumberOfRoomObjects();

	RoomObject& operator[](unsigned int index);
};