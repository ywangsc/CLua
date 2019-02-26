//
//  main.c
//  C2Lua
//
//  Created by Yingying Wang on 8/21/18.
//  Copyright © 2018 Yingying Wang. All rights reserved.
//

#include <stdio.h>

#include <lua.h>                               /* Always include this */
#include <lauxlib.h>                           /* Always include this */
#include <lualib.h>                            /* Always include this */

static int isquare(lua_State *L){              /* Internal name of func */
    float rtrn = lua_tonumber(L, -1);      /* Get the single number arg */
    //printf("Top of square(), nbr=%f\n",rtrn);
    lua_pushnumber(L,rtrn*rtrn);           /* Push the return */
    return 1;                              /* One return value */
}
static int icube(lua_State *L){                /* Internal name of func */
    float rtrn = lua_tonumber(L, -1);      /* Get the single number arg */
    //printf("Top of cube(), number=%f\n",rtrn);
    lua_pushnumber(L,rtrn*rtrn*rtrn);      /* Push the return */
    return 1;                              /* One return value */
}

static const struct luaL_Reg testlib[] = {
    {"square", isquare},
    {"cube",icube},
    {NULL, NULL}
};
static int dub(lua_State *L) {
    const double a = lua_tonumber(L, 1);
    lua_pushnumber(L, a*2);
    return 1;
}

int luaopen_gun(lua_State *L){
    lua_pushcfunction(L, dub);
    lua_setglobal(L, "dub");
    
    lua_register(L,"square",isquare);
    lua_register(L,"cube",icube);
    return 1;
}

/* Register this file's functions with the
 * luaopen_libraryname() function, where libraryname
 * is the name of the compiled .so output. In other words
 * it's the filename (but not extension) after the -o
 * in the cc command.
 *
 * So for instance, if your cc command has -o power.so then
 * this function would be called luaopen_power().
 *
 * This function should contain lua_register() commands for
 * each function you want available from Lua.
 *
 */
/*int luaopen_gun(lua_State *L){
    lua_register(L,"square",isquare);
    lua_register(L,"cube",icube);
    printf("shit");
    return 0;
}*/

/*int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}*/
