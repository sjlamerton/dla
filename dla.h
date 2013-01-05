///////////////////////////////////////////////////////////////////////////////
// Author: Steven Lamerton
// Copyright: 2013 Steven Lamerton
// License: MIT, see LICENSE
///////////////////////////////////////////////////////////////////////////////

#ifndef _DNL_H_
#define _DNL_H_

#include <cmath>

struct cell
{
    bool particle;
};

constexpr double pi()
{
    return 4 * std::atan(1);
}

void updateposition(std::pair<int, int> &pos, int direction);

#endif

