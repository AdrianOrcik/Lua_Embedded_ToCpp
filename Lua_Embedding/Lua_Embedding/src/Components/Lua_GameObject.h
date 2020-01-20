#pragma once 
#include "../lua.hpp"
#include <iostream>
#include <string>
#include <assert.h>

struct Lua_GameObject
{
	int x;
	int y;

	Lua_GameObject() :x(0), y(0) {}
	~Lua_GameObject() {}

	void Move(int _x, int _y)
	{
		x += _x;
		y += _y;
	}

	void Draw()
	{
		std::cout << this << " x:" << x << " y:" << y << std::endl;
	}
};

int Lua_GameObject_Create(lua_State* L)
{
	void* gameObject_Pointer = lua_newuserdata(L, sizeof(Lua_GameObject));
	new (gameObject_Pointer) Lua_GameObject();
	luaL_getmetatable(L, "GameObject_MetaTable");
	lua_setmetatable(L, -2);
	return 1;
}

int Lua_GameObject_Destroy(lua_State* L)
{
	Lua_GameObject* gameObject = (Lua_GameObject*)lua_touserdata(L, -1);
	gameObject->~Lua_GameObject();
	return 1;
}

int Lua_GameObject_Move(lua_State* L)
{
	Lua_GameObject* gameObject = (Lua_GameObject*)lua_touserdata(L, -3);
	int x = lua_tonumber(L, -2);
	int y = lua_tonumber(L, -1);
	gameObject->Move(x, y);
	return 1;
}

int Lua_GameObject_Draw(lua_State* L)
{
	Lua_GameObject* gameObject = (Lua_GameObject*)lua_touserdata(L, -1);
	gameObject->Draw();
	return 0;
}

void Lua_Init_GameObject(lua_State* L)
{
	//Table
	lua_newtable(L);
	int gameObject_Table_ID = lua_gettop(L);
	lua_pushvalue(L, gameObject_Table_ID);
	lua_setglobal(L, "GameObject");

	lua_pushcfunction(L, Lua_GameObject_Create);
	lua_setfield(L, -2, "Create");

	lua_pushcfunction(L, Lua_GameObject_Move);
	lua_setfield(L, -2, "Move");

	lua_pushcfunction(L, Lua_GameObject_Draw);
	lua_setfield(L, -2, "Draw");

	//Table Behaviour
	luaL_newmetatable(L, "GameObject_MetaTable");
	lua_pushstring(L, "__gc");
	lua_pushcfunction(L, Lua_GameObject_Destroy);
	lua_settable(L, -3);

	lua_pushstring(L, "__index");
	lua_pushvalue(L, gameObject_Table_ID);
	lua_settable(L, -3);
}
