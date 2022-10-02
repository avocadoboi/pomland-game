#pragma once
#include "Character.hpp"
#include "../resource/TextureRects.hpp"

class Aon : public Character {
public:
	Aon() : Character{"Aon", resource_paths::sound::voice_aon} {
		color = sf::Color{196, 133, 77};

		animations["walk_left"].setSprite(sprite);
		animations["walk_left"].setVelocity(sf::Vector2f(-1, 0));
		animations["walk_left"].setTextureRects({
			TextureRects::character_aon_overworld_left,
			TextureRects::character_aon_overworld_left_walking_0,
			TextureRects::character_aon_overworld_left,
			TextureRects::character_aon_overworld_left_walking_1
		});
		
		animations["walk_right"].setSprite(sprite);
		animations["walk_right"].setVelocity(sf::Vector2f(1, 0));
		animations["walk_right"].setTextureRects({
			TextureRects::character_aon_overworld_right,
			TextureRects::character_aon_overworld_right_walking_0,
			TextureRects::character_aon_overworld_right,
			TextureRects::character_aon_overworld_right_walking_1
		});

		animations["walk_left_worried"].setSprite(sprite);
		animations["walk_left_worried"].setTextureRectAnimationFrequency(15);
		animations["walk_left_worried"].setTextureRects({
			TextureRects::character_aon_overworld_left_worried,
			TextureRects::character_aon_overworld_left_walking_0_worried,
			TextureRects::character_aon_overworld_left_worried,
			TextureRects::character_aon_overworld_left_walking_1_worried
		});

		animations["closeup_angry"].setSprite(sprite_closeup);
		animations["closeup_angry"].setTextureRectAnimationFrequency(CHARACTER_TALK_ANIMATION_FREQUENCY);
		animations["closeup_angry"].setTextureRects({
			TextureRects::character_aon_closeup_angry,
			TextureRects::character_aon_closeup_angry_talking
		});

		animations["closeup_happy"].setSprite(sprite_closeup);
		animations["closeup_happy"].setTextureRectAnimationFrequency(CHARACTER_TALK_ANIMATION_FREQUENCY);
		animations["closeup_happy"].setTextureRects({
			TextureRects::character_aon_closeup_happy,
			TextureRects::character_aon_closeup_happy_talking
		});

		animations["closeup_heh"].setSprite(sprite_closeup);
		animations["closeup_heh"].setTextureRectAnimationFrequency(CHARACTER_TALK_ANIMATION_FREQUENCY);
		animations["closeup_heh"].setTextureRects({
			TextureRects::character_aon_closeup_heh,
			TextureRects::character_aon_closeup_heh_talking
		});

		animations["closeup_huh"].setSprite(sprite_closeup);
		animations["closeup_huh"].setTextureRectAnimationFrequency(CHARACTER_TALK_ANIMATION_FREQUENCY);
		animations["closeup_huh"].setTextureRects({
			TextureRects::character_aon_closeup_huh,
			TextureRects::character_aon_closeup_huh_talking
		});

		animations["closeup_sad"].setSprite(sprite_closeup);
		animations["closeup_sad"].setTextureRectAnimationFrequency(CHARACTER_TALK_ANIMATION_FREQUENCY);
		animations["closeup_sad"].setTextureRects({
			TextureRects::character_aon_closeup_sad,
			TextureRects::character_aon_closeup_sad_talking
		});

		animations["closeup_suprised"].setSprite(sprite_closeup);
		animations["closeup_suprised"].setTextureRectAnimationFrequency(CHARACTER_TALK_ANIMATION_FREQUENCY);
		animations["closeup_suprised"].setTextureRects({
			TextureRects::character_aon_closeup_suprised,
			TextureRects::character_aon_closeup_suprised_talking
		});

		animations["closeup_sweat"].setSprite(sprite_closeup);
		animations["closeup_sweat"].setTextureRectAnimationFrequency(CHARACTER_TALK_ANIMATION_FREQUENCY);
		animations["closeup_sweat"].setTextureRects({
			TextureRects::character_aon_closeup_sweat,
			TextureRects::character_aon_closeup_sweat_talking
		});
	}
};