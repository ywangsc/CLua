//gcc -fPIC -dynamiclib -Wl,-undefined,dynamic_lookup -L. -llightningWrapper -o clibLightning.so clibLightning.c 
//here -undefined,dynamic_lookup is for dynamic linking to lua library
//
#include "lightningWrapper.h" 
#include <math.h>

#include <lua.h>                           
#include <lauxlib.h>                            
#include <lualib.h>  

static int lightning(lua_State *L){              
    float numId = lua_tonumber(L, -1);      
    lua_pushnumber(L, sqrt(numId));   
    testcall_lightning();     
    return 1;                               
} 

int luaopen_clibLightning(lua_State *L){ 
    lua_register(L,"wLightning",lightning); 
    return 1;
}