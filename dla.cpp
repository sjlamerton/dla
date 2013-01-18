///////////////////////////////////////////////////////////////////////////////
// Author: Steven Lamerton
// Copyright: 2013 Steven Lamerton
// License: MIT, see LICENSE
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <array>
#include <random>
#include <functional>
#include <cmath>
#include <fstream>

#include <boost/program_options.hpp>

#include "dla.h"
#include "output.h"
#include "input.h"

int main(int argc, char** argv)
{
    // Parse the commad line arguments
    boost::program_options::variables_map options;
    
    if(!parse_options(argc, argv, options))
        return EXIT_FAILURE;
    
    // Various constants
    int N = options["size"].as<int>();
    int P = options["particles"].as<int>();
    int kR = N / 2 - 1;
    int sR = 25;
    int maxradius = 1;
    int count = 0;


    // Random number generation
    std::default_random_engine engine;
    std::uniform_int_distribution<int> dirdist(0, 3);
    std::uniform_real_distribution<double> angledist(0, 2 * pi());

    engine.seed(options["seed"].as<int>());
    
    // Set up and default initialise our grid
    std::vector<std::vector<cell>> grid (N, std::vector<cell>(N));

    // Set the central point
    grid[N/2][N/2].particle = true;
    
    
    for(int i = 0; i < P; i++)
    {
        // Generate a new starting position
        double angle = angledist(engine);

        position pos = std::make_pair(sR * std::cos(angle) + N/2,
                                      sR * std::sin(angle) + N/2);

        // Move until we hit the solid mass or are too far away
        while(true)
        {
            updateposition(pos, dirdist(engine));

            int radius = (int) std::sqrt(std::pow(N/2 - pos.second, 2) +
                                         std::pow(N/2 - pos.first, 2));

            // Kill the particle if it stays too near the edge
            if(radius >= kR)
                break;

            // Fix particle if needed
            if(grid[pos.second - 1][pos.first].particle == true
                    || grid[pos.second + 1][pos.first].particle == true
                    || grid[pos.second][pos.first - 1].particle == true
                    || grid[pos.second][pos.first + 1].particle == true)
            {
                count++;
                grid[pos.second][pos.first].particle = true;
                grid[pos.second][pos.first].age = count;
                maxradius = std::max(maxradius, radius);
                break;
            }
        }

        // Extend the starting radius if needed
        if(maxradius >= sR - 20)
        {
            if(sR == kR)
            {
                std::cout << "sR == kR, stopping" << std::endl;
                break;
            }

            sR = std::min(kR, sR + 20);
            std::cout << "Expanding the starting radius: " << sR << std::endl;
        }

    }

    // Print the grid to screen if it is small enough
    if(N <= 100)
        to_screen(grid);

    to_ppm(grid, options["output"].as<std::string>());

    std::cout << std::endl;
    std::cout << "Particle count: " << count << std::endl;
    std::cout << "Maximum radius: " << maxradius << std::endl;
}

void updateposition(position &pos, int direction)
{
    switch(direction)
    {
        case 0:
            pos.second--;
            break;
        case 1:
            pos.first++;
            break;
        case 2:
            pos.second++;
            break;
        case 3:
            pos.first--;
            break;
    }
}

