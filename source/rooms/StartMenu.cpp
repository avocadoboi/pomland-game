#include "StartMenu.hpp"
#include "StartMenu_InputName.hpp"

void StartMenu::initialize() {
	buttons.push_back(std::make_unique<GameButton>("New game"));
	buttons[0]->setOrigin(buttons[0]->getGlobalBounds().width / 2, buttons[0]->getGlobalBounds().height / 2);
	buttons[0]->setPosition((buttons[0]->getGlobalBounds().width / 2)*-1, 95);
	buttons[0]->setIsSelected(true);
	buttons.push_back(std::make_unique<GameButton>("Continue game"));
	buttons[1]->setOrigin(buttons[1]->getGlobalBounds().width / 2, buttons[1]->getGlobalBounds().height / 2);
	buttons[1]->setPosition(GAME_SIZE.x + (buttons[1]->getGlobalBounds().width / 2), 105);

	sprite_title.setTexture(*texture);
	sprite_title.setTextureRect(TextureRects::UI_title);
	sprite_title.setPosition((GAME_SIZE.x - sprite_title.getGlobalBounds().width) / 2, 25);

	text_demo.setFont(font);
	text_demo.setCharacterSize(40);
	text_demo.setScale(0.35f, 0.35f);
	text_demo.setString("Demo");
	text_demo.setPosition((GAME_SIZE.x - text_demo.getGlobalBounds().width) / 2, 55);
	text_demo.setFillColor(sf::Color(90, 85, 85));

	text_dog.setFont(font);
	text_dog.setScale(0.25f, 0.25f);
	text_dog.setCharacterSize(50);
	state_dogText = 0;

	music->openFromFile(resource_paths::music::start_menu);
	music->play();

	state = 0;
}
void StartMenu::update() {
	GameButton::update(buttons);

	switch (state) {
	case 0: {
		fadeIn();

		buttons[0]->setPosition((float)animateInt((int)buttons[0]->getPosition().x, int(GAME_SIZE.x*0.5f), 6), buttons[0]->getPosition().y);
		buttons[1]->setPosition((float)animateInt((int)buttons[1]->getPosition().x, int(GAME_SIZE.x*0.5f), 6), buttons[1]->getPosition().y);

		if (Events::pressedKey == sf::Keyboard::D) {
			switch (state_dogText) {
			case 0:
				text_dog.setString("Hello my friend, i like dogs!");
				state_dogText++;
				break;

			case 1:
				text_dog.setString("Do you like dogs?");
				state_dogText++;
				break;

			case 2:
				text_dog.setString("THAT'S A YES, GREAT!");
				state_dogText++;
				break;

			case 3:
				text_dog.setString("...");
				state_dogText++;
				break;

			case 4:
				text_dog.setString("...Just press space...");
				state_dogText++;
				break;

			case 5:
				text_dog.setString("");
				state_dogText = 0;
				break;
			}
			text_dog.setPosition((GAME_SIZE.x - text_dog.getGlobalBounds().width) / 2, GAME_SIZE.y - 40);
		}

		if (Events::wasContinueKeyPressed) state++;
		break;
	}
	case 1: {
		buttons[0]->setPosition((float)animateInt((int)buttons[0]->getPosition().x, int(WINDOW_SIZE.x + buttons[0]->getGlobalBounds().width * 0.5f), 6), buttons[0]->getPosition().y);
		buttons[1]->setPosition((float)animateInt((int)buttons[1]->getPosition().x, -int(buttons[1]->getGlobalBounds().width*0.5f), 6), buttons[1]->getPosition().y);
		if ((int)buttons[1]->getPosition().x == -int(buttons[1]->getGlobalBounds().width*0.5f)) {
			state++;
		}
		break;
	}
	case 2: {
		fadeOut();
		if (getBlackOpacity() == 100) {
			if (buttons[0]->getIsSelected()) {
				Game::setRoom(new StartMenu_InputName());
				return;
			}
		}
	}
	}
}
void StartMenu::draw() {
	window->draw(sprite_title);
	window->draw(text_demo);
	buttons[0]->draw();
	buttons[1]->draw();
	window->draw(text_dog);
	window->draw(blackRectangle);
}

std::string StartMenu::getName() {
	return "StartMenu";
}