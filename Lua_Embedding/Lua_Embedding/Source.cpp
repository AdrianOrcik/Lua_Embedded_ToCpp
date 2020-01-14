#include "src/lua.hpp"
#include <iostream>
#include <string>

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

int main() 
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L); //Add general libs what programmer can use
	luaopen_debug(L);

	int lua_source = luaL_dofile(L, "src/LuaScripts/LuaScript.lua");
	if (IsLuaValid(L, lua_source))
	{
		lua_getglobal(L, "a");
		lua_getglobal(L, "Return4");
		DEBUG_stackDump(L);
		if (lua_isfunction(L, -1)) {
			lua_pcall(L, 0, 1,0);
			DEBUG_stackDump(L);
			int a = lua_tonumber(L, -1);
			DEBUG_stackDump(L);
			std::cout << a << std::endl;
		}
	}

	lua_close(L);
	return 0;
}