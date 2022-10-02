#include "StartMenu_Controls.hpp"
#include "StartMenu_InputName.hpp"
#include "Intro_0.hpp"

void StartMenu_Controls::initialize() {
	text_controlsTitle.setFont(font);
	text_controlsTitle.setCharacterSize(35 * 8);
	text_controlsTitle.setScale(0.04f, 0.04f);
	text_controlsTitle.setString("Controls:");
	text_controlsTitle.setFillColor(sf::Color::White);
	text_controlsTitle.setPosition((GAME_SIZE.x - text_controlsTitle.getGlobalBounds().width) / 2, 3);

	for (int c = 0; c < 4; c++) {
		text_controls.push_back(sf::Text());
		text_controls[c].setFont(font);
		text_controls[c].setCharacterSize(35 * 8);
		text_controls[c].setScale(0.035f, 0.035f);
		text_controls[c].setFillColor(sf::Color::White);
	}
	text_controls[0].setString("F4: Toggle fullscreen.");
	text_controls[1].setString("Enter: Continue/press button.");
	text_controls[2].setString("Arrow keys: Select button/walk.");
	text_controls[3].setString("Esc: Open floating menu.");
	for (int c = 0; c < (int)text_controls.size(); c++) {
		text_controls[c].setPosition((GAME_SIZE.x - text_controls[c].getGlobalBounds().width) * 0.5f, 23.f + 15.f * (float)c);
	}

	buttons.push_back(std::make_unique<GameButton>("Back"));
	buttons[0]->setPosition(5, 2);
	buttons.push_back(std::make_unique<GameButton>("Start"));
	buttons[1]->setOrigin(buttons[1]->getGlobalBounds().width, 0);
	buttons[1]->setPosition(GAME_SIZE.x - 5, 2);
	buttons[1]->setIsSelected(true);
}
void StartMenu_Controls::update() {
	GameButton::update(buttons);
	if (Events::wasContinueKeyPressed) {
		if (buttons[0]->getIsSelected()) {
			state = 1;
		}
		if (buttons[1]->getIsSelected()) {
			state = 2;
		}
	}

	switch (state) {
	case 0: {
		fadeIn();
		break;
	}
	case 1: {
		fadeOut();
		if (getBlackOpacity() == 100) {
			Game::setRoom(new StartMenu_InputName());
			return;
		}
		break;
	}
	case 2: {
		fadeOut();
		if (getBlackOpacity() == 100) {
			Game::setRoom(new Intro_0());
		}
	}
	}
}
void StartMenu_Controls::draw() {
	buttons[0]->draw();
	buttons[1]->draw();
	window->draw(text_controlsTitle);
	for (int c = 0; c < (int)text_controls.size(); c++) {
		window->draw(text_controls[c]);
	}
	window->draw(blackRectangle);
}

std::string StartMenu_Controls::getName() {
	return "StartMenu_Controls";
}