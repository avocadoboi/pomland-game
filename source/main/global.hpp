#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

#include <json.hpp>

#include "../resource/resources.hpp"

//
// Global constants
//

inline auto const GAME_SIZE = sf::Vector2f{195, 162};
inline auto const WINDOW_SIZE = sf::Vector2f{585, 486};

//-------------------------------------------------------------

inline auto const TILESET_SIZE = sf::Vector2f{9, 7};
inline auto const TILESET_SPACING = 1;
inline auto const TILESET_MARGIN = 1;
inline auto const TILE_WIDTH = 33;

//-------------------------------------------------------------

inline auto const COLOR_GOLD_YELLOW = sf::Color{227, 185, 0};
inline auto const COLOR_GOLD_YELLOW_DARK = sf::Color{static_cast<sf::Uint8>(227*0.7), static_cast<sf::Uint8>(185*0.7), 0};
inline auto const COLOR_GRAY = sf::Color{186, 186, 186};
inline auto const COLOR_FULLGRAY = sf::Color{128, 128, 128};

//-------------------------------------------------------------

inline auto const CHARACTER_TALK_ANIMATION_FREQUENCY = 10;
inline auto const CHARACTER_TALK_SOUND_FREQUENCY = 2;
inline auto const CHARACTER_TALK_TEXT_FREQUENCY = 1;

//-------------------------------------------------------------

inline auto const PLAYER_FOOT_LENGTH = 4;
inline auto const PLAYER_WALK_SPEED_NORMAL = 1;
inline auto const PLAYER_WALK_SPEED_FAST = 2;
inline auto const PLAYER_NUMBER_OF_COLLISION_ITERATIONS = 5;
inline auto const PLAYER_MIN_ANIMATED_VELOCITY = 0.03;

//-------------------------------------------------------------

inline auto const ROOM_FADE_SPEED = 15;

//
// Global variables
//

inline std::unique_ptr<sf::RenderWindow> window;
inline sf::View view;
inline sf::Vector2f viewCenter;

inline std::unique_ptr<sf::Texture> texture;
inline std::unique_ptr<sf::Texture> texture_tileset;
inline sf::Image icon;
inline sf::Font font;
inline sf::RectangleShape blackRectangle;
inline std::unique_ptr<sf::Music> music;

inline long long frameCount;

//
// Global functions
//

template<typename A, typename B>
float getVector2DistanceSquared(const sf::Vector2<A>& p_vector_0, const sf::Vector2<B>& p_vector_1) {
	return (p_vector_1.x - p_vector_0.x)*(p_vector_1.x - p_vector_0.x) + (p_vector_1.y - p_vector_0.y)*(p_vector_1.y - p_vector_0.y);
}
template<typename A, typename B>
float getVector2Distance(const sf::Vector2<A>& p_vector_0, const sf::Vector2<B>& p_vector_1) {
	return sqrt((p_vector_1.x - p_vector_0.x)*(p_vector_1.x - p_vector_0.x) + (p_vector_1.y - p_vector_0.y)*(p_vector_1.y - p_vector_0.y));
}

template<typename A>
float getVector2LengthSquared(const sf::Vector2<A>& p_vector) {
	return p_vector.x*p_vector.x + p_vector.y*p_vector.y;
}
template<typename A>
float getVector2Length(const sf::Vector2<A>& p_vector) {
	return sqrt(p_vector.x*p_vector.x + p_vector.y*p_vector.y);
}

template<typename A>
sf::Vector2<A> getVector2Normalized(const sf::Vector2<A>& p_vector) {
	float length = sqrt(p_vector.x*p_vector.x + p_vector.y*p_vector.y);
	return sf::Vector2<A>(p_vector.x / length, p_vector.y / length);
}

template<typename A>
void rotateVector2(sf::Vector2<A>& p_vector, float p_angle) {
	A xBefore = p_vector.x;
	p_vector.x = xBefore*cos(p_angle) - p_vector.y*sin(p_angle);
	p_vector.y = xBefore*sin(p_angle) + p_vector.y*cos(p_angle);
}
template<typename A, typename B>
void rotateVector2(sf::Vector2<A>& p_vector, const sf::Vector2<B>& p_origin, float p_angle) {
	p_vector -= p_origin;
	A xBefore = p_vector.x;
	p_vector.x = p_origin.x + xBefore * cos(p_angle) - p_vector.y*sin(p_angle);
	p_vector.y = p_origin.y + xBefore * sin(p_angle) + p_vector.y*cos(p_angle);
}

template<typename A>
float getVector2Rotation(const sf::Vector2<A>& p_vector) {
	return atan2(p_vector.y, p_vector.x);
}
template<typename A, typename B>
float getVector2Rotation(const sf::Vector2<A>& p_vector, const sf::Vector2<B>& p_origin) {
	return atan2(p_vector.y - p_origin.y, p_vector.x - p_origin.x);
}

template<typename A>
sf::Vector2<A> getVector2Rotated90Degrees(const sf::Vector2<A>& p_vector, bool p_isClockwise) {
	if (p_isClockwise) {
		return sf::Vector2<A>(-p_vector.y, p_vector.x);
	}
	return sf::Vector2<A>(p_vector.y, -p_vector.x);
}

template<typename A, typename B>
float getVector2DotProduct(const sf::Vector2<A>& p_vector_0, const sf::Vector2<B>& p_vector_1) {
	return p_vector_0.x*p_vector_1.x + p_vector_0.y*p_vector_1.y;
}

//-------------------------------------------------------------

