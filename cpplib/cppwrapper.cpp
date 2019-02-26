#include <cstdlib>

#include "cppwrapper.h"
#include "cpplib.h"
 

class WangClass;
extern "C" {  
	// Inside this "extern C" block, I can define C functions that are able to call C++ code 

	void WANG_sayHi() {

		WangClass wc; 
    	wc.sayHi();
	} 
} 