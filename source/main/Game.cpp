#include "Game.hpp"
#include "../rooms/Room.hpp"
#include "../rooms/StartMenu.hpp"

//
// Private
//

void Game::updateView() {
	sf::Vector2f windowSize = (sf::Vector2f)window->getSize();
	if (windowSize.y > windowSize.x*(GAME_SIZE.y / GAME_SIZE.x)) {
		// Width should fill window
		view.setViewport(sf::FloatRect(
			0.f, (float)(windowSize.y - (windowSize.x*(GAME_SIZE.y / GAME_SIZE.x)))*0.5f / windowSize.y,
			1.f, (float)windowSize.x*(GAME_SIZE.y / GAME_SIZE.x) / windowSize.y
		));
	}
	else {
		// Height should fill window
		view.setViewport(sf::FloatRect(
			(float)(windowSize.x - (windowSize.y*(GAME_SIZE.x / GAME_SIZE.y)))*0.5f / windowSize.x, 0.f,
			windowSize.y*((float)GAME_SIZE.x / (float)GAME_SIZE.y) / windowSize.x, 1.f
		));
	}
	initializeWindowSettings();
	window->setView(view);
}
void Game::toggleFullscreen() {
	isFullscreen = !isFullscreen;
	if (isFullscreen) {
		window->create(sf::VideoMode::getFullscreenModes()[0], "Pomland", sf::Style::Fullscreen);
	}
	else {
		window->create(sf::VideoMode((unsigned int)WINDOW_SIZE.x, (unsigned int)WINDOW_SIZE.y), "Pomland", sf::Style::Close);
	}
	updateView();
}

void Game::handleGlobalEvents() {
	if (!window->hasFocus()) {
		bool wasMusicPlaying = false;
		if (music->getStatus() == sf::SoundSource::Status::Playing) {
			wasMusicPlaying = true;
			music->pause();
		}
		while (!window->hasFocus()) {
			sf::sleep(sf::seconds(0.2f));
			Events::update();
		}
		if (wasMusicPlaying) {
			music->play();
		}
	}

	if (Events::pressedKey == sf::Keyboard::F4) {
		toggleFullscreen();
	}
}
bool Game::isPaused = false;
bool Game::isFullscreen = false;
bool Game::isRunning = true;

//-------------------------------------------------------------

void Game::initializeCharacters() {
}
void Game::initializeWindowSettings() {
	window->setVerticalSyncEnabled(true);
	window->setKeyRepeatEnabled(false);
	if (icon.getSize().x > 0) window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void Game::initialize() {
	window = std::make_unique<sf::RenderWindow>(sf::VideoMode((unsigned int)WINDOW_SIZE.x, (unsigned int)WINDOW_SIZE.y), "Pomland", sf::Style::Close);
	initializeWindowSettings();

	view = sf::View(sf::FloatRect(0.f, 0.f, GAME_SIZE.x, GAME_SIZE.y));
	window->setView(view);

	icon.loadFromFile(resource_paths::image::icon);
	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	texture = std::make_unique<sf::Texture>();
	texture->loadFromFile(resource_paths::image::sprites);

	texture_tileset = std::make_unique<sf::Texture>();
	texture_tileset->loadFromFile(resource_paths::image::tileset);

	font.loadFromFile(resource_paths::font::main);

	blackRectangle.setSize(GAME_SIZE);
	blackRectangle.setFillColor(sf::Color::Black);

	music = std::make_unique<sf::Music>();
	music->setLoop(true);

	narrator = std::make_unique<Character>("Narrator", resource_paths::sound::voice_narrator);
	aon = std::make_unique<Aon>();
	player = std::make_unique<Player>();

	dialogBox = std::make_unique<DialogBox>();
	dialogBox->setCharacter(narrator.get());
	dialogBox->setString("");
	dialogBox->setIsVisible(false);
	dialogBox->counter = 0;

	setRoom(new StartMenu());
}

//
// Public
//

void Game::run() {
	initialize();

	while (isRunning) {
		Events::update();
		handleGlobalEvents();

		room->update();

		//-------------------------------------------------------------

		view.setCenter(round(viewCenter.x) + 0.5f, round(viewCenter.y));
		window->setView(view);

		blackRectangle.setPosition(view.getCenter() - GAME_SIZE*0.5f);

		//-------------------------------------------------------------

		window->clear();
		room->draw();
		window->display();
	}

	window->close();
}
void Game::exit() {
	isRunning = false;
}

//-------------------------------------------------------------

Room* Game::room;
std::string Game::string_lastRoom = "";
void Game::setRoom(Room* p_room) {
	// Delete last room

	if (room != nullptr) {
		string_lastRoom = room->getName();
		delete room;
	}

	//-------------------------------------------------------------
	// Reset some global variables and stuff

	viewCenter = sf::Vector2f(GAME_SIZE.x * 0.5f, GAME_SIZE.y * 0.5f);

	dialogBox->setCharacter(narrator.get());
	dialogBox->counter = 0;

	music->setVolume(100);
	music->setLoop(true);

	frameCount = 0;
	Events::reset();
	player->resetHeading();

	//-------------------------------------------------------------
	// Set new room

	room = p_room;
	room->initialize();
}
