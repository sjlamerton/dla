///////////////////////////////////////////////////////////////////////////////
// Author: Steven Lamerton
// Copyright: 2013 Steven Lamerton
// License: MIT, see LICENSE
///////////////////////////////////////////////////////////////////////////////

#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include <array>
#include <iostream>
#include <fstream>

#include "dla.h"

template<size_t N> void topbm(std::array<std::array<cell, N>, N> grid)
{
    std::ofstream out;
    out.open("out.pbm");
    
    out << "P1\n";
    out << N << " " << N << "\n";

    for(auto i : grid)
    {
        for(auto j : i)
        {
            out << j.particle;
        }
        out << "\n";
    }

    out.close();
}

template<size_t N> void toscreen(std::array<std::array<cell, N>, N> grid)
{
    for(auto i : grid)
    {
        for(auto j : i)
        {
            if(j.particle)
                std::cout << j.particle;
            else
                std::cout << " ";
        }
        std::cout << std::endl;
    }
}

#endif

