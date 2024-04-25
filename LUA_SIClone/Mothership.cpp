/*
Space invaders game
Author:		Philip Alassad
Filename:	Mothership.cpp
Date:		14/10/2015
Last Updated:	23/04/2024 (Matthew Bell)

Description: Source file for Mothership class
*/

#include "Mothership.h"
#include <stdio.h>

//Constructor
Mothership::Mothership(float xPos, float yPos, string filename, lua_State* lua)
	:Ship(xPos, yPos, filename)
{	
	m_lives = 3;
	m_xpos = xPos;
	m_ypos = yPos;
	L = lua;
}

Mothership::~Mothership()
{

}

//Methods
void Mothership::left()
{
}

void Mothership::right()
{
	m_xpos = m_xpos + LuaGetFloat(L, "mothershipSpeed");
}

void Mothership::reduceLives()
{
	m_lives --;
}

int Mothership::getLives()
{
	return m_lives;
}
