#pragma once
#include "Room.hpp"
#include "../UI/GameButton.hpp"

class StartMenu : public Room {
private:
	std::vector<std::unique_ptr<GameButton>> buttons;

	sf::Sprite sprite_title;

	sf::Text text_demo;
	sf::Text text_dog;

	int state_dogText;

public:
	void initialize();
	void update();
	void draw();

	std::string getName();
};