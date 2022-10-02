#include "Player.hpp"
#include "../rooms/OverworldRoom.hpp"

//
// Public
//

Player::Player() : Character("") {
	animations["walk_left"].setSprite(sprite);
	animations["walk_left"].setTextureRects({
		TextureRects::character_flynn_overworld_left,
		TextureRects::character_flynn_overworld_left_walking_0,
		TextureRects::character_flynn_overworld_left,
		TextureRects::character_flynn_overworld_left_walking_1
		});
	animations["walk_right"].setSprite(sprite);
	animations["walk_right"].setTextureRects({
		TextureRects::character_flynn_overworld_right,
		TextureRects::character_flynn_overworld_right_walking_0,
		TextureRects::character_flynn_overworld_right,
		TextureRects::character_flynn_overworld_right_walking_1
		});
	animations["walk_up"].setSprite(sprite);
	animations["walk_up"].setTextureRects({
		TextureRects::character_flynn_overworld_up,
		TextureRects::character_flynn_overworld_up_walking_0,
		TextureRects::character_flynn_overworld_up,
		TextureRects::character_flynn_overworld_up_walking_1
		});
	animations["walk_down"].setSprite(sprite);
	animations["walk_down"].setTextureRects({
		TextureRects::character_flynn_overworld_down,
		TextureRects::character_flynn_overworld_down_walking_0,
		TextureRects::character_flynn_overworld_down,
		TextureRects::character_flynn_overworld_down_walking_1
		});
	animations["walk_left_outOfBed"].setSprite(sprite);
	animations["walk_left_outOfBed"].setTextureRects({
		TextureRects::character_flynn_overworld_down,
		TextureRects::character_flynn_overworld_left,
		TextureRects::character_flynn_overworld_left_sitting,
		TextureRects::character_flynn_overworld_left
		});
	animations["walk_left_outOfBed"].setTextureRectAnimationFrequency(40);
}

//-------------------------------------------------------------

sf::FloatRect Player::getCollisionRectangle() {
	return sf::FloatRect(
		position.x, position.y - (float)PLAYER_FOOT_LENGTH,
		(float)TextureRects::character_flynn_overworld_right.width, (float)PLAYER_FOOT_LENGTH + 1
	);
}
bool Player::getWillOpenInfoDialogBox(const sf::FloatRect& p_intersectionRect, Heading p_heading) {
	sf::FloatRect playerRect = getCollisionRectangle();
	playerRect.left -= 1.f;
	playerRect.top -= 1.f;
	playerRect.width += 2.f;
	playerRect.height += 2.f;
	if (Events::wasContinueKeyPressed && p_intersectionRect.intersects(playerRect)) {
		switch (p_heading) {
		case Left:
			return sprite.getTextureRect() == TextureRects::character_flynn_overworld_left;
		case Right:
			return sprite.getTextureRect() == TextureRects::character_flynn_overworld_right;
		case Up:
			return sprite.getTextureRect() == TextureRects::character_flynn_overworld_up;
		case Down:
			return sprite.getTextureRect() == TextureRects::character_flynn_overworld_down;
		}
	}
	return false;
}
bool Player::getWillOpenDoor(const sf::FloatRect& p_intersectionRect, Heading p_heading) {
	if (p_intersectionRect.intersects(getCollisionRectangle())) {
		switch (p_heading) {
		case Left:
			return sprite.getTextureRect() == TextureRects::character_flynn_overworld_left;
		case Right:
			return sprite.getTextureRect() == TextureRects::character_flynn_overworld_right;
		case Up:
			return sprite.getTextureRect() == TextureRects::character_flynn_overworld_up;
		case Down:
			return sprite.getTextureRect() == TextureRects::character_flynn_overworld_down;
		}
	}
	return false;
}

