#pragma once

#include <string>
#include <functional>
#include <map>

#include <assert.h>		// for debug assertions

extern "C"
{
	#include "../lua-5.4.4/include/lua.h"
	#include "../lua-5.4.4/include/lauxlib.h"
	#include "../lua-5.4.4/include/lualib.h"
}

#ifdef _WIN32
#pragma comment(lib, "../lua-5.4.4/liblua54.a")
#endif // _WIN32

// Check for errors
bool LuaOK(lua_State* L, int id);

// Get an int from Lua
int LuaGetInt(lua_State* L, const std::string& name);

// Get a string from Lua
std::string LuaGetStr(lua_State* L, const std::string& name);

// Get a boolean from Lua
bool LuaGetBool(lua_State* L, const std::string& name);

// Get a float from Lua
float LuaGetFloat(lua_State* L, const std::string& name);

// Get a double from Lua
double LuaGetDouble(lua_State* L, const std::string& name);


struct Vector2
{
	int x, y;
	void FromLua(lua_State* L, const std::string& name)
	{
		lua_getglobal(L, name.c_str());
		if (!lua_istable(L, -1))
		{
			assert(false);
		}

		lua_pushstring(L, "x");
		lua_gettable(L, -2);
		x = (int)lua_tointeger(L, -1);
		lua_pop(L, 1);

		lua_pushstring(L, "y");
		lua_gettable(L, -2);
		y = (int)lua_tointeger(L, -1);
		lua_pop(L, 1);
	}
};