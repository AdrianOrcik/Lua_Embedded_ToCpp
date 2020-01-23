#pragma once 
#include "../lua.hpp"
#include <iostream>
#include <Windows.h>
#include <string>

struct Lua_UI
{
	HANDLE m_Handler;

	Lua_UI()
	{
		m_Handler = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	~Lua_UI(){}

	void Text(int x, int y, const std::string text)
	{
		COORD coord = { x,y };
		SetConsoleCursorPosition(m_Handler, coord);
		std::cout << text << std::endl;
	}

	int InputField_Int(int x, int y, const std::string text)
	{
		COORD coord = { x,y };
		int value = 0;
		SetConsoleCursorPosition(m_Handler, coord);
		std::cout << text << " ";
		std::cin >> value;
		return value;
	}

	float InputField_Float(int x, int y, const std::string text)
	{
		COORD coord = { x,y };
		float value = 0;
		SetConsoleCursorPosition(m_Handler, coord);
		std::cout << text << " ";
		std::cin >> value;
		return value;
	}
};

int Lua_UI_Create(lua_State* L)
{
	void* luaUI_Pointer = lua_newuserdata(L, sizeof(Lua_UI));
	new(luaUI_Pointer) Lua_UI();
	luaL_newmetatable(L, "Canvas_MetaTable");
	lua_setmetatable(L, -2);
	return 1;
}

int Lua_UI_Destroy(lua_State* L)
{
	Lua_UI* luaUI = (Lua_UI*)lua_touserdata(L, -1);
	luaUI->~Lua_UI();
	return 1;
}

int Lua_UI_Text(lua_State* L)
{
	Lua_UI* luaUI = (Lua_UI*)lua_touserdata(L, -4);
	int x = lua_tonumber(L, -3);
	int y = lua_tonumber(L, -2);
	const std::string text = lua_tostring(L, -1);
	luaUI->Text(x, y, text);
	return 1;
}

int Lua_UI_InputField_Int(lua_State* L)
{
	Lua_UI* luaUI = (Lua_UI*)lua_touserdata(L, -4);
	int x = lua_tonumber(L, -3);
	int y = lua_tonumber(L, -2);
	const std::string text = lua_tostring(L, -1);
	int value = luaUI->InputField_Int(x, y, text);
	lua_pushnumber(L, value);
	return 1;
}

int Lua_UI_InputField_Float(lua_State* L)
{
	Lua_UI* luaUI = (Lua_UI*)lua_touserdata(L, -4);
	int x = lua_tonumber(L, -3);
	int y = lua_tonumber(L, -2);
	const std::string text = lua_tostring(L, -1);
	float value = luaUI->InputField_Float(x, y, text);
	lua_pushnumber(L, value);
	return 1;
}

void Lua_Init_UI(lua_State* L)
{
	//Table
	lua_newtable(L);
	int ui_Table_ID = lua_gettop(L);
	lua_pushvalue(L, ui_Table_ID);
	lua_setglobal(L, "Canvas");

	lua_pushcfunction(L, Lua_UI_Create);
	lua_setfield(L, -2, "Create");

	lua_pushcfunction(L, Lua_UI_Text);
	lua_setfield(L, -2, "Text");

	lua_pushcfunction(L, Lua_UI_InputField_Int);
	lua_setfield(L, -2, "InputField_Int");

	lua_pushcfunction(L, Lua_UI_InputField_Float);
	lua_setfield(L, -2, "InputField_Float");

	//Table Behaviour
	luaL_newmetatable(L, "Canvas_MetaTable");
	lua_pushstring(L, "__gc");
	lua_pushcfunction(L, Lua_UI_Destroy);
	lua_settable(L, -3);

	lua_pushstring(L, "__index");
	lua_pushvalue(L, ui_Table_ID);
	lua_settable(L, -3);
}