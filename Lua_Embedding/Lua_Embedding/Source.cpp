#include "src/lua.hpp"
#include <iostream>
#include <string>
#include <assert.h>

#include "src/Components/Lua_GameObject.h"
#include "src/Components/Lua_Sprite.h"
#include "src/Components/Lua_Console.h"
#include "src/DebugLuaStack.h"

#include <Windows.h>
#include <time.h> 
#include <cstdlib>

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

const unsigned char RohVpravoDole = 0xd9;     // ostatne si zistite sami!


#include <iostream>
#include <fstream>
#include <string>

std::string getFileContents(std::ifstream&);          


//std::string getFileContents(std::ifstream& File)
//{
//	std::string Lines = "";       
//	int tmp_line = 0;
//	if (File)           
//	{
//		while (File.good())
//		{
//			std::string TempLine;               
//			std::getline(File, TempLine);
//			TempLine += "\n";
//			Lines += TempLine;
//		}
//		return Lines;
//	}
//	else                       
//	{
//		return "ERROR File does not exist.";
//	}
//}

std::string* getFileContentsArr(std::ifstream& File, int imgSize)
{
	std::string* art = new std::string[imgSize];
	int tmp_line = 0;
	if (File) 
	{
		while (File.good()) {
			std::string tempLine;
			std::getline(File, tempLine);
			art[tmp_line] = tempLine;
			tmp_line++;
		}
		return art;
	}

	return nullptr;
}

std::string* getFileContentsArr_Path(const std::string filePath, int imgSize)
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
		return art;
	}
	return nullptr;
}

void Draw(HANDLE hConsole, COORD position, std::string* sprite, int size)
{
	for (int i = 0; i < size; i++) {

		SetConsoleCursorPosition(hConsole, position);
		std::cout << sprite[i] << std::endl;
		position.Y++;
	}
}


struct Point {
	int x;
	int y;
};

#define GRAVITY -9.8
#define PI 3.14159265
double DegToRad(double degres)
{
	return (degres * PI) / 180;
}

double MaxHeight(double initSpeed, double directionAngle)
{
	return abs((pow(initSpeed, 2.0) *  pow(sin(DegToRad(directionAngle)), 2.0)) / (2.0 * GRAVITY));
}

double MaxDistance(double initSpeed, double directionAngle)
{
	return abs(((pow(initSpeed, 2.0)*pow(sin(DegToRad(directionAngle)), 2.0)) / GRAVITY));
}

double PositionXInTime(double inTime, double speed, double directionAngle, double initXValue = 0)
{
	return initXValue + (speed * inTime * cos(DegToRad(directionAngle)));
}

double PositionYInTime(double inTime, double speed, double directionAngle, double initYValue = 0)
{
	return initYValue + (speed * inTime * sin(DegToRad(directionAngle))) - ((GRAVITY * pow(inTime, 2)) * 0.5);
}

double TimeToHitMaxHeight(double speed, double directionAngle)
{
	return abs(speed * sin(DegToRad(directionAngle)) / GRAVITY);
}

double TimeToHitMaxDistance(double speed, double directionAngle)
{
	return abs(2 * speed * sin(DegToRad(directionAngle)) / GRAVITY);
}

void CPP_TEST()
{
	//TODO: absolute value from results
	std::cout << MaxHeight(10.0, 45.0) << std::endl; //2.5
	std::cout << MaxDistance(10.0, 45.0) << std::endl; //5.10

	//Time is default 1s
	std::cout << PositionXInTime(1.0, 10.0, 45.0) << std::endl; //?? //2.62 (half from MaxDistance) 
	std::cout << PositionYInTime(1.0, 10.0, 45.0) << std::endl; //??

	std::cout << TimeToHitMaxHeight(10.0, 45.0) << std::endl; //?? 
	std::cout << TimeToHitMaxDistance(10.0, 45.0) << std::endl; //?? 

	std::cout << "Projectile Test" << std::endl;
	std::cout << MaxDistance(10.0, 45.0) << std::endl; //5.10
	std::cout << MaxDistance(10.0, 55.0) << std::endl; //5.10
	std::cout << MaxDistance(10.0, 65.0) << std::endl; //5.10

	//std::string* tank1 = getFileContentsArr_Path("src/Sprites/File.txt", 3);
	//std::string* tank2 = getFileContentsArr_Path("src/Sprites/File2.txt", 3);

	//std::string* explosion_1 = getFileContentsArr_Path("src/Sprites/Explosion_1.txt", 4);
	//std::string* explosion_2 = getFileContentsArr_Path("src/Sprites/Explosion_2.txt", 4);
	//std::string* explosion_3 = getFileContentsArr_Path("src/Sprites/Explosion_3.txt", 4);

	//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	//COORD tank1Coord, tank2Coord;
	//tank1Coord.X = 10; 
	//tank1Coord.Y = 22;

	//tank2Coord.X = 50;
	//tank2Coord.Y = 22;

	//Draw(hConsole, tank1Coord, tank1, 3);
	//Sleep(1000);
	//std::system("cls");

	////while (true)
	////{
	////	Draw(hConsole, tank1Coord, tank1, 3);
	////	Sleep(1000);
	////	std::system("cls");
	////	Draw(hConsole, tank1Coord, explosion_1, 4);
	////	Sleep(100);
	////	std::system("cls");
	////	Draw(hConsole, tank1Coord, explosion_2, 4);
	////	Sleep(100);
	////	std::system("cls");
	////	Draw(hConsole, tank1Coord, explosion_3, 4);
	////	Sleep(100);
	////	std::system("cls");
	////	Sleep(100);

	////	//Sleep(500);
	////	//std::system("cls");
	////	//Draw(hConsole, tank1Coord, tank1,3);
	////	//Draw(hConsole, tank2Coord, tank2,3);
	////	//tank1Coord.X++;
	////	//tank2Coord.X--;
	////}
}

void Lua_Test()
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	luaopen_debug(L);

	Lua_Init_GameObject(L);
	Lua_Init_Sprite(L);
	Lua_Init_Console(L);
	
	int lua_source = luaL_dofile(L, "src/LuaScripts/LuaScript.lua");
	if (IsLuaValid(L, lua_source))
	{


	}


	lua_close(L);
}

int main() 
{
	CPP_TEST();
	//Lua_Test();
	
	return 0;
}