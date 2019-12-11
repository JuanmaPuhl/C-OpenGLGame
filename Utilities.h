#ifndef UTILITIES_H_
#define UTILITIES_H_
#include "Debug.h"
#include "FileManager.h"
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))
extern Debug debug;
extern FileManager fileManager;
#endif
