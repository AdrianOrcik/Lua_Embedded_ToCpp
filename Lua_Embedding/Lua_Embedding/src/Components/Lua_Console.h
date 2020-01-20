#include "../lua.hpp"
#include "src/DebugLuaStack.h"
#include <iostream>
#include <Windows.h>
#include <ctime>

struct Lua_Console
{
	static void Sleep(int seconds)
	{
		clock_t delay = seconds * CLOCKS_PER_SEC;
		clock_t start = GetTickCount();
		while (GetTickCount() - start < delay) {}

		//Sleep has problem to keep stack of functions during waiting
		//Sleep(miliseconds);
	}

	static void Clear()
	{
		std::system("cls");
	}

};

int Lua_Console_Sleep(lua_State* L)
{
	int miliseconds = lua_tonumber(L, -1);
	Lua_Console::Sleep(miliseconds);
	return 1;
}

int Lua_Console_Clean(lua_State* L)
{
	Lua_Console::Clear();
	return 0;
}

void Lua_Init_Console(lua_State* L)
{
	//Table
	lua_newtable(L);
	int console_Table_ID = lua_gettop(L);
	lua_pushvalue(L, console_Table_ID);
	lua_setglobal(L, "Console");

	lua_pushcfunction(L, Lua_Console_Sleep);
	lua_setfield(L, -2, "Sleep");

	lua_pushcfunction(L, Lua_Console_Clean);
	lua_setfield(L, -2, "Clear");
}