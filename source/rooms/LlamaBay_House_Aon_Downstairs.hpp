#pragma once
#include "OverworldRoom.hpp"

class LlamaBay_House_Aon_Downstairs : public OverworldRoom {
public:
	void initialize();
	void update();
	void draw();

	std::string getName();
};