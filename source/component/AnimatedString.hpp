#pragma once
#include "../main/global.hpp"

//-------------------------------------------------------------

class AnimatedString{
private:
	std::string currentString;
	std::string targetString;

	//-------------------------------------------------------------

	unsigned int speed = 5;
	unsigned int currentDelay = speed;
	
	unsigned long updateCount = 0;

public:
	AnimatedString();
	AnimatedString(std::string p_string);
	
	//-------------------------------------------------------------

	void set(std::string p_string);
	std::string get();
	std::string getTarget();

	//-------------------------------------------------------------
	
	bool update();
	bool getIsAnimationDone();
	
	void complete();
	void reset();

	//-------------------------------------------------------------
	
	void setSpeed(unsigned int p_speed);
};