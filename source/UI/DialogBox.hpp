#pragma once
#include "../main/Events.hpp"
#include "../UI/GameButton.hpp"
#include "../character/Character.hpp"
#include "../component/AnimatedString.hpp"
#include "../resource/TextureRects.hpp"

class DialogBox {
private:
	Character* character;

	//-------------------------------------------------------------

	// Box sprite
	sf::Sprite sprite;
	
	std::vector<std::unique_ptr<GameButton>> buttons;
	bool areButtonsActive = false;

	sf::Text text;
	AnimatedString animatedString;
	std::string m_string;
	void updateTextLineBreaks();

	bool isVisible = true;

public:
	DialogBox();

	//-------------------------------------------------------------
	
	void reset();
	void update();
	void draw();

	//-------------------------------------------------------------
	
	void setCharacter(Character* const p_character) {
		character = p_character;
	}
	Character* getCharacter() const {
		return character;
	}

	//-------------------------------------------------------------
	
	void setAreButtonsVisible(bool p_areButtonsActive);
	void setButtonStrings(std::string string_0, std::string string_1);
	int getSelectedButtonIndex();

	void setString(std::string p_string);
	std::string getString();
	bool getHasTalked();

	int counter = 0;

	//-------------------------------------------------------------

	void setIsVisible(bool p_isVisible);
	bool getIsVisible();
};