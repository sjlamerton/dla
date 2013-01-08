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

typedef std::pair<int, int> position;

void updateposition(position &pos, int direction);

#endif

