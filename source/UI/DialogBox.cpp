#include "DialogBox.hpp"
#include "../resource/TextureRects.hpp"

//
// Private
//

void DialogBox::updateTextLineBreaks() {
	auto const previousTextString = text.getString();
	text.setString(m_string);

	int lastSpaceIndex = -1;
	for (std::size_t a{}; a < m_string.size(); ++a) {
		if (m_string[a] == ' ') {
			lastSpaceIndex = static_cast<int>(a);
		}
		if (lastSpaceIndex != -1 && text.findCharacterPos(a).x > sprite.getGlobalBounds().left + sprite.getGlobalBounds().width - 5) {
			m_string[static_cast<std::size_t>(lastSpaceIndex)] = '\n';
			text.setString(m_string);
		}
	}
	text.setString(previousTextString);
	animatedString.set(m_string);
}

//
// Public
//

DialogBox::DialogBox() {
	sprite.setTexture(*texture);
	sprite.setTextureRect(TextureRects::UI_textbox);
	sprite.setOrigin(sprite.getGlobalBounds().width * 0.5f, sprite.getGlobalBounds().height);

	text.setFont(font);
	text.setCharacterSize(35 * 8);
	text.setScale(0.035f, 0.035f);
	text.setFillColor(sf::Color::White);

	animatedString.setSpeed(CHARACTER_TALK_TEXT_FREQUENCY);
}

//-------------------------------------------------------------

void DialogBox::reset() {
	setAreButtonsVisible(false);
	setIsVisible(false);
	setString("");
	counter = 0;
}
void DialogBox::update() {
	sprite.setPosition(round(viewCenter.x), round(viewCenter.y + GAME_SIZE.y * 0.5f));
	character->sprite_closeup.setOrigin(0, character->sprite_closeup.getGlobalBounds().height*0.5f);
	character->sprite_closeup.setPosition(sprite.getGlobalBounds().left + 5, sprite.getGlobalBounds().top + sprite.getGlobalBounds().height * 0.5f);

	//-------------------------------------------------------------

	bool wasChanged = animatedString.update();

	if (animatedString.get().size() > 0) {
		if (!animatedString.getIsAnimationDone() && Events::wasContinueKeyPressed) {
			animatedString.complete();
			Events::wasContinueKeyPressed = false;
		}
		if (animatedString.get().back() != '.' && animatedString.get().back() != '!' && animatedString.get().back() != '?') {
			if (character->animation_closeup != nullptr) {
				character->animation_closeup->update();
			}
			if (wasChanged && animatedString.get().back() != ' ' && animatedString.get().size() % CHARACTER_TALK_SOUND_FREQUENCY == 0) {
				character->voice.play();
			}
		}
		else if (character->animation_closeup != nullptr && character->animation_closeup->getNumberOfTextureRects() > 0) {
			character->sprite_closeup.setTextureRect(character->animation_closeup->getTextureRect(0));
		}
		text.setString(animatedString.get());
	}

	//-------------------------------------------------------------

	if (areButtonsActive) {
		text.setPosition(round(viewCenter.x) - text.getGlobalBounds().width * 0.5f, sprite.getGlobalBounds().top + 4.5f);
	}
	else {
		text.setPosition(sprite.getGlobalBounds().left + 10.f + character->sprite_closeup.getGlobalBounds().width, sprite.getGlobalBounds().top + 4.5f);
	}
	if (areButtonsActive) {
		GameButton::update(buttons);
		buttons[0]->setPosition(
			sprite.getGlobalBounds().left + sprite.getGlobalBounds().width*0.25f - buttons[0]->getGlobalBounds().width*0.5f,
			round(round(viewCenter.y) + GAME_SIZE.y * 0.5f) - 20.f - buttons[0]->getGlobalBounds().height*0.5f
		);
		buttons[1]->setPosition(
			sprite.getGlobalBounds().left + sprite.getGlobalBounds().width*0.75f - buttons[0]->getGlobalBounds().width*0.5f,
			round(round(viewCenter.y) + GAME_SIZE.y * 0.5f) - 20.f - buttons[1]->getGlobalBounds().height*0.5f
		);
	}
}
void DialogBox::draw() {
	window->draw(sprite);
	window->draw(text);
	window->draw(character->sprite_closeup);
	if (areButtonsActive) {
		GameButton::draw(buttons);
	}
}

//-------------------------------------------------------------

void DialogBox::setAreButtonsVisible(bool p_areButtonsActive) {
	areButtonsActive = p_areButtonsActive;
}
void DialogBox::setButtonStrings(std::string string_0, std::string string_1) {
	buttons.resize(0);
	buttons.push_back(make_unique<GameButton>(string_0));
	buttons[0]->setIsSelected(true);
	buttons.push_back(make_unique<GameButton>(string_1));
}
int DialogBox::getSelectedButtonIndex() {
	for (int c = 0; c < (int)buttons.size(); c++) {
		if (buttons[c]->getIsSelected()) return c;
	}
	buttons[0]->setIsSelected(true);
	return 0;
}

void DialogBox::setString(std::string p_string) {
	animatedString.set(p_string);
	m_string = p_string;

	// It needs to update the text position before it updates the line breaks.
	update();
	updateTextLineBreaks();
	text.setString("");
	animatedString.reset();

	counter++;
}
std::string DialogBox::getString() {
	return m_string;
}
bool DialogBox::getHasTalked() {
	return animatedString.getIsAnimationDone();
}

//-------------------------------------------------------------

void DialogBox::setIsVisible(bool p_isVisible) {
	sprite.setColor(sf::Color(255, 255, 255, (p_isVisible) ? 255 : 0));
	character->sprite_closeup.setColor(sf::Color(255, 255, 255, (p_isVisible) ? 255 : 0));
	text.setFillColor(sf::Color(255, 255, 255, (p_isVisible) ? 255 : 0));
	isVisible = p_isVisible;
}
bool DialogBox::getIsVisible() {
	return isVisible;
}