void Player::setPosition(float p_x, float p_y) {
	position.x = p_x;
	position.y = p_y;
	sprite.setPosition(p_x, p_y);
}
void Player::setPosition(const sf::Vector2f& p_position) {
	position = p_position;
	sprite.setPosition(position);
}
void Player::updateMovement(OverworldRoom* p_room) {
	//
	// View animation
	//

	if (p_room->sceneSize.x > GAME_SIZE.x) {
		centerViewX(p_room);

		if (viewCenter.x - GAME_SIZE.x*0.5f < 0.f) {
			viewCenter.x = GAME_SIZE.x*0.5f;
		}
		if (viewCenter.x + GAME_SIZE.x*0.5f > p_room->sceneSize.x) {
			viewCenter.x = (float)p_room->sceneSize.x - GAME_SIZE.x*0.5f;
		}
	}
	if (p_room->sceneSize.y > GAME_SIZE.y) {
		centerViewY(p_room);

		if (viewCenter.y - GAME_SIZE.y*0.5f < 0.f) {
			viewCenter.y = GAME_SIZE.y*0.5f;
		}
		if (viewCenter.y + GAME_SIZE.y*0.5f > p_room->sceneSize.y) {
			viewCenter.y = (float)p_room->sceneSize.y - GAME_SIZE.y*0.5f;
		}
	}

	//
	// Control
	//

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
		walkSpeed = PLAYER_WALK_SPEED_FAST;
	}
	else {
		walkSpeed = PLAYER_WALK_SPEED_NORMAL;
	}

	if (Events::isLeftPressed && !Events::isRightPressed) {
		velocity.x = (float)-walkSpeed;
	}
	else if (Events::isRightPressed && !Events::isLeftPressed) {
		velocity.x = (float)walkSpeed;
	}
	else {
		velocity.x = 0;
	}

	if (Events::isUpPressed && !Events::isDownPressed) {
		velocity.y = (float)-walkSpeed;
	}
	else if (Events::isDownPressed && !Events::isUpPressed) {
		velocity.y = (float)walkSpeed;
	}
	else {
		velocity.y = 0;
	}

	//
	// Collisions
	//

	sprite.setOrigin(0, sprite.getGlobalBounds().height);
	sf::FloatRect playerRect = getCollisionRectangle();

	auto collisionRectangles = p_room->collisionRectangles;
	for (int a = 0; a < (int)p_room->roomObjects.getNumberOfRoomObjects(); a++) {
		sf::FloatRect collisionRect = p_room->roomObjects[a].getCollisionRect();
		if (collisionRect.width != 0 && collisionRect.height != 0) {
			collisionRectangles.push_back(collisionRect);
		}
	}

	for (int i_collisionIteration = 0; i_collisionIteration < PLAYER_NUMBER_OF_COLLISION_ITERATIONS; i_collisionIteration++) {
		// Resolve rectangle collisions
		for (int a = 0; a < (int)collisionRectangles.size(); a++) {
			sf::FloatRect& rect = collisionRectangles[a];
			sf::Vector2f delta = sf::Vector2f(playerRect.left + playerRect.width*0.5f + velocity.x - rect.left - rect.width*0.5f, playerRect.top + playerRect.height*0.5f + velocity.y - rect.top - rect.height*0.5f);
			sf::Vector2f overlap = sf::Vector2f(std::max(0.0f, playerRect.width*0.5f + rect.width*0.5f - abs(delta.x)), std::max(0.0f, playerRect.height*0.5f + rect.height*0.5f - std::abs(delta.y)));

			if (overlap.x < overlap.y) {
				velocity.x += overlap.x * getSign(delta.x);
			}
			else {
				velocity.y += overlap.y * getSign(delta.y);
			}
		}

		// Resolve triangle collisions
		if (p_room->collisionTriangles.size() > 0) {
			sf::Vector2f playerRectPoints[4] = {
				sf::Vector2f(playerRect.left, playerRect.top),
				sf::Vector2f(playerRect.left + playerRect.width, playerRect.top),
				sf::Vector2f(playerRect.left + playerRect.width, playerRect.top + playerRect.height),
				sf::Vector2f(playerRect.left, playerRect.top + playerRect.height)
			};
			sf::Vector2f playerRectNormals[4] = {
				sf::Vector2f(-1, 0),
				sf::Vector2f(1, 0),
				sf::Vector2f(0, -1),
				sf::Vector2f(0, 1)
			};
			for (int a = 0; a < (int)p_room->collisionTriangles.size(); a++) {
				Triangle& triangle = p_room->collisionTriangles[a];

				float intersectionDepth = 0;
				sf::Vector2f* intersectionNormal = triangle.sideNormals;
				bool isIntersecting = true;

				for (int b = 0; b < 7; b++) {
					sf::Vector2f* normal;
					if (b < 3) {
						normal = triangle.sideNormals + b;
					}
					else {
						normal = playerRectNormals + b - 3;
					}

					float min_0, max_0;
					for (int c = 0; c < 3; c++) {
						float projectedPoint = getVector2DotProduct(*normal, triangle.points[c]);
						if (c == 0 || projectedPoint < min_0) {
							min_0 = projectedPoint;
						}
						if (c == 0 || projectedPoint > max_0) {
							max_0 = projectedPoint;
						}
					}

					float min_1, max_1;
					for (int c = 0; c < 4; c++) {
						float projectedPoint = getVector2DotProduct(*normal, playerRectPoints[c] + velocity);
						if (c == 0 || projectedPoint < min_1) {
							min_1 = projectedPoint;
						}
						if (c == 0 || projectedPoint > max_1) {
							max_1 = projectedPoint;
						}
					}

					if (max_0 <= min_1 || max_1 <= min_0) {
						isIntersecting = false;
						break;
					}

					float thisIntersectionDepth = (b < 3) ? (max_0 - min_1) : -(max_1 - min_0);
					if (intersectionDepth == 0 || abs(thisIntersectionDepth) < abs(intersectionDepth)) {
						intersectionDepth = thisIntersectionDepth;
						intersectionNormal = normal;
					}
				}

				if (isIntersecting) {
					velocity += *intersectionNormal * intersectionDepth;
				}
			}
		}
	}

	position += velocity;
	sprite.setPosition(round(position.x), round(position.y));

	//
	// Update animations
	//

	if (abs(velocity.x) >= PLAYER_MIN_ANIMATED_VELOCITY && !Events::isUpPressed && !Events::isDownPressed) {
		if (Events::isLeftPressed && !Events::isRightPressed) {
			animationHeading = 0;
		}
		else if (!Events::isLeftPressed && Events::isRightPressed) {
			animationHeading = 1;
		}
	}
	else if (abs(velocity.y) >= PLAYER_MIN_ANIMATED_VELOCITY && !Events::isLeftPressed && !Events::isRightPressed) {
		if (Events::isUpPressed && !Events::isDownPressed) {
			animationHeading = 2;
		}
		else if (!Events::isUpPressed && Events::isDownPressed) {
			animationHeading = 3;
		}
	}
	else if (abs(velocity.x) >= PLAYER_MIN_ANIMATED_VELOCITY && abs(velocity.y) >= PLAYER_MIN_ANIMATED_VELOCITY) {
		if (animationHeading == -1) {
			if (velocity.x < 0) {
				animationHeading = 0;
			}
			else if (velocity.x > 0) {
				animationHeading = 1;
			}
		}
	}
	else if (abs(velocity.x) < PLAYER_MIN_ANIMATED_VELOCITY && abs(velocity.y) < PLAYER_MIN_ANIMATED_VELOCITY) {
		if ((Events::isLeftPressed || Events::isRightPressed) != (Events::isUpPressed || Events::isDownPressed)) {
			if (Events::isLeftPressed && !Events::isRightPressed) {
				animationHeading = 0;
			}
			else if (Events::isRightPressed && !Events::isLeftPressed) {
				animationHeading = 1;
			}
			if (Events::isUpPressed && !Events::isDownPressed) {
				animationHeading = 2;
			}
			else if (Events::isDownPressed && !Events::isUpPressed) {
				animationHeading = 3;
			}
		}

		if (animationHeading == 0) {
			sprite.setTextureRect(TextureRects::character_flynn_overworld_left);
		}
		else if (animationHeading == 1) {
			sprite.setTextureRect(TextureRects::character_flynn_overworld_right);
		}
		else if (animationHeading == 2) {
			sprite.setTextureRect(TextureRects::character_flynn_overworld_up);
		}
		else if (animationHeading == 3) {
			sprite.setTextureRect(TextureRects::character_flynn_overworld_down);
		}
		animationHeading = -1;
		return;
	}
	else if (abs(velocity.x) >= PLAYER_MIN_ANIMATED_VELOCITY) {
		if (Events::isLeftPressed && !Events::isRightPressed) {
			animationHeading = 0;
		}
		else if (!Events::isLeftPressed && Events::isRightPressed) {
			animationHeading = 1;
		}
	}
	else if (abs(velocity.y) >= PLAYER_MIN_ANIMATED_VELOCITY) {
		if (Events::isUpPressed && !Events::isDownPressed) {
			animationHeading = 2;
		}
		else if (!Events::isUpPressed && Events::isDownPressed) {
			animationHeading = 3;
		}
	}

	if (animationHeading == 0) {
		animations["walk_left"].update();
	}
	else if (animationHeading == 1) {
		animations["walk_right"].update();
	}
	else if (animationHeading == 2) {
		animations["walk_up"].update();
	}
	else if (animationHeading == 3) {
		animations["walk_down"].update();
	}
}
void Player::resetHeading() {
	animationHeading = -1;
}

