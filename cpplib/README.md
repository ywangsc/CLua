# Cpp Wrapper Exposed in C for Lua 

* cpplib.h/cpplib.cpp ------------------------------------------------------

This is the cpp library that supposed to the implementation needed for lua

compile use:

g++ -fPIC -shared -o libcppLib.so cpplib.cpp

output: libcppLib.so




* cppwrapper.h/cppwrapper.cpp -----------------------------------------------

This is wrapping the cppLib, expose its C API.

compile use: (still use g++, but the API is in C)

g++ -fPIC -shared -L. -lcppLib -o libcppwrapper.so cppwrapper.cpp

output: libcppwrapper.so




* clib.c -------------------------------------------------------------------

This is the lua API.

compile use: 

gcc -fPIC -dynamiclib -Wl,-undefined,dynamic_lookup -L. -lcppwrapper -o clib.so clib.c

output: clib.so




* In Lua, -------------------------------------------------------------------

require("clib") 

print(sayHi(2));

can call c++ WangClass::sayHi();




* For Moho: ------------------------------------------------------------------

clib.so -> /usr/local/lib/lua/5.2/

libcppwrapper.so -> /usr/local/lib/

libcppLib.so -> /usr/local/lib/
