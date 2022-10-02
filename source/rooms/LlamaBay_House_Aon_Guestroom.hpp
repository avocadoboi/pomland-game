#pragma once
#include "OverworldRoom.hpp"

//-------------------------------------------------------------

class LlamaBay_House_Aon_Guestroom : public OverworldRoom {
private:
	sf::Sprite sprite_bedSheet;
	sf::Sprite sprite_leftButton;
	sf::Text text;

	//-------------------------------------------------------------

	sf::FloatRect
		collisionRect_desk,
		collisionRect_bed;

public:
	void initialize();
	void update();
	void draw();

	std::string getName();
};