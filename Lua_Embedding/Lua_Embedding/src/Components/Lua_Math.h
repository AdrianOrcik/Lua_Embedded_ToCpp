#include "../lua.hpp"
#include "../DebugLuaStack.h"
#include <iostream>

struct Lua_Math
{
	#define GRAVITY -9.8
	#define PI 3.14159265
	
	static float DegToRad(float degrees)
	{
		return (degrees * PI) / 180.0;
	}

	static float MaxHeight(float initSpeed, float directionAngle) 
	{
		return abs((pow(initSpeed, 2.0) *  pow(sin(DegToRad(directionAngle)), 2.0)) / (2.0 * GRAVITY));
	}

	static float MaxDistance(float initSpeed, float directionAngle)
	{
		return abs(((pow(initSpeed, 2.0)*pow(sin(DegToRad(directionAngle)), 2.0)) / GRAVITY));
	}

#pragma region NotImplemented
	//Note: Not implemented

	//static float PositionXInTime(float inTime, float speed, float directionAngle, float initXValue = 0)
	//{
	//	return initXValue + (speed * inTime * cos(DegToRad(directionAngle)));
	//}

	//static float PositionYInTime(float inTime, float speed, float directionAngle, float initYValue = 0)
	//{
	//	return initYValue + (speed * inTime * sin(DegToRad(directionAngle))) - ((GRAVITY * pow(inTime, 2)) * 0.5);
	//}

	//static float TimeToHitMaxHeight(float speed, float directionAngle)
	//{
	//	return abs(speed * sin(DegToRad(directionAngle)) / GRAVITY);
	//}

	//static float TimeToHitMaxDistance(float speed, float directionAngle)
	//{
	//	return abs(2 * speed * sin(DegToRad(directionAngle)) / GRAVITY);
	//}
#pragma endregion NotImplemented
};

int Lua_Math_DegToRad(lua_State* L)
{
	float deg = lua_tonumber(L, -1);
	float rad = Lua_Math::DegToRad(deg);
	lua_pushnumber(L, rad);
	return 1;
}

int Lua_Math_MaxHeight(lua_State* L)
{
	float initSpeed = lua_tonumber(L, -2);
	float directionAngle = lua_tonumber(L, -1);
	float maxHeight = Lua_Math::MaxHeight(initSpeed, directionAngle);
	lua_pushnumber(L, maxHeight);
	return 1;
}

int Lua_Math_MaxDistance(lua_State* L)
{
	float initSpeed = lua_tonumber(L, -2);
	float directionAngle = lua_tonumber(L, -1);
	float maxDistance = Lua_Math::MaxDistance(initSpeed, directionAngle);
	lua_pushnumber(L, maxDistance);
	return 1;
}

void Lua_Init_Math(lua_State* L)
{
	//Table
	lua_newtable(L);
	int math_Table_ID = lua_gettop(L);
	lua_pushvalue(L, math_Table_ID);
	lua_setglobal(L, "Math");

	lua_pushcfunction(L, Lua_Math_DegToRad);
	lua_setfield(L, -2, "DegToRad");

	lua_pushcfunction(L, Lua_Math_MaxHeight);
	lua_setfield(L, -2, "MaxHeight");

	lua_pushcfunction(L, Lua_Math_MaxDistance);
	lua_setfield(L, -2, "MaxDistance");
}