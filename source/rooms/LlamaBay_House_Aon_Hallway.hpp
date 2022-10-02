#pragma once
#include "OverworldRoom.hpp"

class LlamaBay_House_Aon_Hallway : public OverworldRoom {
private:
	sf::FloatRect doorRect_kitchen;

public:
	void initialize();
	void update();
	void draw();

	std::string getName();
};