//-------------------------------------------------------------

void Player::centerViewX() {
	viewCenter.x = sprite.getPosition().x + TextureRects::character_flynn_overworld_down.width*0.5f;
}
void Player::centerViewY() {
	viewCenter.y = sprite.getPosition().y - TextureRects::character_flynn_overworld_down.height*0.5f;
}
void Player::centerView() {
	centerViewX();
	centerViewY();
}

void Player::centerViewX(OverworldRoom* p_room) {
	viewCenter.x = std::max(GAME_SIZE.x*0.5f, std::min(position.x + TextureRects::character_flynn_overworld_down.width*0.5f, p_room->sceneSize.x - GAME_SIZE.x*0.5f));
}
void Player::centerViewY(OverworldRoom* p_room) {
	viewCenter.y = std::max(GAME_SIZE.y*0.5f, std::min(position.y - TextureRects::character_flynn_overworld_down.height*0.5f, p_room->sceneSize.y - GAME_SIZE.y*0.5f));
}
void Player::centerView(OverworldRoom* p_room) {
	centerViewX(p_room);
	centerViewY(p_room);
}

//-------------------------------------------------------------

void Player::setName(std::string p_name) {
	name = p_name;
}
const std::string& Player::getName() {
	return name;
}
int Player::getMaxNameLength() {
	return 8;
}

//-------------------------------------------------------------

void Player::setLives(int p_lives) {
	lives = p_lives;
}
int Player::getLives() {
	return lives;
}
void Player::damage(int amount) {
	lives -= amount;
}
