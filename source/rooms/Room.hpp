#pragma once
#include "../main/Game.hpp"
#include "../resource/TextureRects.hpp"

class Room {
protected:
	int state{};

public:
	virtual ~Room(){}

	virtual void initialize() {}
	virtual void update() {}
	virtual void draw() {}

	virtual std::string getName() { return ""; }
};