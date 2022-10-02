#include "LlamaBay_Outside_0.hpp"
#include "LlamaBay_House_Aon_Downstairs.hpp"
#include <fstream>

void LlamaBay_Outside_0::initialize() {
	Game::player->sprite.setTextureRect(TextureRects::character_flynn_overworld_down);
	Game::player->setPosition(135, 165);

	music->openFromFile(resource_paths::music::llama_bay);
	music->play();

	loadScene(nlohmann::json::parse(std::ifstream{resource_paths::json::llamabay_outside_0}));
}
void LlamaBay_Outside_0::update() {
	switch (state) {
	case 0: {
		fadeIn();
		if (getBlackOpacity() == 0) state++;
		break;
	}
	case 1: {
		Game::player->updateMovement(this);
		if (Game::player->getWillOpenDoor(sf::FloatRect(132, 137, 27, 18), Player::Up)) {
			state++;
		}
		break;
	}
	case 2: {
		fadeOut();
		if (getBlackOpacity() == 100) {
			Game::setRoom(new LlamaBay_House_Aon_Downstairs());
		}
		break;
	}
	}
}
void LlamaBay_Outside_0::draw() {
	drawScene();
	window->draw(blackRectangle);
}

std::string LlamaBay_Outside_0::getName() {
	return "LlamaBay_Outside_0";
}