inline void printMousePosition() {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		std::cout << (int)round(window->mapPixelToCoords(sf::Mouse::getPosition(*window)).x) << ", " << (int)round(window->mapPixelToCoords(sf::Mouse::getPosition(*window)).y) << '\n';
	}
}

//-------------------------------------------------------------

inline void moveViewToX(float p_target) {
	viewCenter.x += (p_target - viewCenter.x)*0.1f;
}
inline void moveViewToY(float p_target) {
	viewCenter.y += (p_target - viewCenter.y)*0.1f;
}

//-------------------------------------------------------------

inline sf::IntRect animateTextureRect(std::vector<sf::IntRect> const& p_textureRects, int& p_currentIndex, int const p_rate) {
	if (frameCount % p_rate == 0) {
		if (p_currentIndex >= (int)p_textureRects.size() - 1) {
			p_currentIndex = 0;
		}
		else {
			p_currentIndex++;
		}
	}
	return p_textureRects[p_currentIndex];
}
inline sf::IntRect animateTextureRect(std::vector<sf::IntRect> const& p_textureRects, sf::IntRect const& p_current, int const p_rate) {
	if (frameCount % p_rate == 0) {
		if (p_current == p_textureRects[p_textureRects.size() - 1]) {
			return p_textureRects[0];
		}
		else {
			for (int c = 0; c < (int)p_textureRects.size(); c++) {
				if (p_textureRects[c] == p_current) {
					return p_textureRects[c + 1];
				}
			}
			return p_textureRects[0];
		}
	}
	return p_current;
}

inline sf::Vector2f animatePosition(const sf::Vector2f& p_current, const sf::Vector2f& p_target, float p_amount) {
	if (p_current == p_target) return p_current;
	float distance = getVector2Distance(p_target, p_current);
	sf::Vector2f result(p_current.x + (((p_target.x - p_current.x)/distance)*p_amount), p_current.y + (((p_target.y - p_current.y)/distance)*p_amount));
	if ((p_current.x > p_target.x && result.x < p_target.x)
	 || (p_current.x < p_target.x && result.x > p_target.x)
	 || (p_current.y > p_target.y && result.y < p_target.y)
	 || (p_current.y < p_target.y && result.y > p_target.y))
		result = p_target;
	return result;
}
inline int animateInt(int const current, int const target, int const amount) {
	int result = current;
	if (result < target) {
		result += amount;
		if (result > target) {
			result = target;
		}
	}
	else if (result > target) {
		result -= amount;
		if (result < target) {
			result = target;
		}
	}
	return result;
}

//-------------------------------------------------------------

inline void insertBreaksInText(sf::Text& p_text, int width) {
	std::string textString = p_text.getString();
	float left = p_text.getPosition().x;
	int lastSpaceIndex = -1;

	for (int a = 0; a < (int)textString.size(); a++) {
		if (textString[a] == ' ') {
			lastSpaceIndex = a;
		}
		if (lastSpaceIndex != -1 && p_text.findCharacterPos(a).x > left + (float)width) {
			textString[lastSpaceIndex] = '\n';

			while (a < (int)textString.size()-1 && textString[a + 1] != ' ') a++;
		}
		p_text.setString(textString);
	}
}

inline sf::FloatRect getFloatRect(float p_left, float p_top, float p_right, float p_bottom) {
	return sf::FloatRect{p_left, p_top, p_right - p_left, p_bottom - p_top};
}
inline sf::Vector2u getPositionFromIndex(const sf::Vector2u& p_size, unsigned int p_index) {
	return sf::Vector2u{p_index % p_size.x, (unsigned int)floor((float)p_index / (float)p_size.x)};
}

//-------------------------------------------------------------

template<class A>
int getSign(A const p_value) {
	return (p_value > 0) - (p_value < 0);
}
constexpr float getDividedSafely(float const p_dividend, float const p_divisor) {
	if (p_divisor == 0.f) {
		return p_dividend;
	}
	return p_dividend / p_divisor;
}

//-------------------------------------------------------------

inline bool getIsEndOfStringEqualTo(const std::string& p_string_0, const std::string& p_string_1) {
	return p_string_0.substr(p_string_0.size() - p_string_1.size(), p_string_1.size()) == p_string_1;
}
template<class A, class B>
bool getHasVectorOnly(const std::vector<A>& p_vector, const B& p_value) {
	for (int c = 0; c < p_vector.size(); c++) {
		if (p_vector[c] != p_value) {
			return false;
		}
	}
	return true;
}

//-------------------------------------------------------------

inline void setBlackOpacity(int p_opacity) {
	blackRectangle.setFillColor(sf::Color(0, 0, 0, (sf::Uint8)round(255.f*p_opacity/100.f)));
}
inline int getBlackOpacity() {
	return (int)round(blackRectangle.getFillColor().a*100.f/255.f);
}

inline void fadeIn() {
	blackRectangle.setFillColor(sf::Color(0, 0, 0, animateInt((int)blackRectangle.getFillColor().a, 0, ROOM_FADE_SPEED)));
}
inline void fadeIn(unsigned int p_speed) {
	blackRectangle.setFillColor(sf::Color(0, 0, 0, animateInt((int)blackRectangle.getFillColor().a, 0, p_speed)));
}
inline void fadeOut() {
	blackRectangle.setFillColor(sf::Color(0, 0, 0, animateInt((int)blackRectangle.getFillColor().a, 255, ROOM_FADE_SPEED)));
}
inline void fadeOut(unsigned int p_speed) {
	blackRectangle.setFillColor(sf::Color(0, 0, 0, animateInt((int)blackRectangle.getFillColor().a, 255, p_speed)));
}
