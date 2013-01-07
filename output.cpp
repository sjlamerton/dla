///////////////////////////////////////////////////////////////////////////////
// Author: Steven Lamerton
// Copyright: 2013 Steven Lamerton
// License: MIT, see LICENSE
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <iostream>
#include <fstream>

#include "dla.h"

void to_pbm(std::vector<std::vector<cell>> grid)
{
    std::ofstream out;
    out.open("out.pbm");
    
    out << "P1\n";
    out << grid.size() << " " << grid.size() << "\n";

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

void to_screen(std::vector<std::vector<cell>> grid)
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
