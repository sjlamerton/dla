///////////////////////////////////////////////////////////////////////////////
// Author: Steven Lamerton
// Copyright: 2013 Steven Lamerton
// License: MIT, see LICENSE
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <iostream>
#include <fstream>

#include <png.h>

#include "output.h"
#include "dla.h"

rgb get_colour(int age)
{
    rgb ret;
    // Scale the output to give a smoother gradient
    double h = (age % 36000) / 6000.0, i, f, r, g, b;

    f = std::modf(h, &i);

    if(age == 0)
    {
        ret.r = 0; ret.g = 0; ret.b = 0;
        return ret;
    }
    
    // Perform a hsv -> rgb conversion with v = s = 1
    if(i == 0) { r = 1; g = f; b = 0; }
    if(i == 1) { r = 1 - f; g = 1; b = 0; }
    if(i == 2) { r = 0; g = 1; b = f; }
    if(i == 3) { r = 0; g = 1 - f; b = 1; }
    if(i == 4) { r = f; g = 0; b = 1; }
    if(i == 5) { r = 1; g = 0; b = 1 - f; }

    // Scale the output to 8 byte triplet
    ret.r = static_cast<int>(r * 255);
    ret.g = static_cast<int>(g * 255);
    ret.b = static_cast<int>(b * 255);

    return ret;
}
