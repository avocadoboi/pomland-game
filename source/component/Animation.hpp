#include "../main/global.hpp"

//-------------------------------------------------------------

class Animation {
private:
	sf::Sprite* sprite = nullptr;
	std::vector<sf::IntRect> textureRects;
	int currentTextureRectIndex = 0;
	int textureRectAnimationRate = 12;

	//-------------------------------------------------------------

	sf::Vector2f startPosition;
	sf::Vector2f destinationPosition;
	sf::Vector2f velocity;

	int positionAnimationSpeed = 1;
	bool isPositionAnimationEnabled = false;

public:
	Animation() {}
	Animation(sf::Sprite &p_sprite);

	void operator=(Animation& animation);

	//-------------------------------------------------------------
	
	void update();
	void reset();

	//-------------------------------------------------------------
	
	void setSprite(sf::Sprite &p_sprite);
	void setSprite(sf::Sprite* p_sprite);
	sf::Sprite* getSprite();
	
	void setTextureRects(std::vector<sf::IntRect> p_textureRects);
	void setTextureRectAnimationFrequency(int rate);
	void setCurrentTextureRectIndex(int index);
	int getCurrentTextureRectIndex();
	int getNumberOfTextureRects();
	sf::IntRect getTextureRect(unsigned int index);
	
	//-------------------------------------------------------------

	void setDestinationPosition(sf::Vector2f p_destinationPosition);
	void setPositionAnimationSpeed(int speed);
	void setVelocity(sf::Vector2f p_velocity);
	void setIsPositionAnimationEnabled(bool p_isPositionAnimationEnabled);
};