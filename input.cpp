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
            ("help", "Prints this help message")
            ("seed", po::value<int>()->default_value(0), "Sets RNG seed")
            ("size", po::value<int>()->default_value(500), "Sets grid size")
            ("particles", po::value<int>()->default_value(15000), 
                          "Sets particle count")
            ("name", po::value<std::string>()->default_value("output"),
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

