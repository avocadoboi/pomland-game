#pragma once
#include "../main/global.hpp"

class RoomObject {
private:
	sf::Sprite sprite;

	unsigned int bottomWidth = 0;

public:
	RoomObject();
	RoomObject(sf::IntRect p_textureRect, unsigned int p_bottomWidth);

	void draw();
	
	void setTextureRect(sf::IntRect rect);
	sf::IntRect getTextureRect() const;

	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);

	void setOrigin(sf::Vector2f origin);
	void setOrigin(float x, float y);
	sf::Vector2f getOrigin() const;

	void setBottomWidth(unsigned int p_height);
	sf::FloatRect getCollisionRect() const;
};