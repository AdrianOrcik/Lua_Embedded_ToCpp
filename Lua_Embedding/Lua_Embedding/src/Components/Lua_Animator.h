#pragma once 
#include "../lua.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <fstream>

struct Lua_Animator
{
	std::vector<std::string*>	m_AnimationSheet;
	std::string*				m_Sprite;
	int							m_AnimationSheetHeight;
	HANDLE						m_Handler;

	Lua_Animator()
	{
		m_Handler = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	~Lua_Animator(){}

	void AddSpriteToSheet(const std::string filePath, int imgSize)
	{
		std::ifstream reader(filePath);
		std::string* art = new std::string[imgSize];
		int tmp_line = 0;
		if (reader)
		{
			while (reader.good()) {
				std::string tempLine;
				std::getline(reader, tempLine);
				art[tmp_line] = tempLine;
				tmp_line++;
			}
			reader.close();
			m_AnimationSheetHeight = imgSize;
			m_AnimationSheet.push_back(art);
		}
	}

	void AnimateSheet(int x, int y, int animationDelay)	
	{
		if (m_AnimationSheet.size() == 0)
		{
			std::cout << "ERROR::ANIMATOR::ANIMATION_SHEET_EMPTY" << std::endl;
			return;
		}

		std::system("cls");
		for (int i = 0; i < m_AnimationSheet.size(); i++)
		{
			Draw(x,y, m_AnimationSheet[i]);
			Sleep(animationDelay);
			std::system("cls");
		}
	}

	void Draw(int x, int y,std::string* sprite)
	{
		COORD coord = { x,y };
		for (int i = 0; i < m_AnimationSheetHeight; i++) {
			SetConsoleCursorPosition(m_Handler, coord);
			std::cout << sprite[i] << std::endl;
			coord.Y++;
		}
	}
};

int Lua_Animator_Create(lua_State* L)
{
	void* animator_Pointer = lua_newuserdata(L, sizeof(Lua_Animator));
	new (animator_Pointer)Lua_Animator();
	luaL_getmetatable(L, "Animator_MetaTable");
	lua_setmetatable(L, -2);
	return 1;
}

int Lua_Animator_Destroy(lua_State* L)
{
	Lua_Animator* animator = (Lua_Animator*)lua_touserdata(L, -1);
	animator->~Lua_Animator();
	return 1;
}

int Lua_Animator_AddToSheet(lua_State* L)
{
	Lua_Animator* animator = (Lua_Animator*)lua_touserdata(L, -3);
	std::string filePath = lua_tostring(L, -2);
	int imgSize = lua_tonumber(L, -1);
	animator->AddSpriteToSheet(filePath, imgSize);
	return 1;
}

int Lua_Animator_Animate(lua_State* L)
{
	Lua_Animator* animator = (Lua_Animator*)lua_touserdata(L, -4);
	int x = lua_tonumber(L, -3);
	int y = lua_tonumber(L, -2);
	int animateDelay = lua_tonumber(L, -1);
	animator->AnimateSheet(x, y, animateDelay);
	return 0;
}

void Lua_Init_Animator(lua_State* L)
{
	//Table
	lua_newtable(L);
	int tableID = lua_gettop(L);
	lua_pushvalue(L, tableID);
	lua_setglobal(L, "Animator");

	lua_pushcfunction(L, Lua_Animator_Create);
	lua_setfield(L, -2, "Create");

	lua_pushcfunction(L, Lua_Animator_AddToSheet);
	lua_setfield(L, -2, "AddToSheet");

	lua_pushcfunction(L, Lua_Animator_Animate);
	lua_setfield(L, -2, "Animate");

	//Table Behaviour
	luaL_newmetatable(L, "Animator_MetaTable");
	lua_pushstring(L, "__gc");
	lua_pushcfunction(L, Lua_Animator_Destroy);
	lua_settable(L, -3);

	lua_pushstring(L, "__index");
	lua_pushvalue(L, tableID);
	lua_settable(L, -3);
}