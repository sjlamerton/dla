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
#include "grid.h"
#include "particle_inserter.h"

int main(int argc, char** argv)
{
    // Parse the commad line arguments
    boost::program_options::variables_map options;
    
    if(!parse_options(argc, argv, options))
        return EXIT_FAILURE;
    
    // Various constants
    int N = options["size"].as<int>();
    int P = options["particles"].as<int>();

    // Random number generation
    boost::taus88 engine;
    boost::uniform_smallint<int> dirdist(0, 7);

    engine.seed(options["seed"].as<int>());
   
    // Start our timing
    hr_clock::time_point start = hr_clock::now(); 

    point_grid grid(N);
    particle_inserter ins(P, &grid);

    ins();

    hr_clock::time_point calc = hr_clock::now();

    grid.to_png(options["output"].as<std::string>());

    hr_clock::time_point io = hr_clock::now();

    std::cout << std::endl;
    std::cout << "Fixed particle count: " << grid.get_count() << std::endl;
    std::cout << "Maximum radius: " << grid.get_radius() << std::endl;
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
