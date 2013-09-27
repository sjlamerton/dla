///////////////////////////////////////////////////////////////////////////////
// Author: Steven Lamerton
// Copyright: 2013 Steven Lamerton
// License: MIT, see LICENSE
///////////////////////////////////////////////////////////////////////////////

#ifndef _GRID_H_
#define _GRID_H_

#include <utility>
#include <vector>
#include <random>
#include <boost/random/taus88.hpp>

class grid
{
public:
    virtual std::pair<int, int> get_start() = 0;
    virtual bool should_kill(std::pair<int, int> p) = 0;
    virtual bool should_stick(std::pair<int, int> p) = 0;
    virtual int get_count() = 0;
    virtual void to_png(const std::string &filename) = 0;
};

class point_grid
{
public:
    point_grid(int size);
    virtual std::pair<int, int> get_start();
    virtual bool should_kill(std::pair<int, int> p);
    virtual bool should_stick(std::pair<int, int> p);
    virtual void to_png(const std::string &filename);

    virtual int get_count() { return count; }
    virtual int get_radius() {return maxR; }


private:
    std::vector<std::vector<int>> grid;
    int N, sR, kR, maxR, count;
    // Random number generation
    boost::taus88 engine;
    std::uniform_real_distribution<double> angleDist;
};

#endif

