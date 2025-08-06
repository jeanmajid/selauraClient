#pragma once
#include <chrono>
#include <string>

#ifdef SELAURA_WINDOWS
#define MCSDK __declspec(dllimport)
#else
#define MCSDK
#endif
