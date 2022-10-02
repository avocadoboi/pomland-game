#pragma once
#include "Room.hpp"

class StartMenu_Controls : public Room {
private:
	std::vector<std::unique_ptr<GameButton>> buttons;
	std::vector<sf::Text> text_controls;
	sf::Text text_controlsTitle;

public:
	void initialize();
	void update();
	void draw();

	std::string getName();
};