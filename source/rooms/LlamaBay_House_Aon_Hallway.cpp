#include "LlamaBay_House_Aon_Hallway.hpp"
#include "LlamaBay_House_Aon_Livingroom.hpp"
#include "LlamaBay_House_Aon_Kitchen.hpp"
#include "LlamaBay_House_Aon_Downstairs.hpp"
#include <fstream>

void LlamaBay_House_Aon_Hallway::initialize() {
	loadScene(nlohmann::json::parse(std::ifstream{resource_paths::json::llamabay_house_aon_hallway}));

	if (Game::string_lastRoom == "LlamaBay_House_Aon_Livingroom" || Game::string_lastRoom == "") {
		Game::player->setPosition(40, 88);
		Game::player->sprite.setTextureRect(TextureRects::character_flynn_overworld_right);
	}
	else if (Game::string_lastRoom == "LlamaBay_House_Aon_Kitchen") {
		Game::player->setPosition(105, 80);
		Game::player->sprite.setTextureRect(TextureRects::character_flynn_overworld_down);
	}
	else if (Game::string_lastRoom == "LlamaBay_House_Aon_Downstairs") {
		Game::player->setPosition(189, 128);
		Game::player->sprite.setTextureRect(TextureRects::character_flynn_overworld_up);
	}

	doorRect_kitchen = sf::FloatRect(103, 68, 28, 8);

	roomObjects.add(TextureRects::object_house_aon_hallway_wall, 0);
	roomObjects[0].setOrigin(0, 74);
	roomObjects[0].setPosition(0, 94);

	viewCenter.y -= 20;
	Game::player->centerViewX(this);
	Game::player->updateMovement(this);
}
void LlamaBay_House_Aon_Hallway::update() {
	switch (state) {
	case 0: {
		fadeIn();
		if (getBlackOpacity() == 0) state++;
		break;
	}
	case 1: {
		Game::player->updateMovement(this);
		if (Game::player->sprite.getPosition().x < 15 && Game::player->sprite.getPosition().y < 94) {
			state = 2;
		}
		else if (Game::player->getWillOpenDoor(doorRect_kitchen, Player::Up)) {
			state = 3;
		}
		else if (Game::player->sprite.getPosition().y > 133) {
			state = 4;
		}
		break;
	}
	case 2: {
		fadeOut();
		if (getBlackOpacity() == 100) {
			Game::setRoom(new LlamaBay_House_Aon_Livingroom);
		}
		break;
	}
	case 3: {
		fadeOut();
		if (getBlackOpacity() == 100) {
			Game::setRoom(new LlamaBay_House_Aon_Kitchen);
		}
		break;
	}
	case 4: {
		fadeOut();
		if (getBlackOpacity() == 100) {
			Game::setRoom(new LlamaBay_House_Aon_Downstairs);
		}
	}
	}
}
void LlamaBay_House_Aon_Hallway::draw() {
	drawScene();
	window->draw(blackRectangle);
}

std::string LlamaBay_House_Aon_Hallway::getName() {
	return "LlamaBay_House_Aon_Hallway";
}