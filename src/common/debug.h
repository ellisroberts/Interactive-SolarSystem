#pragma once

#ifdef DEBUG_BUILD
#include <iostream>
#include <string>
#endif

#ifdef DEBUG_BUILD
#define DebugPrint(out) std::cout << out << std::endl
#else
#define DebugPrint(out) ((void) 0)
#endif 
