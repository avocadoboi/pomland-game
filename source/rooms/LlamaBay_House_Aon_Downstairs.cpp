#include "LlamaBay_House_Aon_Downstairs.hpp"
#include "LlamaBay_House_Aon_Hallway.hpp"
#include "LlamaBay_Outside_0.hpp"
#include <fstream>

void LlamaBay_House_Aon_Downstairs::initialize() {
	loadScene(nlohmann::json::parse(std::ifstream{resource_paths::json::llamabay_house_aon_downstairs}));

	Game::player->sprite.setTextureRect(TextureRects::character_flynn_overworld_down);

	if (Game::string_lastRoom == "LlamaBay_House_Aon_Hallway") {
		Game::player->setPosition(148, 51);
	}
	else if (Game::string_lastRoom == "LlamaBay_Outside_0") {
		Game::player->setPosition(15, 125);
		music->openFromFile(resource_paths::music::aon);
		music->play();
	}

	Game::player->centerViewX(this);
}
void LlamaBay_House_Aon_Downstairs::update() {
	switch (state) {
	case 0: {
		fadeIn();
		if (getBlackOpacity() == 0) state++;
		break;
	}
	case 1: {
		Game::player->updateMovement(this);

		if (Game::player->sprite.getPosition().y < 30) {
			state = 2;
		}
		if (Game::player->getWillOpenDoor(sf::FloatRect(11, 100, 27, 11), Player::Up)) {
			state = 3;
		}
		break;
	}
	case 2: {
		fadeOut();
		if (getBlackOpacity() == 100) {
			Game::setRoom(new LlamaBay_House_Aon_Hallway);
		}
		break;
	}
	case 3: {
		fadeOut();
		if (getBlackOpacity() == 100) {
			Game::setRoom(new LlamaBay_Outside_0);
		}
	}
	}
}
void LlamaBay_House_Aon_Downstairs::draw() {
	drawScene();
	window->draw(blackRectangle);
}

std::string LlamaBay_House_Aon_Downstairs::getName() {
	return "LlamaBay_House_Aon_Downstairs";
}