#pragma once
#include "global.hpp"
#include "../character/Character.hpp"
#include "../character/Player.hpp"
#include "../character/Aon.hpp"

class Room;

class Game {
private:
	static void updateView();
	static void toggleFullscreen();
	
	static void handleGlobalEvents();
	static bool isPaused;
	static bool isFullscreen;
	static bool isRunning;
	
	//-------------------------------------------------------------

	static void initializeCharacters();
	static void initializeWindowSettings();

	static void initialize();

public:
	static void run();
	static void exit();

	//-------------------------------------------------------------

	static Room* room;
	static std::string string_lastRoom;
	static void setRoom(Room* p_room);

	//-------------------------------------------------------------

	inline static std::unique_ptr<DialogBox> dialogBox;

	inline static std::unique_ptr<Character> narrator;
	inline static std::unique_ptr<Aon> aon;
	inline static std::unique_ptr<Player> player;
};