# CLua
C and Lua Wrapper
nstall lua 5.2

not lua 5.3 to be consistent with Moho

* download lua 5.2
* in terminal, execute the following command

tar zxf lua-5.2.4.tar.gz
cd lua-5.2.4
make macosx test
sudo make macosx install

* check header and lib files' path is: /usr/local/include and /usr/local/lib 
* create c code, include relevant lua header

//main.c THIS IS JUST AN EXAMPLE: exposing square and cube to lua

#include <stdio.h>
#include <lua.h>                           
#include <lauxlib.h>                            
#include <lualib.h>                            

static int isquare(lua_State *L){              
    float rtrn = lua_tonumber(L, -1);      
    lua_pushnumber(L,rtrn*rtrn);            
    return 1;                               
}

static int icube(lua_State *L){                
    float rtrn = lua_tonumber(L, -1);        
    lua_pushnumber(L,rtrn*rtrn*rtrn);      
    return 1;                             
} 

int luaopen_mylib(lua_State *L){ 
    lua_register(L,"square",isquare);
    lua_register(L,"cube",icube);
    return 1;
}

* compile using:  gcc* -fPIC -dynamiclib -Wl,-undefined,dynamic_lookup* -o mylib.so main.c . 
It is very import for mylib.so to dynamically link to lua (MacOSX), so do NOT use: gcc -shared -fPIC -o mylib.so -I/usr/local/include -llua main.c , because it will cause crash in Moho and maybe multiple Lua VMs detected error

* put the mylib.so under /usr/local/lib/lua/5.2/, so that Moho can find it

* In lua script,  

require("mylib") 

print(square(1.414213598))

print(cube(5))



