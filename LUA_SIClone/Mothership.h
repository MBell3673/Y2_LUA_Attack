/*
Space invaders game
Author:		Philip Alassad
Filename:	Mothership.h
Date:		14/10/2015
Last Updated:	25/10/2015

Description: Header file for Mothership class
*/

#pragma once

//includes go here
#include "Ship.h"


using namespace std;

class Mothership : public Ship
{
private:
	//members
	int m_lives;
	lua_State* L = nullptr;

public:
	//constructor
	Mothership(float xPos, float yPos, string filename, lua_State* lua);
	~Mothership(void);

	//methods
	void left();
	void right();
	void reduceLives();
	int getLives();

};