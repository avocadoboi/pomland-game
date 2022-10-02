#include "../component/RoomObjects.hpp"
#include "../character/Player.hpp"

//
// Public
//

RoomObjects::RoomObjects() {}
RoomObjects::~RoomObjects() {
	for (int a = 0; a < (int)roomObjects.size(); a++) {
		delete roomObjects[a];
	}
	roomObjects.clear();
}

void RoomObjects::draw() {
	for (int a = 0; a < (int)roomObjects.size(); a++) {
		roomObjects[a]->draw();
	}
}
void RoomObjects::draw(std::vector<Character*> characters) {
	for (int a = -1; a < (int)roomObjects.size(); a++) {
		if (a > -1) roomObjects[a]->draw();
		for (int b = 0; b < (int)characters.size(); b++) {
			if (a == -1) {
				if (characters[b]->sprite.getPosition().y <= roomObjects[a + 1]->getCollisionRect().top) {
					window->draw(characters[b]->sprite);
				}
			}
			else if (a == roomObjects.size() - 1) {
				if (characters[b]->sprite.getPosition().y > roomObjects[a]->getCollisionRect().top) {
					window->draw(characters[b]->sprite);
				}
			}
			else if (
				characters[b]->sprite.getPosition().y > roomObjects[a]->getCollisionRect().top &&
				characters[b]->sprite.getPosition().y <= roomObjects[a + 1]->getCollisionRect().top
				) {
				window->draw(characters[b]->sprite);
			}
		}
	}
}
void RoomObjects::draw(std::vector<Character>& characters) {
	for (int a = -1; a < (int)roomObjects.size(); a++) {
		if (a > -1) roomObjects[a]->draw();
		for (int b = 0; b < (int)characters.size(); b++) {
			if (a == -1) {
				if (characters[b].sprite.getPosition().y <= roomObjects[a + 1]->getCollisionRect().top) {
					window->draw(characters[b].sprite);
				}
			}
			else if (a == roomObjects.size() - 1) {
				if (characters[b].sprite.getPosition().y > roomObjects[a]->getCollisionRect().top) {
					window->draw(characters[b].sprite);
				}
			}
			else if (
				characters[b].sprite.getPosition().y > roomObjects[a]->getCollisionRect().top &&
				characters[b].sprite.getPosition().y <= roomObjects[a + 1]->getCollisionRect().top
				) {
				window->draw(characters[b].sprite);
			}
		}
	}
}

void RoomObjects::add(sf::IntRect textureRect, int bottomWidth) {
	roomObjects.push_back(new RoomObject(textureRect, bottomWidth));
}
void RoomObjects::add(RoomObject* roomObject) {
	roomObjects.push_back(roomObject);
}

std::vector<sf::FloatRect> RoomObjects::getCollisionRects() {
	std::vector<sf::FloatRect> collisionRects;
	collisionRects.reserve(roomObjects.size());
	for (int a = 0; a < (int)roomObjects.size(); a++) {
		collisionRects.push_back(roomObjects[a]->getCollisionRect());
	}
	return collisionRects;
}
unsigned int RoomObjects::getNumberOfRoomObjects() {
	return roomObjects.size();
}

RoomObject& RoomObjects::operator[](unsigned int index) {
	return *roomObjects[index];
}