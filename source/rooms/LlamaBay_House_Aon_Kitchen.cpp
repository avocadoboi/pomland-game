#include "LlamaBay_House_Aon_Kitchen.hpp"
#include "LlamaBay_House_Aon_Hallway.hpp"
#include <fstream>

void LlamaBay_House_Aon_Kitchen::initialize() {
	Game::player->setPosition(98, 150);

	loadScene(nlohmann::json::parse(std::ifstream{resource_paths::json::llamabay_house_aon_kitchen}));
}
void LlamaBay_House_Aon_Kitchen::update() {
	switch (state) {
	case 0: {
		fadeIn();
		if (getBlackOpacity() == 0) state++;
		break;
	}
	case 1: {
		Game::player->updateMovement(this);

		if (Game::player->getWillOpenInfoDialogBox(sf::FloatRect(122, 70, 24, 27), Player::Right)) {
			Game::dialogBox->setString("It's a book.");
			Game::dialogBox->setIsVisible(true);
			state = 2;
		}
		if (Game::player->sprite.getPosition().y > 150) {
			state = 3;
		}
		break;
	}
	case 2: {
		if (Events::wasContinueKeyPressed && Game::dialogBox->getHasTalked()) {
			switch (Game::dialogBox->counter) {
			case 1:
				Game::dialogBox->setString("Read one page?");
				Game::dialogBox->setAreButtonsVisible(true);
				Game::dialogBox->setButtonStrings("Yes", "No");
				break;
			case 2:
				if (Game::dialogBox->getSelectedButtonIndex() == 0) {
					Game::dialogBox->setAreButtonsVisible(false);
					Game::dialogBox->setString("This is my favorite recipe; chocolate bread, with strawberry filling. - Aon.");
				}
				else {
					Game::dialogBox->reset();
					state = 1;
				}
				break;
			case 3:
				Game::dialogBox->reset();
				state = 1;
			}
		}
		break;
	}
	case 3: {
		fadeOut();
		if (getBlackOpacity() == 100) {
			Game::setRoom(new LlamaBay_House_Aon_Hallway());
		}
	}
	}
	Game::dialogBox->update();
}
void LlamaBay_House_Aon_Kitchen::draw() {
	drawScene();
	Game::dialogBox->draw();
	window->draw(blackRectangle);
}

std::string LlamaBay_House_Aon_Kitchen::getName() {
	return "LlamaBay_House_Aon_Kitchen";
}