#ifndef GlobalAndIncludes_h
#define GlobalAndIncludes_h

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <string>
#include <sstream>
#include <set>
#include <vector>

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;
const int BLACK = 1;
const int WHITE = 2;
const int VALID = 3;
const int BLANK = 0;
const pair<int,int> corner1 = make_pair(0,0);
const pair<int,int> corner2 = make_pair(0,7);
const pair<int,int> corner3 = make_pair(7,0);
const pair<int,int> corner4 = make_pair(7,7);

const pair<int, int> adjMovs[8] = {make_pair(-1, 0), make_pair(-1, 1),
    make_pair(0 , 1), make_pair(1 , 1), make_pair(1 , 0), make_pair(1 , -1),
    make_pair(0, -1), make_pair(-1, -1)};

#endif