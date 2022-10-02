#pragma once
#include "Room.hpp"

class StartMenu_InputName : public Room {
private:
	std::vector<std::unique_ptr<GameButton>> buttons;

	sf::Text text_typeName;
	sf::Text text_input;

	sf::SoundBuffer writingSoundBuffer;
	sf::Sound writingSound;

	std::string nameTemp = Game::player->getName();

public:
	void initialize();
	void update();
	void draw();

	std::string getName();
};