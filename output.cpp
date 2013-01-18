///////////////////////////////////////////////////////////////////////////////
// Author: Steven Lamerton
// Copyright: 2013 Steven Lamerton
// License: MIT, see LICENSE
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <iostream>
#include <fstream>

#include "output.h"
#include "dla.h"

void to_pbm(std::vector<std::vector<cell>> grid, std::string name)
{
    std::ofstream out;
    out.open(name + ".pbm");

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

void to_ppm(const std::vector<std::vector<cell>> &grid,
            const std::string &name)
{
    std::ofstream out;
    out.open(name + ".ppm");

    out << "P3\n";
    out << grid.size() << " " << grid.size() << "\n";
    out << "255\n";

    for(auto i : grid)
    {
        for(auto j : i)
        {
            out << j.age % 256 << " "
                << (j.age / 256) % 256 << " "
                << (j.age / 65536) % 256 << "\n";
        }
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

