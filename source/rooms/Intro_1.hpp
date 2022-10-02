#pragma once
#include "Room.hpp"

class Intro_1 : public Room {
private:
	sf::Sprite sprite_background;

public:
	void initialize();
	void update();
	void draw();

	std::string getName();
};