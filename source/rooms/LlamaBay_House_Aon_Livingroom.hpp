#pragma once
#include "OverworldRoom.hpp"

class LlamaBay_House_Aon_Livingroom : public OverworldRoom {
private:
	sf::Sprite sprite_wallOverlay;

	int currentGranpaClockFrame = 0;

public:
	void initialize();
	void update();
	void draw();
	~LlamaBay_House_Aon_Livingroom();

	std::string getName();
};