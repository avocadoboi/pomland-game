#include "Intro_0.hpp"
#include "Intro_1.hpp"

void Intro_0::updateStringBreaks() {
	text_narrator.setString(animatedString.getTarget());
	insertBreaksInText(text_narrator, textWidth);
	animatedString.set(text_narrator.getString());
	text_narrator.setString("");
}

void Intro_0::initialize() {
	textWidth = 140;

	sprite_background.setTexture(*texture);
	sprite_background.setTextureRect(TextureRects::room_intro_0);
	sprite_background.setPosition((GAME_SIZE.x - sprite_background.getGlobalBounds().width) / 2, 10);

	animatedString.set("A city has been destroyed and everyone is dead.");
	animatedString.setSpeed(2);

	text_narrator.setFont(font);
	text_narrator.setCharacterSize(35 * 8);
	text_narrator.setScale(0.035f, 0.035f);
	text_narrator.setFillColor(sf::Color(220, 220, 220));
	text_narrator.setPosition((GAME_SIZE.x - textWidth)*0.5f, 110);

	updateStringBreaks();

	music->openFromFile(resource_paths::music::goodbye);
	music->setLoop(false);
	music->stop();
}
void Intro_0::update() {
	if (isBackgroundFadingIn) {
		fadeIn(3);
	}
	else {
		fadeOut(3);
	}

	if (Events::wasContinueKeyPressed) {
		animatedString.complete();
	}

	switch (state) {
	case 0: {
		fadeIn(4);
		if (getBlackOpacity() == 0) {
			music->play();
			state++;
		}
		break;
	}
	case 1: {
		animatedString.update();

		if (animatedString.getIsAnimationDone()) {
			if (pauseClock.getElapsedTime().asSeconds() >= 1) {
				animatedString.set("Everything's on fire and the streets that people used to live by are now empty. ");
				updateStringBreaks();
				sprite_background.setTextureRect(TextureRects::room_intro_1);
				state++;
			}
			isBackgroundFadingIn = false;
		}
		else {
			isBackgroundFadingIn = true;
			pauseClock.restart();
		}
		break;
	}
	case 2: {
		animatedString.update();

		if (animatedString.getIsAnimationDone()) {
			if (pauseClock.getElapsedTime().asSeconds() >= 1) {
				animatedString.set("This war didn't solve anything, it just killed innocent people and animals.");
				updateStringBreaks();
				sprite_background.setTextureRect(TextureRects::room_intro_2);
				state++;
			}
			isBackgroundFadingIn = false;
		}
		else {
			isBackgroundFadingIn = true;
			pauseClock.restart();
		}
		break;
	}
	case 3: {
		animatedString.update();

		if (animatedString.getIsAnimationDone()) {
			if (pauseClock.getElapsedTime().asSeconds() >= 1) {
				animatedString.set("But, one young human somewhere in the country escaped the fires and found a boat. ");
				updateStringBreaks();
				sprite_background.setTextureRect(TextureRects::room_intro_3);
				state++;
			}
			isBackgroundFadingIn = false;
		}
		else {
			isBackgroundFadingIn = true;
			pauseClock.restart();
		}
		break;
	}
	case 4: {
		animatedString.update();

		if (animatedString.getIsAnimationDone()) {
			if (pauseClock.getElapsedTime().asSeconds() >= 1) {
				animatedString.set("The child went to sea and let the boat choose their destiny. ");
				updateStringBreaks();
				sprite_background.setTextureRect(TextureRects::room_intro_4);
				state++;
			}
			isBackgroundFadingIn = false;
		}
		else {
			isBackgroundFadingIn = true;
			pauseClock.restart();
		}
		break;
	}
	case 5: {
		animatedString.update();

		if (animatedString.getIsAnimationDone()) {
			if (pauseClock.getElapsedTime().asSeconds() >= 1) {
				text_narrator.setFillColor(sf::Color::Transparent);
				state++;
			}
			isBackgroundFadingIn = false;
		}
		else {
			isBackgroundFadingIn = true;
			pauseClock.restart();
		}
		break;
	}
	case 6: {
		fadeOut(2);
		if (getBlackOpacity() == 100) {
			animatedString.set("A week later...");
			animatedString.setSpeed(10);
			text_narrator.setFillColor(sf::Color::White);
			state++;
		}
		break;
	}
	case 7: {
		animatedString.update();
		if (animatedString.getIsAnimationDone()) {
			if (pauseClock.getElapsedTime().asSeconds() >= 1) {
				Game::setRoom(new Intro_1());
				return;
			}
		}
		else {
			pauseClock.restart();
		}
	}
	}
	text_narrator.setString(animatedString.get());

	if (state == 7) {
		text_narrator.setPosition((GAME_SIZE.x - text_narrator.getGlobalBounds().width) / 2, (GAME_SIZE.y - text_narrator.getGlobalBounds().height) / 2);
	}
}
void Intro_0::draw() {
	window->draw(sprite_background);
	window->draw(blackRectangle);
	window->draw(text_narrator);
}

std::string Intro_0::getName() {
	return "Intro_0";
}