#include "Intro_1.hpp"
#include "LlamaBay_House_Aon_Guestroom.hpp"

void Intro_1::initialize() {
	sprite_background.setTexture(*texture);
	sprite_background.setTextureRect(TextureRects::room_beach_0);
	sprite_background.setPosition(0, 0);

	//-------------------------------------------------------------

	Game::aon->sprite.setTextureRect(TextureRects::character_aon_overworld_left);
	Game::aon->sprite.setPosition(GAME_SIZE.x, 114);
	Game::aon->animation_closeup = &Game::aon->animations["closeup_sad"];

	Game::dialogBox->setCharacter(Game::aon.get());
	Game::dialogBox->setIsVisible(false);

	Game::player->sprite.setTextureRect(TextureRects::character_flynn_overworld_lying);
	Game::player->setPosition(70, 100);

	//-------------------------------------------------------------

	music->openFromFile(resource_paths::music::beach_background_sound);
	music->play();
}
void Intro_1::update() {
	sprite_background.setTextureRect(animateTextureRect({ TextureRects::room_beach_0, TextureRects::room_beach_1 }, sprite_background.getTextureRect(), 30));

	if (state == 0) {
		fadeIn(2);

		if (frameCount > 60 * 2) state++;
	}
	else if (state == 1) {
		if (frameCount % 2 == 0) Game::aon->sprite.move(-1, 0);
		Game::aon->animations["walk_left_worried"].update();

		if (Game::aon->sprite.getPosition().x == 100) {
			Game::aon->sprite.setTextureRect(TextureRects::character_aon_overworld_left_worried);
			state++;
		}
	}
	else if (state == 2) {
		Game::aon->sprite.setTextureRect(animateTextureRect(
			{
				TextureRects::character_aon_overworld_left_worried,
				TextureRects::character_aon_overworld_onLegs_left_0,
				TextureRects::character_aon_overworld_onLegs_left_1,
				TextureRects::character_aon_overworld_onLegs_left
			}, 
			Game::aon->sprite.getTextureRect(), 30
		));

		if (Game::aon->sprite.getTextureRect() == TextureRects::character_aon_overworld_onLegs_left) {
			Game::dialogBox->setIsVisible(true);
			Game::dialogBox->setString("What's this...");
			state++;
		}
	}
	else if (state == 3) {
		Game::dialogBox->update();

		if (Events::wasContinueKeyPressed && Game::dialogBox->getHasTalked()) {
			switch (Game::dialogBox->counter) {
			case 1:
				Game::dialogBox->setString("Hello? Are you alive?");
				break;

			case 2:
				Game::aon->animation_closeup = &Game::aon->animations["closeup_huh"];
				Game::dialogBox->setString("Hm.");
				break;

			case 3:
				Game::dialogBox->setString("I'll just carry it home and \nsee if it wakes up...");
				break;

			case 4:
				state++;
				break;
			}
		}
		else if (!Game::dialogBox->getHasTalked()) {
			Game::aon->sprite.setTextureRect(animateTextureRect(
				{
					TextureRects::character_aon_overworld_onLegs_left,
					TextureRects::character_aon_overworld_onLegs_left_talking
				},
				Game::aon->sprite.getTextureRect(), CHARACTER_TALK_ANIMATION_FREQUENCY
			));
		}
		else if (Game::dialogBox->getHasTalked()) {
			Game::aon->sprite.setTextureRect(TextureRects::character_aon_overworld_onLegs_left);
		}
	}
	else if (state == 4) {
		fadeOut();
		if (getBlackOpacity() == 100) {
			Game::setRoom(new LlamaBay_House_Aon_Guestroom());
			return;
		}
	}

	Game::aon->sprite.setOrigin(0, Game::aon->sprite.getGlobalBounds().height);
}
void Intro_1::draw() {
	window->draw(sprite_background);
	window->draw(Game::player->sprite);
	window->draw(Game::aon->sprite);
	Game::dialogBox->draw();
	window->draw(blackRectangle);
}

std::string Intro_1::getName() {
	return "Intro_1";
}