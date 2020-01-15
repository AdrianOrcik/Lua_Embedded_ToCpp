#include "src/lua.hpp"
#include <iostream>
#include <string>
#include <assert.h>
#include "src/Components/GameObject.h"

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

static void DEBUG_stackDump(lua_State *L, const char* header = nullptr) {
	lua_Debug ar;
	int i;
	int top = lua_gettop(L);

	if (header != nullptr) std::cout << "--" << header << std::endl;
	std::cout << "--begin-stack: " << std::endl;
	for (i = 1; i <= top; i++) {  /* repeat for each level */
		int t = lua_type(L, i);
		int reverse_index = ((top - (i - 1))*-1);
		
		switch (t) {
			case LUA_TSTRING:  /* strings */
				printf("TString - [%d] [`%s'] [%d]", i,lua_tostring(L, i), reverse_index);
				break;
			case LUA_TBOOLEAN:  /* booleans */
				printf("TBool - [%d] [%s] [%d]", i,lua_toboolean(L, i) ? "true" : "false", reverse_index);
				break;
			case LUA_TNUMBER:  /* numbers */
				printf("TNumber - [%d] [%s - %g ] [%d] ", i,lua_typename(L,t), lua_tonumber(L, i) ,reverse_index);
				break;
			case LUA_TFUNCTION: /* function*/
				//lua_getinfo(L, ">S", &ar);
				printf("TFunction - [%d] [%s] [%d]", i, lua_typename(L, t), reverse_index);
				break;
			default:  /* other values */
				printf("Other - [%d] [%s] [%d]", i, lua_typename(L, t), reverse_index);
				break;
		}

		printf("\n");
	}

	std::cout << "--end-stack: " << std::endl;
	printf("\n");  /* end the listing */
}

#pragma region CODE
//struct GameObject {
//	int x;
//	int y;
//
//	void Move(int _x, int _y) {
//		x = _x;
//		y = _y;
//		std::cout << "Position: " << x << "," << y << std::endl;
//	}
//};

//int lua_CreateGameObject(lua_State* L) {
//	GameObject* gameObject = (GameObject*)lua_newuserdata(L, sizeof(GameObject));
//	gameObject->x = 0;
//	gameObject->y = 0;
//	
//	return 1;
//}
//
//int lua_MoveGameObject(lua_State* L) {
//	GameObject* gameobject = (GameObject*)lua_touserdata(L,1);
//	int x = lua_tonumber(L, 2);
//	int y = lua_tonumber(L, 3);
//
//	gameobject->Move(x, y);
//	return 1;
//}
//
//
//int lua_Sum(lua_State* L) {
//	
//	int a = lua_tonumber(L, 1);
//	int b = lua_tonumber(L, 2);
//
//	std::cout << a << " " << b << std::endl;
//	int c = a + b;
//	lua_pushnumber(L, c);
//	return 1;
//}


//struct GameObject_Table {
//
//	static int __add(lua_State* L) {
//
//		lua_pushstring(L, "x");
//		lua_gettable(L, -3);
//		int xLeft = lua_tonumber(L, -1);
//		lua_pop(L, 1);
//
//		lua_pushstring(L, "x");
//		lua_gettable(L, -2);
//		int xRight = lua_tonumber(L, -1);
//		lua_pop(L, 1);
//
//		int xAdded = xLeft + xRight;
//		std::cout << xAdded << std::endl;
//
//		GameObject_Table::CreateGameObject(L);
//		lua_pushstring(L, "x");
//		lua_pushnumber(L, xAdded);
//		lua_rawset(L, -3); //Set table without invoking
//		return 1;
//	}
//
//	static int CreateGameObject(lua_State* L) {
//		
//		lua_newtable(L);
//
//		lua_pushstring(L, "x");
//		lua_pushnumber(L, 0);
//		lua_settable(L, -3);
//
//
//		lua_pushstring(L, "y");
//		lua_pushnumber(L, 0);
//		lua_settable(L, -3);
//
//		luaL_getmetatable(L, "GameObjectMetaTable");
//		lua_setmetatable(L, -2);
//
//		return 1;
//	}
//
//};

#pragma endregion CODE

int main() 
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L); 
	luaopen_debug(L);

	Lua_Init_GameObject(L);

	int lua_source = luaL_dofile(L, "src/LuaScripts/LuaScript.lua");
	if (IsLuaValid(L, lua_source))
	{


	}
	

	lua_close(L);
	return 0;
}