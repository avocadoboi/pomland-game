#pragma once
#include "../main/Events.hpp"

class GameButton{
public:
	enum Type {
		Rectangle,
		Text
	};

private:
	Type type;

	sf::Text text;

	sf::RectangleShape rect;

	sf::Vector2f origin;

	sf::Color color_notSelected = COLOR_GOLD_YELLOW_DARK;
	sf::Color color_selected = COLOR_GOLD_YELLOW;

	int characterSize = 35;

	bool isSelected = false;

public:
	GameButton();
	GameButton(std::string p_string);
	GameButton(sf::Vector2f size);

	static void update(std::vector<std::unique_ptr<GameButton>>& buttons);
	static void draw(std::vector<std::unique_ptr<GameButton>>& buttons);

	void draw();

	void setString(std::string p_string);
	std::string getString();
	
	void setSize(int p_characterSize);
	void setSize(float x, float y);

	void setPosition(sf::Vector2f position);
	void setPosition(float p_x, float p_y);
	sf::Vector2f getPosition();

	void setOrigin(sf::Vector2f p_pos);
	void setOrigin(float p_x, float p_y);

	void setIsSelected(bool p_isSelected);
	bool getIsSelected();

	void setColors(sf::Color p_color_selected, sf::Color p_color_notSelected);
	sf::FloatRect getGlobalBounds();
};