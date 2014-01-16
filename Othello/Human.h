#ifndef Human_h
#define Human_h

#include "GlobalAndIncludes.h"

class Human{
private:
    int color;
    
public:
	Human(int c = WHITE) { color = c; }
	virtual ~Human() { };
    int getColor() { return color; }
    void setColor(int c) { color = c; }
};

#endif