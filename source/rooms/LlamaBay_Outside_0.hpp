#pragma once
#include "OverworldRoom.hpp"

class LlamaBay_Outside_0 : public OverworldRoom {
public:
	void initialize();
	void update();
	void draw();
	
	std::string getName();
};