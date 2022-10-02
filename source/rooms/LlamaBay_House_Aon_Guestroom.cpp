#include "LlamaBay_House_Aon_Guestroom.hpp"
#include "LlamaBay_House_Aon_Livingroom.hpp"
#include <fstream>

void LlamaBay_House_Aon_Guestroom::initialize() {
	sprite_bedSheet.setTexture(*texture);
	sprite_bedSheet.setTextureRect(TextureRects::object_house_aon_guestroom_bed_overlay);
	sprite_bedSheet.setPosition(124, 74);

	text.setFont(font);
	text.setCharacterSize(35 * 8);
	text.setScale(0.035f, 0.035f);
	text.setString("The next day, in Llama bay...");
	text.setPosition((GAME_SIZE.x - text.getGlobalBounds().width) * 0.5f, (GAME_SIZE.y - text.getGlobalBounds().height) * 0.5f);

	sprite_leftButton.setTexture(*texture);
	sprite_leftButton.setTextureRect(TextureRects::UI_button_left);
	sprite_leftButton.setPosition(GAME_SIZE.x * 0.5f, 155);
	sprite_leftButton.setColor(sf::Color::Transparent);

	//-------------------------------------------------------------

	if (Game::string_lastRoom == "LlamaBay_House_Aon_Livingroom") {
		Game::player->sprite.setTextureRect(TextureRects::character_flynn_overworld_down);
		Game::player->setPosition(89.0f, 85.0f);

		text.setFillColor(sf::Color::Transparent);
		sprite_bedSheet.setColor(sf::Color::Transparent);

		state = 1;
	}
	else {
		Game::player->sprite.setTextureRect(TextureRects::character_flynn_overworld_snoring_0);
		Game::player->setPosition(400.0f, 190.0f);

		music->stop();
	}

	Game::dialogBox->setCharacter(Game::narrator.get());
	Game::dialogBox->setIsVisible(false);

	//-------------------------------------------------------------

	collisionRect_desk = sf::FloatRect(0, 0, 59, 104);
	collisionRect_bed = sf::FloatRect(124, 0, 200, 114);

	loadScene(nlohmann::json::parse(std::ifstream{resource_paths::json::llamabay_house_aon_guestroom}));
}
void LlamaBay_House_Aon_Guestroom::update() {
	Game::player->sprite.setOrigin(0, Game::player->sprite.getGlobalBounds().height);

	// Show text in beginning
	if (state == 0) {
		if (frameCount > 230) {
			text.setFillColor(sf::Color(255, 255, 255, 0));
			state = 2;
			sprite_bedSheet.setColor(sf::Color::White);
		}
	}

	// Fade in
	else if (state == 1) {
		fadeIn();
		if (getBlackOpacity() == 0) {
			state++;
			state = 4;
		}
	}

	// Sleeping
	else if (state == 2) {
		if (Game::string_lastRoom == "LlamaBay_House_Aon_Livingroom") {
			music->setVolume((float)animateInt((int)music->getVolume(), 0, 2));
		}
		setBlackOpacity(animateInt(getBlackOpacity(), 50, 2));

		//-------------------------------------------------------------

		Game::player->setPosition(131, 62 + Game::player->sprite.getGlobalBounds().height);
		Game::player->sprite.setTextureRect(animateTextureRect({
				TextureRects::character_flynn_overworld_snoring_0,
				TextureRects::character_flynn_overworld_snoring_1
			}, Game::player->sprite.getTextureRect(), 80
		));

		sprite_leftButton.setColor(sf::Color::White);
		sprite_leftButton.setOrigin(sprite_leftButton.getGlobalBounds().width / 2, sprite_leftButton.getGlobalBounds().height);
		sprite_leftButton.setTextureRect(animateTextureRect({
				TextureRects::UI_button_left,
				TextureRects::UI_button_left_pressed
			}, sprite_leftButton.getTextureRect(), 40
		));

		if (Events::pressedKey == sf::Keyboard::Left) {
			sprite_leftButton.setTextureRect(TextureRects::UI_button_left_pressed);
			state++;
		}
	}

	// Get out of bed
	else if (state == 3) {
		fadeIn();

		sprite_leftButton.setColor(sf::Color(255, 255, 255, animateInt((int)sprite_leftButton.getColor().a, 0, 5)));

		Game::player->animations["walk_left_outOfBed"].update();

		switch (Game::player->animations["walk_left_outOfBed"].getCurrentTextureRectIndex()) {
		case 1:
			Game::player->setPosition(126, 62 + Game::player->sprite.getGlobalBounds().height);
			break;
		case 2:
			sprite_bedSheet.setColor(sf::Color::Transparent);
			Game::player->setPosition(118, 63 + Game::player->sprite.getGlobalBounds().height);
			break;
		case 3:
			Game::player->setPosition(105, 70 + Game::player->sprite.getGlobalBounds().height);
			Game::player->animations["walk_left_outOfBed"].reset();
			state++;
			break;
		}
	}

	// Free movement
	if (state == 4) {
		if (Game::string_lastRoom == "LlamaBay_House_Aon_Livingroom") {
			music->setVolume((float)animateInt((int)music->getVolume(), 100, 2));
		}
		if (!Game::dialogBox->getIsVisible()) {
			Game::player->updateMovement(this);
		}

		Game::dialogBox->update();

		if (Events::wasContinueKeyPressed) {
			if (Game::dialogBox->getIsVisible() && Game::dialogBox->getHasTalked()) {
				Game::dialogBox->setIsVisible(false);
				Game::dialogBox->setString("");
			}
			else {
				if (Game::player->getWillOpenInfoDialogBox(collisionRect_bed, Game::player->Right)) {
					Game::player->sprite.setTextureRect(TextureRects::character_flynn_overworld_snoring_0);
					state = 2;
					sprite_bedSheet.setColor(sf::Color::White);
				}
				else if (Game::player->getWillOpenInfoDialogBox(collisionRect_desk, Game::player->Left)) {
					Game::dialogBox->setString("You found some notes.\nIt seems to be some homework covered with dog doodles.");
					Game::dialogBox->setIsVisible(true);
				}
				else if (Game::player->getWillOpenInfoDialogBox(sf::FloatRect(0, 0, 83, 77), Game::player->Up)) {
					Game::dialogBox->setString("They're posters from some old movies. You want to see them.");
					Game::dialogBox->setIsVisible(true);
				}
			}
		}

		if (Game::player->getWillOpenDoor(sf::FloatRect(91, 0, 12, 80), Game::player->Up)) {
			state++;
		}
	}

	// fade out to livingroom
	else if (state == 5) {
		fadeOut();
		if (getBlackOpacity() == 100) {
			Game::setRoom(new LlamaBay_House_Aon_Livingroom());
			return;
		}
	}
}
void LlamaBay_House_Aon_Guestroom::draw() {
	drawScene();
	window->draw(sprite_bedSheet);
	window->draw(sprite_leftButton);
	Game::dialogBox->draw();
	window->draw(blackRectangle);
	window->draw(text);
}

std::string LlamaBay_House_Aon_Guestroom::getName() {
	return "LlamaBay_House_Aon_Guestroom";
}