///////////////////////////////////////////////////////////////////////////////
// Author: Steven Lamerton
// Copyright: 2013 Steven Lamerton
// License: MIT, see LICENSE
///////////////////////////////////////////////////////////////////////////////

#ifndef _PARTICLE_INSERTER_H_
#define _PARTICLE_INSERTER_H_

#include <boost/random/taus88.hpp>
#include <boost/random/uniform_int.hpp>

#include "grid.h"

class particle_inserter
{
public:
    particle_inserter(int count, grid_base *grid);
    void operator()();

private:
    void update_position(std::pair<int, int> &p);

    int count;
    grid_base *grid;
    // Random number generation
    boost::taus88 engine;
    boost::uniform_int<int> dirdist;
};

#endif

