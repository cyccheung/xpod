#include "Arena.h"

//Default constructor creates 9x6 arena
Arena::Arena()
    : length(9), width(6) {}

//Custom constructor creates specified arena
Arena::Arena(const int lengthIn, const int widthIn)
    : length(lengthIn), width(widthIn) {}
