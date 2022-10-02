#include "GameButton.hpp"

//
// Public
//

GameButton::GameButton() {}
GameButton::GameButton(std::string buttonString) {
	text.setFont(font);
	text.setString(buttonString);
	text.setCharacterSize(static_cast<unsigned int>(characterSize * 8));
	text.setScale(0.035f, 0.035f);
	text.setFillColor(COLOR_GOLD_YELLOW_DARK);

	type = Text;
}
GameButton::GameButton(sf::Vector2f size) {
	rect.setSize(size);
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineThickness(1);
	rect.setOutlineColor(COLOR_GOLD_YELLOW_DARK);

	type = Rectangle;
}

void GameButton::update(std::vector<std::unique_ptr<GameButton>>& p_buttons) {
	if (Events::pressedKey == sf::Keyboard::Left || Events::pressedKey == sf::Keyboard::Right || Events::pressedKey == sf::Keyboard::Up || Events::pressedKey == sf::Keyboard::Down) {
		for (std::size_t a{}; a < p_buttons.size(); ++a) {
			if (p_buttons[a]->getIsSelected()) {
				auto recordIndex = static_cast<std::size_t>(-1);
				for (std::size_t b{}; b < p_buttons.size(); ++b) {
					if (Events::pressedKey == sf::Keyboard::Left) {
						if (p_buttons[b]->getPosition().x + p_buttons[b]->getGlobalBounds().width < p_buttons[a]->getPosition().x) {
							if (recordIndex == static_cast<std::size_t>(-1)) {
								recordIndex = b;
							}
							else if (
								std::abs(p_buttons[b]->getPosition().y - p_buttons[a]->getPosition().y) + std::abs(p_buttons[b]->getPosition().x + p_buttons[b]->getGlobalBounds().width - p_buttons[a]->getPosition().x) <=
								std::abs(p_buttons[recordIndex]->getPosition().y - p_buttons[a]->getPosition().y) + std::abs(p_buttons[recordIndex]->getPosition().x + p_buttons[recordIndex]->getGlobalBounds().width - p_buttons[a]->getPosition().x)
								) {
								recordIndex = b;
							}
						}
					}
					else if (Events::pressedKey == sf::Keyboard::Right) {
						if (p_buttons[b]->getPosition().x > p_buttons[a]->getPosition().x + p_buttons[a]->getGlobalBounds().width) {
							if (recordIndex == static_cast<std::size_t>(-1)) {
								recordIndex = b;
							}
							else if (
								std::abs(p_buttons[b]->getPosition().y - p_buttons[a]->getPosition().y) + std::abs(p_buttons[b]->getPosition().x - p_buttons[a]->getPosition().x - p_buttons[a]->getGlobalBounds().width) <=
								std::abs(p_buttons[recordIndex]->getPosition().y - p_buttons[a]->getPosition().y) + std::abs(p_buttons[recordIndex]->getPosition().x - p_buttons[a]->getPosition().x - p_buttons[a]->getGlobalBounds().width)
								) {
								recordIndex = b;
							}
						}
					}
					else if (Events::pressedKey == sf::Keyboard::Up) {
						if (p_buttons[b]->getPosition().y < p_buttons[a]->getPosition().y) {
							if (recordIndex == static_cast<std::size_t>(-1)) {
								recordIndex = b;
							}
							else if (
								std::abs(p_buttons[b]->getPosition().x - p_buttons[a]->getPosition().x) + std::abs(p_buttons[b]->getPosition().y - p_buttons[a]->getPosition().y) <=
								std::abs(p_buttons[recordIndex]->getPosition().x - p_buttons[a]->getPosition().x) + std::abs(p_buttons[recordIndex]->getPosition().y - p_buttons[a]->getPosition().y)
								) {
								recordIndex = b;
							}
						}
					}
					else if (Events::pressedKey == sf::Keyboard::Down) {
						if (p_buttons[b]->getPosition().y > p_buttons[a]->getPosition().y) {
							if (recordIndex == static_cast<std::size_t>(-1)) {
								recordIndex = b;
							}
							else if (
								std::abs(p_buttons[b]->getPosition().x - p_buttons[a]->getPosition().x) + std::abs(p_buttons[b]->getPosition().y - p_buttons[a]->getPosition().y) <=
								std::abs(p_buttons[recordIndex]->getPosition().x - p_buttons[a]->getPosition().x) + std::abs(p_buttons[recordIndex]->getPosition().y - p_buttons[a]->getPosition().y)
								) {
								recordIndex = b;
							}
						}
					}
				}
				if (recordIndex == static_cast<std::size_t>(-1)) return;
				p_buttons[a]->setIsSelected(false);
				p_buttons[recordIndex]->setIsSelected(true);
				return;
			}
		}
	}
}
void GameButton::draw(std::vector<std::unique_ptr<GameButton>>& buttons) {
	for (int a = 0; a < (int)buttons.size(); a++) buttons[a]->draw();
}

void GameButton::draw() {
	if (type == Type::Text) {
		window->draw(text);
	}
	else {
		window->draw(rect);
	}
}

void GameButton::setString(std::string p_string) {
	text.setString(p_string);
}
std::string GameButton::getString() {
	return text.getString();
}

void GameButton::setSize(int p_characterSize) {
	characterSize = p_characterSize;
	text.setCharacterSize(characterSize * 8);
}
void GameButton::setSize(float x, float y) {
	rect.setSize(sf::Vector2f(x, y));
}

void GameButton::setPosition(sf::Vector2f position) {
	(type == Type::Text) ? text.setPosition(position - origin) : rect.setPosition(position - origin);
}
void GameButton::setPosition(float p_x, float p_y) {
	setPosition(sf::Vector2f(p_x, p_y));
}
sf::Vector2f GameButton::getPosition() {
	return (type == Type::Text) ? text.getPosition() + origin : rect.getPosition() + origin;
}

void GameButton::setOrigin(sf::Vector2f p_pos) {
	origin = p_pos;
}
void GameButton::setOrigin(float p_x, float p_y) {
	setOrigin(sf::Vector2f(p_x, p_y));
}

void GameButton::setIsSelected(bool p_selected) {
	isSelected = p_selected;
	if (type == Type::Text) {
		text.setFillColor(isSelected ? color_selected : color_notSelected);
	}
	else {
		rect.setOutlineColor(isSelected ? color_selected : color_notSelected);
	}
}
bool GameButton::getIsSelected() {
	return isSelected;
}

void GameButton::setColors(sf::Color p_color_selected, sf::Color p_color_notSelected) {
	color_selected = p_color_selected;
	color_notSelected = p_color_notSelected;
	setIsSelected(isSelected);
}
sf::FloatRect GameButton::getGlobalBounds() {
	return (type == Type::Text) ? text.getGlobalBounds() : rect.getGlobalBounds();
}