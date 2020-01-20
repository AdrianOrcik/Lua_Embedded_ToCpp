#pragma once 
#include "../lua.hpp"
#include <iostream>
#include <string>
#include <assert.h>
#include <fstream>
#include <Windows.h>

struct Lua_ASCIIRenderer
{
	std::string* m_Sprite;
	int m_SpriteHeight;
	HANDLE m_Handler;

	Lua_ASCIIRenderer() 
	{
		m_Handler = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	~Lua_ASCIIRenderer() {}

	void LoadSprite(const std::string filePath, int imgSize)
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
			m_Sprite = art;
			m_SpriteHeight = imgSize;
			reader.close();
		}
	}


	void Draw(int x, int y)
	{
		COORD coord = { x,y };
		for (int i = 0; i < m_SpriteHeight; i++) {
			SetConsoleCursorPosition(m_Handler, coord);
			std::cout << m_Sprite[i] << std::endl;
			coord.Y++;
		}
	}
};

int Lua_ASCIIRenderer_Create(lua_State* L) 
{
	void* asciiRenderer_Pointer = lua_newuserdata(L, sizeof(Lua_ASCIIRenderer));
	new (asciiRenderer_Pointer) Lua_ASCIIRenderer();
	luaL_getmetatable(L, "ASCIIRenderer_MetaTable");
	lua_setmetatable(L, -2);
	return 1;
}

int Lua_ASCIIRenderer_Destroy(lua_State* L) 
{
	Lua_ASCIIRenderer* asciiRenderer = (Lua_ASCIIRenderer*)lua_touserdata(L, -1);
	asciiRenderer->~Lua_ASCIIRenderer();
	return 1;
}

int Lua_ASCIIRenderer_LoadSprite(lua_State* L) 
{
	Lua_ASCIIRenderer* asciiRenderer = (Lua_ASCIIRenderer*)lua_touserdata(L, -3);
	std::string filePath = lua_tostring(L, -2);
	int imgSize = lua_tonumber(L, -1);
	asciiRenderer->LoadSprite(filePath, imgSize);
	return 1;
}

int Lua_ASCIIRenderer_Draw(lua_State* L) 
{
	Lua_ASCIIRenderer* asciiRenderer = (Lua_ASCIIRenderer*)lua_touserdata(L, -3);
	int x = lua_tonumber(L, -2);
	int y = lua_tonumber(L, - 1);
	asciiRenderer->Draw(x,y);
	return 0;
}

void Lua_Init_ASCIIRenderer(lua_State* L)
{
	//Table
	lua_newtable(L);
	int asciiRenderer_Table_ID = lua_gettop(L);
	lua_pushvalue(L, asciiRenderer_Table_ID);
	lua_setglobal(L, "ASCIIRenderer");

	lua_pushcfunction(L, Lua_ASCIIRenderer_Create);
	lua_setfield(L, -2, "Create");

	lua_pushcfunction(L, Lua_ASCIIRenderer_LoadSprite);
	lua_setfield(L, -2, "LoadSprite");

	lua_pushcfunction(L, Lua_ASCIIRenderer_Draw);
	lua_setfield(L, -2, "Draw");

	//Table Behaviour
	luaL_newmetatable(L, "ASCIIRenderer_MetaTable");
	lua_pushstring(L, "__gc");
	lua_pushcfunction(L, Lua_ASCIIRenderer_Destroy);
	lua_settable(L, -3);

	lua_pushstring(L, "__index");
	lua_pushvalue(L, asciiRenderer_Table_ID);
	lua_settable(L, -3);
}
