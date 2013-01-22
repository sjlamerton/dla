///////////////////////////////////////////////////////////////////////////////
// Author: Steven Lamerton
// Copyright: 2013 Steven Lamerton
// License: MIT, see LICENSE
///////////////////////////////////////////////////////////////////////////////

#ifndef _DNL_H_
#define _DNL_H_

#include <cmath>
#include <chrono>

struct cell
{
    bool particle;
    int age;
};

constexpr double pi()
{
    return 4 * std::atan(1);
}

typedef std::pair<int, int> position;
typedef std::chrono::high_resolution_clock hr_clock;
typedef std::chrono::milliseconds milliseconds;

void updateposition(position &pos, int direction);

#endif

