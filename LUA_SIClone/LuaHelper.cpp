#include "LuaHelper.h"

#include <iostream>		// for cout

using namespace std;

bool LuaOK(lua_State* L, int id)
{
	if (id != LUA_OK)
	{
		cout << lua_tostring(L, -1) << endl;	// Print out the error
		return false;
	}
	return true;
}

int LuaGetInt(lua_State* L, const string& name)
{
	lua_getglobal(L, name.c_str());
	if (!lua_isinteger(L, -1))
	{
		assert(false);
	}
	// lua_tointeger returns lua_Integer (typedef: long long) so must be cast to int
	return (int)lua_tointeger(L, -1);
}

string LuaGetStr(lua_State* L, const string& name)
{
	lua_getglobal(L, name.c_str());
	if (!lua_isstring(L, -1))
	{
		assert(false);
	}
	// lua_tostring returns const char*
	return lua_tostring(L, -1);
}

bool LuaGetBool(lua_State* L, const string& name)
{
	lua_getglobal(L, name.c_str());
	if (!lua_isboolean(L, -1))
	{
		assert(false);
	}
	// lua_toboolean returns int, no need to cast
	return lua_toboolean(L, -1);
}

float LuaGetFloat(lua_State* L, const string& name)
{
	lua_getglobal(L, name.c_str());
	if (!lua_isnumber(L, -1))
	{
		assert(false);
	}
	// lua_tonumber returns lua_Number (typedef: double) so must be cast to float
	return (float)lua_tonumber(L, -1);
}

double LuaGetDouble(lua_State* L, const string& name)
{
	lua_getglobal(L, name.c_str());
	if (!lua_isnumber(L, -1))
	{
		assert(false);
	}
	// lua_tonumber returns lua_Number (typedef: double)
	return lua_tonumber(L, -1);
}



int CallRNG(lua_State* L, const string& fName)
{
	lua_getglobal(L, fName.c_str());
	if (!lua_isfunction(L, -1))
	{
		assert(false);
	}
	if (!LuaOK(L, lua_pcall(L, 0, 1, 0)))	// Calls a function in protected mode (state, num of parameters, num of returns, errorfunc)
	{
		assert(false);
	}
	int result = (int)lua_tointeger(L, -1);
	lua_pop(L, 1);
	return result;
}

void CallMoveRight(lua_State* L, const string& fName, float& x, float& frame)
{
	lua_getglobal(L, fName.c_str());
	if (!lua_isfunction(L, -1))
	{
		assert(false);
	}
	lua_pushnumber(L, x);
	lua_pushnumber(L, frame);
	if (!LuaOK(L, lua_pcall(L, 2, 2, 0)))	// Calls a function in protected mode (state, num of parameters, num of returns, errorfunc)
	{
		assert(false);
	}
	x = (float)lua_tonumber(L, -2);
	frame = (float)lua_tonumber(L, -1);
	lua_pop(L, 2);
}

void CallVoidVoidCFunc(lua_State* L, const string& fname)
{
	lua_getglobal(L, fname.c_str());
	if (!lua_isfunction(L, -1))
	{
		assert(false);
	}
	if (!LuaOK(L, lua_pcall(L, 0, 0, 0)))
	{
		assert(false);
	}
}



std::map<string, Dispatcher::Command> Dispatcher::library;

int Dispatcher::LuaCall(lua_State* L)
{
	string name = lua_tostring(L, 1);
	std::map<string, Command>::iterator it = library.find(name);
	assert(it != library.end());
	Command& cmd = (*it).second;
	if (cmd.voidintfunct)
	{
		int param = lua_tointeger(L, 2);
		cmd.voidintfunct(param);
		lua_pop(L, 1);
	}
	else if (cmd.voidvoidfunct)
	{
		cmd.voidvoidfunct();
		lua_pop(L, 1);
	}
	else // Add any more cases here
	{
		assert(false);
	}
	return 1;
}