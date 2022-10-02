#pragma once
#include "Room.hpp"

class Tests : public Room {
private:
	sf::VertexArray shape_0;

public:
	void initialize();
	void update();
	void draw();
	void cleanUp();
};