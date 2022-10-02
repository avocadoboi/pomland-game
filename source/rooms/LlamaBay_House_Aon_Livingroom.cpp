#include "LlamaBay_House_Aon_Livingroom.hpp"
#include "LlamaBay_House_Aon_Guestroom.hpp"
#include "LlamaBay_House_Aon_Hallway.hpp"
#include <fstream>

void LlamaBay_House_Aon_Livingroom::initialize() {
	loadScene(nlohmann::json::parse(std::ifstream{resource_paths::json::llamabay_house_aon_livingroom}));

	//-------------------------------------------------------------

	roomObjects.add(TextureRects::object_house_aon_livingroom_granpaClock_0, 28);
	roomObjects[0].setPosition(215, 74);
	roomObjects.add(TextureRects::object_house_aon_livingroom_couch, 3);
	roomObjects[1].setPosition(80, 90);
	roomObjects.add(TextureRects::object_house_aon_livingroom_table, 3);
	roomObjects[2].setPosition(47, 100);
	roomObjects.add(TextureRects::object_house_aon_livingroom_wall, 0);
	roomObjects[3].setPosition(269, 104);
	roomObjects[3].setOrigin(0, 65);

	//-------------------------------------------------------------

	if (Game::string_lastRoom == "LlamaBay_House_Aon_Hallway") {
		Game::player->sprite.setTextureRect(TextureRects::character_flynn_overworld_left);
		Game::player->setPosition(251, 96);
	}
	else {
		Game::player->sprite.setTextureRect(TextureRects::character_flynn_overworld_up);
		Game::player->setPosition(80, 155);
	}

	//-------------------------------------------------------------

	if (Game::player->data.hasMetAon) {
		Game::aon->sprite.setColor(sf::Color::Transparent);

		Game::dialogBox->setCharacter(Game::narrator.get());
		Game::dialogBox->setIsVisible(false);

		Game::player->centerViewX(this);

		state = 10;
	}
	else {
		Game::aon->sprite.setTextureRect(TextureRects::character_aon_overworld_newspaper_0);
		Game::aon->sprite.setPosition(88, 95);

		Game::dialogBox->setCharacter(Game::aon.get());
		Game::dialogBox->setString("Ah, good morning!");
		Game::dialogBox->setIsVisible(false);
		Game::aon->animation_closeup = &Game::aon->animations["closeup_happy"];
		
		music->openFromFile(resource_paths::music::aon);
	}
}
void LlamaBay_House_Aon_Livingroom::update() {
	switch (state) {
	// Fade in
	case 0: {
		fadeIn();
		if (getBlackOpacity() == 0 && frameCount > 70) {
			music->play();
			state++;
			Game::dialogBox->setIsVisible(true);
		}
		break;
	}
	// Aon talks
	case 1: {
		Game::dialogBox->update();
		if (Game::dialogBox->getHasTalked()) {
			Game::aon->sprite.setTextureRect(TextureRects::character_aon_overworld_newspaper_1);
		}
		else if (Game::dialogBox->getCharacter() == Game::aon.get()) {
			Game::aon->sprite.setTextureRect(animateTextureRect(
				{
					TextureRects::character_aon_overworld_newspaper_1,
					TextureRects::character_aon_overworld_newspaper_1_talking 
				},
				Game::aon->sprite.getTextureRect(), CHARACTER_TALK_ANIMATION_FREQUENCY
			));
		}
		if (Events::wasContinueKeyPressed && Game::dialogBox->getHasTalked()) {
			switch (Game::dialogBox->counter) {
			case 1:
				Game::dialogBox->setString("This might seem a bit weird...");
				Game::aon->animation_closeup = &Game::aon->animations["closeup_huh"];
				break;
			case 2:
				Game::dialogBox->setString("I found you at the beach and I thought you might wake up, so I took you home!");
				Game::aon->animation_closeup = &Game::aon->animations["closeup_happy"];
				break;
			case 3:
				Game::dialogBox->setString("But what is your name?");
				Game::aon->animation_closeup = &Game::aon->animations["closeup_huh"];
				break;
			case 4:
				Game::dialogBox->setCharacter(Game::narrator.get());
				Game::dialogBox->setString("(You don't remember anything.)");
				break;
			case 5:
				Game::dialogBox->setCharacter(Game::aon.get());
				Game::aon->animation_closeup = &Game::aon->animations["closeup_huh"];
				Game::dialogBox->setString("Oh... What about I call you  " + Game::player->getName() + "?");
				break;
			case 6:
				Game::dialogBox->setCharacter(Game::narrator.get());
				Game::dialogBox->setString("(You accept it.)");
				break;
			case 7:
				Game::dialogBox->setCharacter(Game::aon.get());
				Game::aon->animation_closeup = &Game::aon->animations["closeup_happy"];
				Game::dialogBox->setString("Cool! My name is Aon by the  way. But what's up?");
				break;
			case 8:
				Game::dialogBox->setCharacter(Game::narrator.get());
				Game::dialogBox->setString("How do you feel?");
				Game::dialogBox->setButtonStrings("Pretty swell", "Confused");
				Game::dialogBox->setAreButtonsVisible(true);
				break;
			case 9:
				Game::dialogBox->setAreButtonsVisible(false);
				Game::dialogBox->setCharacter(Game::aon.get());
				if (Game::dialogBox->getSelectedButtonIndex() == 0) {
					Game::aon->animation_closeup = &Game::aon->animations["closeup_happy"];
					Game::dialogBox->setString("That's just great!");
					Game::player->data.isConfused = false;
				}
				else {
					Game::aon->animation_closeup = &Game::aon->animations["closeup_sad"];
					Game::dialogBox->setString("Im sorry about that...");
					Game::player->data.isConfused = true;
				}
				break;
			case 10:
				Game::aon->animation_closeup = &Game::aon->animations["closeup_huh"];
				Game::dialogBox->setString("Also, when I found you, your clothing was all dirty and ruined.");
				break;
			case 11:
				Game::dialogBox->setString("So I changed them for you! Sorry, if it weirded you out, hee hee.");
				Game::aon->animation_closeup = &Game::aon->animations["closeup_heh"];
				break;
			case 12:
				Game::dialogBox->setString("But what's on your mind today?");
				Game::aon->animation_closeup = &Game::aon->animations["closeup_huh"];
				break;
			case 13:
				Game::dialogBox->setCharacter(Game::narrator.get());
				Game::dialogBox->setString("What will you say to Aon?");
				Game::dialogBox->setAreButtonsVisible(true);
				Game::dialogBox->setButtonStrings("I want to take\nit easy today.", "I want to exp-\nlore this town.");
				break;
			case 14:
				Game::dialogBox->setAreButtonsVisible(false);
				Game::dialogBox->setCharacter(Game::aon.get());
				Game::aon->animation_closeup = &Game::aon->animations["closeup_happy"];
				if (Game::dialogBox->getSelectedButtonIndex() == 0) {
					Game::dialogBox->setString("Oh, well of course! I would've done that too if I were in your situation.");
					Game::player->data.isExcited = false;
				}
				else {
					Game::dialogBox->setString("I see...");
					Game::player->data.isExcited = true;
				}
				break;
			case 15:
				if (Game::player->data.isExcited) {
					Game::dialogBox->setString("Well, first you gotta eat some breakfast, I'll go get some!");
				}
				else {
					Game::dialogBox->setString("But... I'll go and make some breakfast for us!");
				}
				break;
			case 16:
				Game::aon->sprite.setTextureRect(TextureRects::character_aon_overworld_down);
				frameCount = 0;
				state++;
				break;
			}
		}
		break;
	}
	// Wait 20 frames until aon starts walking to the right
	case 2: {
		if (frameCount > 20) {
			Game::aon->sprite.setTextureRect(TextureRects::character_aon_overworld_right);
			state++;
		}
		break;
	}
	// Aon walks to the right for breakfast
	case 3: {
		Game::aon->animations["walk_right"].update();
		if (Game::aon->sprite.getPosition().x == 300) {
			Game::aon->sprite.setPosition(300, 115);
			state++;
		}
		break;
	}
	// Aon walks to the left
	case 4: {
		Game::aon->animations["walk_left"].update();
		if (Game::aon->sprite.getPosition().x == 100) {
			Game::aon->sprite.setTextureRect(TextureRects::character_aon_overworld_down);

			Game::aon->animation_closeup = &Game::aon->animations["closeup_huh"];
			if (Game::player->data.isExcited) {
				Game::dialogBox->setString("Uhm, hehe. Seems like we don't have any chocolate bread left...");
			}
			else {
				Game::dialogBox->setString("Uhm sorry to bother you, but could you please go and buy us some chocolate bread?");
			}
			Game::dialogBox->counter = 0;
			state++;
		}
		break;
	}
	// Aon talks
	case 5: {
		Game::dialogBox->update();

		if (Game::dialogBox->getHasTalked()) {
			Game::aon->sprite.setTextureRect(TextureRects::character_aon_overworld_down);
		}
		else if (Game::dialogBox->getCharacter() == Game::aon.get()) {
			Game::aon->sprite.setTextureRect(animateTextureRect(
				{
					TextureRects::character_aon_overworld_down,
					TextureRects::character_aon_overworld_down_talking
				},
				Game::aon->sprite.getTextureRect(), CHARACTER_TALK_ANIMATION_FREQUENCY
			));
		}

		if (Game::dialogBox->getHasTalked() && Events::wasContinueKeyPressed) {
			switch (Game::dialogBox->counter) {
			case 0:
				if (Game::player->data.isExcited) {
					Game::aon->animation_closeup = &Game::aon->animations["closeup_happy"];
					Game::dialogBox->setString("But hey! You said you were gonna take a walk, right?");
				}
				else {
					Game::aon->animation_closeup = &Game::aon->animations["closeup_sad"];
					Game::dialogBox->setString("I think we used all of it yesterday when we had a chocolate bread party...");
				}
				break;
			case 1:
				if (Game::player->data.isExcited) {
					Game::dialogBox->setString("Could you go buy some choco- late bread at the store down the road while you're at it?");
				}
				else {
					Game::dialogBox->setCharacter(Game::narrator.get());
					Game::dialogBox->setString("(You accept it.)");
				}
				break;
			case 2:
				if (Game::player->data.isExcited) {
					Game::dialogBox->setCharacter(Game::narrator.get());
					Game::dialogBox->setString("(You accept it.)");
				}
				else {
					Game::dialogBox->setCharacter(Game::aon.get());
					Game::aon->animation_closeup = &Game::aon->animations["closeup_happy"];
					Game::dialogBox->setString("Thanks! The store is down the road, I'm sure you'll find it!");
				}
				break;
			case 3:
				Game::dialogBox->setCharacter(Game::aon.get());
				Game::aon->animation_closeup = &Game::aon->animations["closeup_happy"];
				if (Game::player->data.isExcited)
					Game::dialogBox->setString("Thanks! See you later.");
				else
					Game::dialogBox->setString("Well, see you later!");
				break;
			case 4:
				Game::dialogBox->setIsVisible(false);
				state++;
			}
		}
		break;
	}
	// Aon walks away
	case 6: {
		Game::aon->animations["walk_right"].update();
		if (Game::aon->sprite.getPosition().x == 250) {
			Game::aon->sprite.setColor(sf::Color::Transparent);
			Game::dialogBox->counter = 0;
			Game::dialogBox->setCharacter(Game::narrator.get());
			state++;
		}
		break;
	}
	// Free movement
	case 7: {
		roomObjects[0].setTextureRect(animateTextureRect(
			{
				TextureRects::object_house_aon_livingroom_granpaClock_0,
				TextureRects::object_house_aon_livingroom_granpaClock_1,
				TextureRects::object_house_aon_livingroom_granpaClock_0,
				TextureRects::object_house_aon_livingroom_granpaClock_2
			},
			currentGranpaClockFrame, 30
		));
		Game::dialogBox->update();
		if (!Game::dialogBox->getIsVisible()) {
			Game::player->updateMovement(this);

			if (Game::player->getWillOpenInfoDialogBox(sf::FloatRect(roomObjects[0].getCollisionRect().left - 7, roomObjects[0].getCollisionRect().top, 100, roomObjects[0].getCollisionRect().height + 5), Player::Up)) {
				Game::dialogBox->setString("An old grandfather clock. Something tells you this will probably break any time soon.");
				Game::dialogBox->setIsVisible(true);
			}
			else if (Game::player->getWillOpenInfoDialogBox(sf::FloatRect(73, 54, 49, 20), Player::Up)) {
				Game::dialogBox->setString("Those paintings are just a bunch of nonsense!");
				Game::dialogBox->setIsVisible(true);
			}
			
			if (Game::player->sprite.getPosition().y >= 160) {
				state++;
			}
			else if (Game::player->sprite.getPosition().x >= 275 && Game::player->sprite.getPosition().y < 110) {
				state = 9;
			}
		}
		else if (Events::wasContinueKeyPressed && Game::dialogBox->getHasTalked()) {
			Game::dialogBox->setIsVisible(false);
		}
		break;
	}
	// Fade out and go to guestroom
	case 8: {
		fadeOut();
		if (getBlackOpacity() == 100) {
			Game::setRoom(new LlamaBay_House_Aon_Guestroom());
			return;
		}
	}
	// Fade out and go to the hall
	case 9: {
		fadeOut();
		if (getBlackOpacity() == 100) {
			Game::setRoom(new LlamaBay_House_Aon_Hallway());
			return;
		}
		break;
	}
	// Fade in directly to free movement
	case 10: {
		fadeIn();
		if (getBlackOpacity() == 0) {
			state = 7;
		}
	}
	}
	Game::aon->sprite.setOrigin(0, Game::aon->sprite.getGlobalBounds().height);
}
void LlamaBay_House_Aon_Livingroom::draw() {
	drawScene();
	roomObjects.draw({ Game::player.get(), Game::aon.get() });
	Game::dialogBox->draw();
	window->draw(blackRectangle);
}
LlamaBay_House_Aon_Livingroom::~LlamaBay_House_Aon_Livingroom() {
	Game::aon->sprite.setColor(sf::Color::White);
	Game::player->data.hasMetAon = true;
}

std::string LlamaBay_House_Aon_Livingroom::getName() {
	return "LlamaBay_House_Aon_Livingroom";
}