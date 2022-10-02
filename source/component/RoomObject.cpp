#include "RoomObject.hpp"

//
// Public
//

RoomObject::RoomObject() {
	sprite.setTexture(*texture);
}
RoomObject::RoomObject(sf::IntRect p_textureRect, unsigned int p_bottomWidth) {
	sprite.setTexture(*texture);
	sprite.setTextureRect(p_textureRect);
	sprite.setOrigin(0.f, (float)p_textureRect.height);
	bottomWidth = p_bottomWidth;
}

void RoomObject::draw() {
	window->draw(sprite);
}

void RoomObject::setTextureRect(sf::IntRect rect) {
	sprite.setTextureRect(rect);
	sprite.setOrigin(0, sprite.getGlobalBounds().height);
}
sf::IntRect RoomObject::getTextureRect() const {
	return sprite.getTextureRect();
}

void RoomObject::setPosition(sf::Vector2f position) {
	sprite.setPosition(position);
}
void RoomObject::setPosition(float x, float y) {
	sprite.setPosition(x, y);
}

void RoomObject::setOrigin(sf::Vector2f origin) {
	sprite.setOrigin(origin);
}
void RoomObject::setOrigin(float x, float y) {
	sprite.setOrigin(x, y);
}
sf::Vector2f RoomObject::getOrigin() const {
	return sprite.getOrigin();
}

void RoomObject::setBottomWidth(unsigned int p_bottomWidth) {
	bottomWidth = p_bottomWidth;
}
sf::FloatRect RoomObject::getCollisionRect() const {
	return sf::FloatRect{
		sprite.getGlobalBounds().left,
		sprite.getPosition().y - static_cast<float>(bottomWidth),
		sprite.getGlobalBounds().width,
		static_cast<float>(bottomWidth)
	};
}