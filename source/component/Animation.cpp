#include "Animation.hpp"

//
// Public
//

Animation::Animation(sf::Sprite &p_sprite) {
	sprite = &p_sprite;
	startPosition = sprite->getPosition();
}

void Animation::operator=(Animation& animation){
	// todo: overload assignment operator for animation
}

//-------------------------------------------------------------

void Animation::update() {
	if (sprite != nullptr) {
		if (textureRects.size() > 1) {
			sprite->setTextureRect(animateTextureRect(textureRects, currentTextureRectIndex, textureRectAnimationRate));
		}
		if (isPositionAnimationEnabled) {
			sprite->setPosition(animatePosition(sprite->getPosition(), destinationPosition, (float)positionAnimationSpeed));
		}
		sprite->move(velocity);
	}
}
void Animation::reset(){
	currentTextureRectIndex = 0;
	if (isPositionAnimationEnabled) sprite->setPosition(startPosition);
}

//-------------------------------------------------------------

void Animation::setSprite(sf::Sprite &p_sprite){
	sprite = &p_sprite;
}
void Animation::setSprite(sf::Sprite* p_sprite){
	sprite = p_sprite;
}
sf::Sprite* Animation::getSprite(){
	return sprite;
}

void Animation::setTextureRects(std::vector<sf::IntRect> p_textureRects) {
	textureRects = p_textureRects;
}
void Animation::setTextureRectAnimationFrequency(int rate){
	textureRectAnimationRate = rate;
}

int Animation::getNumberOfTextureRects() {
	return textureRects.size();
}
void Animation::setCurrentTextureRectIndex(int index){
	currentTextureRectIndex = index;
}
int Animation::getCurrentTextureRectIndex() {
	return currentTextureRectIndex;
}
sf::IntRect Animation::getTextureRect(unsigned int index){
	return textureRects[index];
}

//-------------------------------------------------------------

void Animation::setDestinationPosition(sf::Vector2f p_destinationPosition) {
	destinationPosition = p_destinationPosition;
	startPosition = sprite->getPosition();
}
void Animation::setPositionAnimationSpeed(int speed){
	positionAnimationSpeed = speed;
}
void Animation::setVelocity(sf::Vector2f p_velocity){
	velocity = p_velocity;
}
void Animation::setIsPositionAnimationEnabled(bool p_isPositionAnimationEnabled){
	isPositionAnimationEnabled = p_isPositionAnimationEnabled;
}