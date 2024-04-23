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

// Call LUA function "rng"; returns a random number
int CallRNG(lua_State* L, const std::string& fName = "rng");

// Call LUA function "right"; moves the player ship right
void CallMoveRight(lua_State* L, const std::string& fName, float& x, float& frame);

// Call a void C function from LUA
void CallVoidVoidCFunc(lua_State* L, const std::string& fname);


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


// A middle man between C++ and LUA. Register class member functions so
// your LUA script can call them.
class Dispatcher
{
public:
// Capture game functions here
	struct Command
	{
		typedef std::function<void(int)> voidintfunc; // A function which returns void and takes an int
		voidintfunc voidintfunct;
		typedef std::function<void(void)> voidvoidfunc; // A function which returns void and takes a void
		voidvoidfunc voidvoidfunct;
		// Add any other function signatures here
	};

	// Call once at the start
	void Init(lua_State* L)
	{
		lua_register(L, "CDispatcher", LuaCall);
	}

	// Register game functions
	void Register(const std::string& name, Command cmd)
	{
		assert(library.find(name) == library.end());
		library[name] = cmd;
	}

	// LUA calls this, then the data gets dispatched to that named function
	// LUA is old-school C based, so it cannot call class member fnctions without help
	static int LuaCall(lua_State* L);
private:
	static std::map<std::string, Command> library; // This is where game functions are stored
};