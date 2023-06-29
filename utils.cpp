#include "utils.hpp"

int clamp(int x, int low, int high)
{
    if (x < low) {return low;}
    else if (x > high) {return high;}
    else{ return x; }
}
