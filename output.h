///////////////////////////////////////////////////////////////////////////////
// Author: Steven Lamerton
// Copyright: 2013 Steven Lamerton
// License: MIT, see LICENSE
///////////////////////////////////////////////////////////////////////////////

#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include "dla.h"

void to_pbm(const std::vector<std::vector<cell>> &grid,
            const std::string &name);
void to_ppm(const std::vector<std::vector<cell>> &grid,
            const std::string &name);
void to_screen(const std::vector<std::vector<cell>> &grid);

#endif

