///////////////////////////////////////////////////////////////////////////////
// Author: Steven Lamerton
// Copyright: 2013 Steven Lamerton
// License: MIT, see LICENSE
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <chrono>
#include <thread>
#include <boost/program_options.hpp>

#include "dla.h"
#include "input.h"
#include "grid.h"
#include "particle_inserter.h"

int main(int argc, char** argv)
{
    // Parse the commad line arguments
    boost::program_options::variables_map options;
    std::vector<std::thread> threads;
    
    if(!parse_options(argc, argv, options))
        return EXIT_FAILURE;
    
    // Various constants
    int N = options["size"].as<int>();
    int P = options["particles"].as<int>();
    int t = options["threads"].as<int>();

    // Start our timing
    hr_clock::time_point start = hr_clock::now(); 

    line_vector_grid grid(N);

    for(int i = 0; i < t; i++)
        threads.push_back(std::thread(particle_inserter(P/t, &grid)));

    for(int i = 0; i < t; i++)
        threads[i].join();

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
