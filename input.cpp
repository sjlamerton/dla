///////////////////////////////////////////////////////////////////////////////
// Author: Steven Lamerton
// Copyright: 2013 Steven Lamerton
// License: MIT, see LICENSE
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <boost/program_options.hpp>

namespace po = boost::program_options;
    
bool parse_options(int argc, char** argv, po::variables_map &map)
{
    po::options_description desc("Options");
    desc.add_options()
            ("help,h", "Prints this help message")
            ("seed,s", po::value<int>()->default_value(0), "Sets RNG seed")
            ("size,n", po::value<int>()->default_value(1000), "Sets grid size")
            ("particles,p", po::value<int>()->default_value(50000),
                          "Sets particle count")
            ("output,o", po::value<std::string>()->default_value("output"),
                     "Output name");

    po::store(po::parse_command_line(argc, argv, desc), map);
    po::notify(map);
    
    if(map.count("help"))
    {
        std::cout << desc << "\n";
        return false;
    }

    return true;
}

