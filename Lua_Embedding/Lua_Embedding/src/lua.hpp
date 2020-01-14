//lua.hpp
//Lua header files for C++
//<<extern "C">> not suppied automatically because Lua also compiles as C++
extern "C"
{
#include "../Lua535/include/lua.h"
#include "../Lua535/include/lauxlib.h"
#include "../Lua535/include/lualib.h"
}
