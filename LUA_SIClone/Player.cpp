/*
Space invaders game
Author:		Philip Alassad
Filename:	Player.cpp
Date:		14/10/2015
Last Updated:	23/04/2024 (Matthew Bell)

Description: Source file for Player class
*/

#include "Player.h"
#include <stdio.h>

//Constructor
Player::Player(float xPos, float yPos, int lives, string filename)
	:Ship(xPos, yPos, filename)
{
	m_lives = lives;
	m_score = 0;

	L = luaL_newstate();

	// Open main libraries for scripts
	luaL_openlibs(L);

	// Load and parse the Lua file
	if (!LuaOK(L, luaL_dofile(L, "Script.lua")))
	{
		assert(false);
	}
}

Player::~Player()
{
	lua_close(L);
}

void Player::Init(Dispatcher& disp)
{
	// Tell the dispatcher we have a new (void int) function for LUA
	Dispatcher::Command::voidintfunc vif{[this](int score) {return setScore(score); } };
	disp.Register("setScore", Dispatcher::Command{vif});

	// Tell the dispatcher we have a new (void void) function for LUA
	Dispatcher::Command::voidvoidfunc vvf{[this]() {return kill(); } };
	disp.Register("kill", Dispatcher::Command{NULL, vvf});
}

void Player::right(void)
{
	CallMoveRight(L, "right", m_xpos, m_direction_flag);
}

//Methods
int Player::getScore()//gets the current score
{
	return m_score;
}

void Player::reduceLives()
{
	m_lives -= 1;
}

void Player::increaseLives()
{
	m_lives += 1;
}

int Player::getLives()
{
	return m_lives;
}

void Player::setScore(int score)
{
	m_score = m_score + score;
}

void Player::kill()
{
	m_lives = -1;
}

void Player::reset_lives()
{
	m_lives = 3;
}

void Player::reset_score()
{
	m_score = 0;
}

void Player::setFrame(int frame)
{
	m_current_frame = frame;
}