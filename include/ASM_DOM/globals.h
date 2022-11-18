#ifndef globals_h
#define globals_h
#define html(a) (a)
#include <string>
#include "config.h"

extern int i;
extern std::string page;

void render();

bool direct(std::string pageN);

#endif