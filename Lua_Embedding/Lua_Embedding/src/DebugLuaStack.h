#pragma once
#include "lua.hpp"
#include <iostream>

void DEBUG_stackDump(lua_State *L, const char* header = nullptr) {
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
			printf("TString - [%d] [`%s'] [%d]", i, lua_tostring(L, i), reverse_index);
			break;
		case LUA_TBOOLEAN:  /* booleans */
			printf("TBool - [%d] [%s] [%d]", i, lua_toboolean(L, i) ? "true" : "false", reverse_index);
			break;
		case LUA_TNUMBER:  /* numbers */
			printf("TNumber - [%d] [%s - %g ] [%d] ", i, lua_typename(L, t), lua_tonumber(L, i), reverse_index);
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