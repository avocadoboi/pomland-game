#pragma once
#include "Character.hpp"
#include "../UI/DialogBox.hpp"
#include "../component/RoomObjects.hpp"
#include "../resource/TextureRects.hpp"
#include "../component/geometry.hpp"

class OverworldRoom;

class Player : public Character {
private:
	sf::Vector2f position;
	sf::Vector2f velocity;

	int animationHeading = -1;
	int walkSpeed;

	//-------------------------------------------------------------

	int lives;

public:
	enum Heading {
		Left,
		Right,
		Up,
		Down
	};

	struct Data {
		bool
			isConfused = false,
			isExcited = false,
			hasMetAon = false;
	} data;

	//-------------------------------------------------------------

	Player();

	//-------------------------------------------------------------

	sf::Vector2f getVelocity() const {
		return velocity;
	}
	sf::FloatRect getCollisionRectangle();
	bool getWillOpenInfoDialogBox(const sf::FloatRect& p_intersectionRect, Heading p_heading);
	bool getWillOpenDoor(const sf::FloatRect& p_intersectionRect, Heading p_heading);

	void setPosition(float p_x, float p_y);
	void setPosition(const sf::Vector2f& p_position);
	void updateMovement(OverworldRoom* p_room);

	void resetHeading();
	
	//-------------------------------------------------------------

	void centerViewX();
	void centerViewY();
	void centerView();

	void centerViewX(OverworldRoom* p_room);
	void centerViewY(OverworldRoom* p_room);
	void centerView(OverworldRoom* p_room);

	//-------------------------------------------------------------

	void setName(std::string p_name);
	const std::string& getName();
	int getMaxNameLength();

	//-------------------------------------------------------------

	void setLives(int p_lives);
	int getLives();
	void damage(int p_amount);
};

