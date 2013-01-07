///////////////////////////////////////////////////////////////////////////////
// Author: Steven Lamerton
// Copyright: 2013 Steven Lamerton
// License: MIT, see LICENSE
///////////////////////////////////////////////////////////////////////////////

#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include "dla.h"

void to_pbm(std::vector<std::vector<cell>> grid, std::string name);
void to_screen(std::vector<std::vector<cell>> grid);

#endif

