//Lua 
#include "src/lua.hpp"
//Cpp standard libs
#include <iostream>
#include <string>
#include <assert.h>
#include <Windows.h>
#include <time.h> 
#include <cstdlib>
#include <vector>
//Embedded components
#include "src/Components/Lua_GameObject.h"
#include "src/Components/Lua_Sprite.h"
#include "src/Components/Lua_Console.h"
#include "src/DebugLuaStack.h"
#include "src/Components/Lua_Math.h"
#include "src/Components/Lua_UI.h"
#include "src/Components/Lua_Animator.h"

//Lua load file validator
bool IsLuaValid(lua_State *L, int result) 
{
	if(result != LUA_OK)
	{
		std::string errormsg = lua_tostring(L, -1);
		std::cout << errormsg << std::endl;
		return false;
	}
	return true;
}

void Lua_Init()
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	luaopen_debug(L);

	Lua_Init_GameObject(L);
	Lua_Init_Sprite(L);
	Lua_Init_Console(L);
	Lua_Init_Math(L);
	Lua_Init_UI(L);
	Lua_Init_Animator(L);
	
	int lua_source = luaL_dofile(L, "src/LuaScripts/LuaScript.lua");
	if (IsLuaValid(L, lua_source))
	{
	}
	lua_close(L);
	std::cout << "OK" << std::endl;
}

int main() 
{
	Lua_Init();	
	return 0;
}