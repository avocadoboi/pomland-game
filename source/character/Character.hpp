#pragma once
#include "../main/global.hpp"
#include "../component/Animation.hpp"

#include <unordered_map>

class Character {
protected:
	std::string name;

public:
	Character(){}
	Character(std::string p_name) : name(std::move(p_name)) {
		sprite.setTexture(*texture);
		sprite_closeup.setTexture(*texture);
		sprite_closeup.setTextureRect(sf::IntRect(0, 0, 0, 0));
	}
	Character(std::string p_name, std::string p_talkingSoundResource) : name(std::move(p_name)) {
		voiceBuffer.loadFromFile(std::move(p_talkingSoundResource));
		voice.setBuffer(voiceBuffer);

		sprite.setTexture(*texture);
		sprite_closeup.setTexture(*texture);
		sprite_closeup.setTextureRect(sf::IntRect(0, 0, 0, 0));
	}

	//-------------------------------------------------------------

	std::unordered_map<std::string, Animation> animations;
	Animation* animation_closeup = nullptr;

	sf::Sprite sprite_closeup;
	sf::Sprite sprite;

	sf::SoundBuffer voiceBuffer;
	sf::Sound voice;

	sf::Color color;
};