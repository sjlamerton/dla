///////////////////////////////////////////////////////////////////////////////
// Author: Steven Lamerton
// Copyright: 2013 Steven Lamerton
// License: MIT, see LICENSE
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <iostream>
#include <fstream>

#include <png.h>

#include "output.h"
#include "dla.h"

rgb get_colour(int age)
{
    rgb ret;
    // Scale the output to give a smoother gradient
    double h = (age % 36000) / 6000.0, i, f, r, g, b;

    f = std::modf(h, &i);

    if(age == 0)
    {
        ret.r = 0; ret.g = 0; ret.b = 0;
        return ret;
    }
    
    // Perform a hsv -> rgb conversion with v = s = 1
    if(i == 0) { r = 1; g = f; b = 0; }
    if(i == 1) { r = 1 - f; g = 1; b = 0; }
    if(i == 2) { r = 0; g = 1; b = f; }
    if(i == 3) { r = 0; g = 1 - f; b = 1; }
    if(i == 4) { r = f; g = 0; b = 1; }
    if(i == 5) { r = 1; g = 0; b = 1 - f; }

    // Scale the output to 8 byte triplet
    ret.r = r * 255; ret.g = g * 255;
    ret.b = b * 255;

    return ret;
}

void to_png(const std::vector<std::vector<cell>> &grid,
            const std::string &name, int radius)
{
    FILE* file;
    png_structp write_struct;
    png_infop info_struct;
    std::vector<unsigned char> data;
    std::string fullname = name;
    fullname += ".png";
    const int N = grid.size();

    file = fopen(fullname.c_str(), "wb");
    if(!file)
        goto finish;

    write_struct = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, 
                                           NULL);
    if(!write_struct)
        goto finish;

    info_struct = png_create_info_struct(write_struct);

    if(!info_struct)
        goto finish;

    if(setjmp(png_jmpbuf(write_struct)))
        goto finish;

    png_init_io(write_struct, file);

    // We write in  8 byte RGB format
    png_set_IHDR(write_struct, info_struct, 2 * radius, 2 * radius, 8,
                 PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(write_struct, info_struct);
   
    for(int i = N/2 - radius; i < N/2 + radius; i++)
    {
        data.clear();
        for(int j = N/2 - radius; j < N/2 + radius; j++)
        {
            rgb val = get_colour(grid[i][j].age);
            data.push_back(val.r);
            data.push_back(val.g);
            data.push_back(val.b);
        }
        png_write_row(write_struct, data.data());
    }
    png_write_end(write_struct, NULL);

finish:
    if(file) 
        fclose(file);
    if(info_struct)
        png_free_data(write_struct, info_struct, PNG_FREE_ALL, -1);
    if(write_struct)
        png_destroy_write_struct(&write_struct, NULL);
}

void to_screen(const std::vector<std::vector<cell>> &grid)
{
    for(auto i : grid)
    {
        for(auto j : i)
        {
            if(j.particle)
                std::cout << j.particle;
            else
                std::cout << " ";
        }
        std::cout << std::endl;
    }
}

