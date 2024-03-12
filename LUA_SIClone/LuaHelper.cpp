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
	return (int)lua_tointeger(L, -1);
}

string LuaGetStr(lua_State* L, const string& name)
{
	lua_getglobal(L, name.c_str());
	if (!lua_isstring(L, -1))
	{
		assert(false);
	}
	return lua_tostring(L, -1);
}

bool LuaGetBool(lua_State* L, const string& name)
{
	lua_getglobal(L, name.c_str());
	if (!lua_isboolean(L, -1))
	{
		assert(false);
	}
	return lua_toboolean(L, -1);
}

float LuaGetFloat(lua_State* L, const string& name)
{
	lua_getglobal(L, name.c_str());
	if (!lua_isnumber(L, -1))
	{
		assert(false);
	}
	return (float)lua_tonumber(L, -1);
}

double LuaGetDouble(lua_State* L, const string& name)
{
	lua_getglobal(L, name.c_str());
	if (!lua_isnumber(L, -1))
	{
		assert(false);
	}
	return (double)lua_tonumber(L, -1);
}