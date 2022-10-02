#include "StartMenu_InputName.hpp"
#include "StartMenu.hpp"
#include "StartMenu_Controls.hpp"

void StartMenu_InputName::initialize() {
	buttons.push_back(std::make_unique<GameButton>("Back"));
	buttons[0]->setPosition(5, 2);

	buttons.push_back(std::make_unique<GameButton>("Next"));
	buttons[1]->setOrigin(buttons[1]->getGlobalBounds().width, 0);
	buttons[1]->setPosition(GAME_SIZE.x - 5, 2);

	sf::Vector2f keyboardPosition(45, 50);
	for (int a = 0; a < 54; a++) {
		if (a == 52) {
			buttons.push_back(std::make_unique<GameButton>("backspace"));
		}
		else if (a == 53) {
			buttons.push_back(std::make_unique<GameButton>("clear"));
		}
		else {
			buttons.push_back(std::make_unique<GameButton>(std::string(1, char(((a < 26) ? (97) : (65 - 26)) + a))));
		}
		buttons.back()->setSize(50);
		buttons.back()->setColors(sf::Color(180, 180, 180), sf::Color(90, 90, 90));
		if (a == 0) {
			buttons.back()->setPosition(keyboardPosition);
		}
		else {
			buttons.back()->setPosition(
				((buttons.size() > 1 && buttons[buttons.size() - 2]->getPosition().x + buttons[buttons.size() - 2]->getGlobalBounds().width + buttons.back()->getGlobalBounds().width <= GAME_SIZE.x - keyboardPosition.x)
					? (buttons[buttons.size() - 2]->getPosition().x + buttons[buttons.size() - 2]->getGlobalBounds().width + 5) : (keyboardPosition.x)),
					((buttons.size() > 1 && buttons[buttons.size() - 2]->getPosition().x + buttons[buttons.size() - 2]->getGlobalBounds().width + buttons.back()->getGlobalBounds().width <= GAME_SIZE.x - keyboardPosition.x)
						? (buttons[buttons.size() - 2]->getPosition().y) : (buttons[buttons.size() - 2]->getPosition().y + 15))
			);
		}
	}
	buttons[2]->setIsSelected(true);

	text_typeName.setFont(font);
	text_typeName.setString("Type a name!");
	text_typeName.setScale(0.035f, 0.035f);
	text_typeName.setCharacterSize(35 * 8);
	text_typeName.setPosition((GAME_SIZE.x - text_typeName.getGlobalBounds().width) / 2 - 2, 10);
	text_typeName.setFillColor(sf::Color::White);

	text_input.setFont(font);
	text_input.setString(Game::player->getName());
	text_input.setScale(0.035f, 0.035f);
	text_input.setCharacterSize(35 * 9);
	text_input.setFillColor(sf::Color::White);

	writingSoundBuffer.loadFromFile(resource_paths::sound::write);
	writingSound.setBuffer(writingSoundBuffer);

	music->setVolume(30);
}
void StartMenu_InputName::update() {
	GameButton::update(buttons);

	if (Events::wasContinueKeyPressed) {
		writingSound.play();
		for (int a = 0; a < (int)buttons.size(); a++) {
			if (buttons[a]->getIsSelected()) {
				if (a < 54 && a > 1) {
					if ((int)nameTemp.size() < Game::player->getMaxNameLength()) {
						nameTemp.push_back(buttons[a]->getString()[0]);
					}
				}
				else if (a == 54) {
					if (nameTemp.size() > 0) {
						nameTemp.pop_back();
					}
				}
				else if (a == 55) {
					nameTemp.resize(0);
				}
			}
		}
		if (buttons[0]->getIsSelected()) {
			state = 1;
			Game::player->setName(nameTemp);
		}
		else if (buttons[1]->getIsSelected()) {
			if (nameTemp.size() > 1) {
				state = 2;
				Game::player->setName(nameTemp);
			}
		}
	}

	text_input.setString(nameTemp);
	text_input.setPosition(GAME_SIZE.x / 2 - text_input.getGlobalBounds().width / 2, 30);

	switch (state) {
	case 0: {
		fadeIn();
		break;
	}
	case 1: {
		fadeOut();
		if (getBlackOpacity() == 100) {
			Game::setRoom(new StartMenu());
			return;
		}
		break;
	}
	case 2: {
		fadeOut();
		if (getBlackOpacity() == 100) {
			Game::setRoom(new StartMenu_Controls());
			return;
		}
	}
	}
}
void StartMenu_InputName::draw() {
	window->draw(text_typeName);
	GameButton::draw(buttons);
	window->draw(text_input);
	window->draw(blackRectangle);
}

std::string StartMenu_InputName::getName() {
	return "StartMenu_InputName";
}