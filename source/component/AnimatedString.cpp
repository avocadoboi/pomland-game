#include "AnimatedString.hpp"

//
// Public
//

AnimatedString::AnimatedString(){}
AnimatedString::AnimatedString(std::string p_string) : targetString(p_string) {}

//-------------------------------------------------------------

void AnimatedString::set(std::string p_string) {
	targetString = p_string;
	currentString = "";
}
std::string AnimatedString::get() {
	return currentString;
}
std::string AnimatedString::getTarget() {
	return targetString;
}

//-------------------------------------------------------------

bool AnimatedString::update() {
	if (updateCount >= currentDelay && currentString.size() < targetString.size()) {
		currentString.push_back(targetString[currentString.size()]);
		switch (currentString[currentString.size() - 1]) {
		case ',':
		case ';':
		case ':':
			currentDelay = speed + 8;
			break;
		case '.':
		case '!':
		case '?':
			currentDelay = speed + 20;
			break;
		default:
			currentDelay = speed;
		}
		updateCount = 0;
		return true;
	}
	updateCount++;
	return false;
}
bool AnimatedString::getIsAnimationDone() {
	return targetString == currentString;
}

void AnimatedString::complete() {
	currentString = targetString;
}
void AnimatedString::reset() {
	currentString = "";
}

//-------------------------------------------------------------

void AnimatedString::setSpeed(unsigned int p_speed) {
	speed = p_speed;
}