#include "Events.hpp"
#include "Game.hpp"

//
// Private
//

sf::Event Events::event;

//
// Public
//

void Events::update() {
	pressedKey = sf::Keyboard::Key(-1);
	releasedKey = sf::Keyboard::Key(-1);

	wasTextEntered = false;
	wasContinueKeyPressed = false;

	while (window->pollEvent(event)) {
		if (event.type == sf::Event::KeyPressed) {
			pressedKey = event.key.code;

			switch (event.key.code) {
			case sf::Keyboard::Left: isLeftPressed = true; break;
			case sf::Keyboard::Right: isRightPressed = true; break;
			case sf::Keyboard::Up: isUpPressed = true; break;
			case sf::Keyboard::Down: isDownPressed = true; break;
			case sf::Keyboard::Return: wasContinueKeyPressed = true; break;
			case sf::Keyboard::RControl: pressedKey = sf::Keyboard::LControl; break;
			case sf::Keyboard::Z: wasContinueKeyPressed = true; break;
			case sf::Keyboard::Space: wasContinueKeyPressed = true; break;
			default: break;
			}
		}

		if (event.type == sf::Event::KeyReleased) {
			releasedKey = event.key.code;

			switch (event.key.code) {
			case sf::Keyboard::Left: isLeftPressed = false; break;
			case sf::Keyboard::Right: isRightPressed = false; break;
			case sf::Keyboard::Up: isUpPressed = false; break;
			case sf::Keyboard::Down: isDownPressed = false; break;
			case sf::Keyboard::RControl: releasedKey = sf::Keyboard::LControl; break;
			default: break;
			}
		}

		if (event.type == sf::Event::TextEntered) {
			wasTextEntered = true;
			enteredCharacter = (char)event.text.unicode;
		}

		if (event.type == sf::Event::Closed) Game::exit();
	}
	frameCount++;
}
void Events::reset() {
	Events::pressedKey = sf::Keyboard::Key(-1);
	Events::releasedKey = sf::Keyboard::Key(-1);
	Events::enteredCharacter = ' ';
	Events::wasTextEntered = false;
	Events::wasContinueKeyPressed = false;
	Events::isLeftPressed = false;
	Events::isRightPressed = false;
	Events::isUpPressed = false;
	Events::isDownPressed = false;
}

sf::Keyboard::Key Events::pressedKey = sf::Keyboard::Key(-1);
sf::Keyboard::Key Events::releasedKey = sf::Keyboard::Key(-1);

char Events::enteredCharacter = ' ';

bool Events::wasTextEntered = false;
bool Events::wasContinueKeyPressed = false;
bool Events::isLeftPressed = false;
bool Events::isRightPressed = false;
bool Events::isUpPressed = false;
bool Events::isDownPressed = false;