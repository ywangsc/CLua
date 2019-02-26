//THIS IS TRYING TO LINK DIRECTLY TO cppLib, DOESNT WORK!!!
//gcc -fPIC -dynamiclib -Wl,-undefined,dynamic_lookup -lstdc++ -L. -lcppLib -o clib.so clib2.c
//here -undefined,dynamic_lookup is for dynamic linking to lua library
// 
#include <lua.h>                           
#include <lauxlib.h>                            
#include <lualib.h>  
 


#include "cpplib.h"

	void WANG_sayHi() { 
		WangClass wc; 
    	wc.sayHi();
	} 

	static int sayHi(lua_State *L){              
    	//float rtrn = lua_tonumber(L, -1);      
    	//lua_pushnumber(L,rtrn*rtrn);   
    	//WANG_sayHi();         
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