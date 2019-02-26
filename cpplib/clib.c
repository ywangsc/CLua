//gcc -fPIC -dynamiclib -Wl,-undefined,dynamic_lookup -L. -lcppwrapper -o clib.so clib.c
//here -undefined,dynamic_lookup is for dynamic linking to lua library
//
#include "cppwrapper.h" 
#include <math.h>

#include <lua.h>                           
#include <lauxlib.h>                            
#include <lualib.h>  

static int sayHi(lua_State *L){              
    float numId = lua_tonumber(L, -1);      
    lua_pushnumber(L, sqrt(numId));   
    WANG_sayHi();         
    return 1;                               
}
static int icube(lua_State *L){                
    float rtrn = lua_tonumber(L, -1);        
    lua_pushnumber(L,rtrn*rtrn*rtrn);      
    return 1;                             
} 

int luaopen_clib(lua_State *L){ 
    lua_register(L,"sayHi",sayHi);
    lua_register(L,"cube",icube);
    return 1;
}