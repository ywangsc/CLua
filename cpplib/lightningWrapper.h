//g++ -fPIC -shared -L./wsvgBuilder -lsvgBuilder -o libLightningWrapper.so lightningWrapper.cpp

#ifndef WANG_C_WRAPPER_H 
#define WANG_C_WRAPPER_H 

#include "wsvgBuilder/wangyiMoho.h"

#ifdef __cplusplus
extern "C" {
#endif

void testcall_lightning();

#ifdef __cplusplus
}
#endif


#endif