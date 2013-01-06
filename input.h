///////////////////////////////////////////////////////////////////////////////
// Author: Steven Lamerton
// Copyright: 2013 Steven Lamerton
// License: MIT, see LICENSE
///////////////////////////////////////////////////////////////////////////////

#ifndef _INPUT_H_
#define _INPUT_H_

#include <boost/program_options.hpp>

bool parse_options(int argc, char** argv, 
                   boost::program_options::variables_map &map);

#endif

