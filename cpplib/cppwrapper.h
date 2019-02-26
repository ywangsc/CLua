//g++ -fPIC -dynamiclib -L. -lcppLib -o libcppwrapper.so cppwrapper.cpp
//g++ -fPIC -shared -L. -lcppLib -o libcppwrapper.so cppwrapper.cpp

#ifndef WANG_C_WRAPPER_H 
#define WANG_C_WRAPPER_H 

#ifdef __cplusplus
extern "C" {
#endif

void WANG_sayHi();

#ifdef __cplusplus
}
#endif


#endif