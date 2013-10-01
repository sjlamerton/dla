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

class grid_base
{
public:
    virtual std::pair<int, int> get_start() = 0;
    virtual bool should_kill(std::pair<int, int> p) = 0;
    virtual bool should_stick(std::pair<int, int> p) = 0;
    virtual int get_count() = 0;
    virtual void to_png(const std::string &filename) = 0;
};

class vector_grid : public grid_base
{
public:
    vector_grid(int size);
    virtual std::pair<int, int> get_start() = 0;
    virtual bool should_kill(std::pair<int, int> p) = 0;
    virtual bool should_stick(std::pair<int, int> p);
    virtual void to_png(const std::string &filename);
    virtual int get_count() { return count; }

protected:
    std::vector<std::vector<int>> grid;
    int N, count;
};

class point_vector_grid : public vector_grid
{
public:
    point_vector_grid(int size);
    virtual std::pair<int, int> get_start();
    virtual bool should_kill(std::pair<int, int> p);
    virtual bool should_stick(std::pair<int, int> p);
    virtual int get_radius() {return maxR; }

private:
    int sR, kR, maxR;
    // Random number generation
    boost::taus88 engine;
    std::uniform_real_distribution<double> angleDist;
};

class line_vector_grid : public vector_grid
{
public:
    line_vector_grid(int size);
    virtual std::pair<int, int> get_start();
    virtual bool should_kill(std::pair<int, int> p);
    virtual bool should_stick(std::pair<int, int> p);
    virtual int get_radius() {return maxR; }

private:
    int sR, kR, maxR;
    // Random number generation
    boost::taus88 engine;
    std::uniform_int_distribution<int> dist;
};

#endif

