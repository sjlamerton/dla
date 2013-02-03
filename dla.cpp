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
#include <chrono>

#include <boost/program_options.hpp>
#include <boost/random/taus88.hpp>
#include <boost/random/uniform_smallint.hpp>

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
    int kR = 100;
    int sR = 25;
    int maxradius = 1;
    int count = 0;


    // Random number generation
    boost::taus88 engine;
    boost::uniform_smallint<int> dirdist(0, 3);
    std::uniform_real_distribution<double> angledist(0, 2 * pi());

    engine.seed(options["seed"].as<int>());
   
    // Start our timing
    hr_clock::time_point start = hr_clock::now(); 

    // Set up and default initialise our grid
    std::vector<std::vector<cell>> grid (N, std::vector<cell>(N));

    // Set the central point
    grid[N/2][N/2].particle = true;
    
    
    for(int i = 1; i <= P; i++)
    {
        if(i % 10000 == 0)
            std::cout << "Particle count: " << i << std::endl;
        // Generate a new starting position
        double angle = angledist(engine);

        position pos = std::make_pair(sR * std::cos(angle) + N/2,
                                      sR * std::sin(angle) + N/2);

        // Move until we hit the solid mass or are too far away
        while(true)
        {
            updateposition(pos, dirdist(engine));

            int x = N/2 - pos.first;
            int y = N/2 - pos.second;
            int radius = (int) std::sqrt(x * x + y * y);

            // Kill the particle if it stays too near the edge
            if(radius >= kR)
                break;

            // Only check if we are near the fractal
            if(radius >= maxradius + 5)
                continue;

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

        if(kR <= sR + 100)
        {
            kR = std::min(N/2 - 1, kR + 100);
            if(kR != N/2 -1)
            std::cout << "Expanding kR: " << kR << std::endl;
        }

        // Extend the starting radius if needed
        if(maxradius >= sR - 50)
        {
            if(sR == kR)
            {
                std::cout << "sR == kR, stopping" << std::endl;
                break;
            }

            sR = std::min(kR, sR + 100);
            std::cout << "Expanding sR: " << sR << std::endl;
        }

    }

    hr_clock::time_point calc = hr_clock::now();

    // Print the grid to screen if it is small enough
    if(N <= 100)
        to_screen(grid);

    to_png(grid, options["output"].as<std::string>());

    hr_clock::time_point io = hr_clock::now();

    std::cout << std::endl;
    std::cout << "Fixed particle count: " << count << std::endl;
    std::cout << "Maximum radius: " << maxradius << std::endl;
    std::cout << "Calculation time: " 
              << std::chrono::duration_cast<milliseconds>(calc - start).count()
              << "ms\n";
    std::cout << "IO time: " 
              << std::chrono::duration_cast<milliseconds>(io - calc).count()
              << "ms\n";
    std::cout << "Total time: " 
              << std::chrono::duration_cast<milliseconds>(io - start).count()
              << "ms\n";
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

