/*
Space invaders game
Author:		Philip Alassad
Filename:	Ufo.cpp
Date:		14/10/2015
Last Updated:	23/04/2024 (Matthew Bell)

Description: Source file for Ufo class
*/

#include "Ufo.h"
#include <stdio.h>

//Constructor
Ufo::Ufo( float xPos, float yPos, string filename, lua_State* lua)
	:Ship(xPos, yPos, filename)
{
	m_xpos = xPos;
	m_ypos = yPos;
	L = lua;
}

Ufo::~Ufo()
{
	
}

//Methods
void Ufo::right(int counter, int level)
{
	m_direction_flag = true;
	move((float)counter, (float)level);
}

void Ufo::left(int counter, int level)
{
	m_direction_flag = false;
	move((float)counter, (float)level);
}

// A standardised function for moving the enemies either left or right depending on directional flag
void Ufo::move(float counter, float level)
{
	CallMoveUFO(L, "moveUfo", m_xpos, m_current_frame, counter, level, (bool)m_direction_flag);
}


