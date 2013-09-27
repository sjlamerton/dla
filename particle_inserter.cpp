///////////////////////////////////////////////////////////////////////////////
// Author: Steven Lamerton
// Copyright: 2013 Steven Lamerton
// License: MIT, see LICENSE
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <boost/random/taus88.hpp>
#include <boost/random/uniform_smallint.hpp>

#include "particle_inserter.h"

particle_inserter::particle_inserter(int count, grid_base *grid) : count(count),
                                                                   grid(grid),
                                                                   dirdist(0, 7)
{}

void particle_inserter::operator()()
{
    for(int i = 1; i <= count; i++)
    {
        if(i % 10000 == 0)
            std::cout << "Particle count: " << i << std::endl;

        // Generate a new starting position
        std::pair<int, int> p = grid->get_start();

        // Move until we hit the solid mass or are too far away
        while(true)
        {
            update_position(p);

            if(grid->should_kill(p))
                break;

            if(grid->should_stick(p))
                break;
        }
        // Maybe have grid.update_radius here
    }
}

void particle_inserter::update_position(std::pair<int, int> &p)
{
    switch(dirdist(engine))
    {
        case 0:
            p.second--;
            break;
        case 1:
            p.first++;
            break;
        case 2:
            p.second++;
            break;
        case 3:
            p.first--;
            break;
        case 4:
            p.first++;
            p.second--;
            break;
        case 5:
            p.first++;
            p.second++;
            break;
        case 6:
            p.first--;
            p.second++;
            break;
        case 7:
            p.first--;
            p.second--;
            break;
    }
}
