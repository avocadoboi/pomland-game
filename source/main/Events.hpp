#pragma once
#include "global.hpp"

class Events {
private:
	static sf::Event event;

public:
	static void update();
	static void reset();

	static sf::Keyboard::Key pressedKey;
	static sf::Keyboard::Key releasedKey;

	static char enteredCharacter;

	static bool wasTextEntered;
	static bool wasContinueKeyPressed;
	static bool isLeftPressed;
	static bool isRightPressed;
	static bool isUpPressed;
	static bool isDownPressed;
};