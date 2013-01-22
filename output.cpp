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

void to_pbm(const std::vector<std::vector<cell>> &grid,
            const std::string &name)
{
    std::ofstream out;
    out.open(name + ".pbm");

    out << "P1\n";
    out << grid.size() << " " << grid.size() << "\n";

    for(auto i : grid)
    {
        for(auto j : i)
        {
            out << j.particle;
        }
        out << "\n";
    }

    out.close();
}

void to_ppm(const std::vector<std::vector<cell>> &grid,
            const std::string &name)
{
    std::ofstream out;
    out.open(name + ".ppm");

    out << "P3\n";
    out << grid.size() << " " << grid.size() << "\n";
    out << "255\n";

    for(auto i : grid)
    {
        for(auto j : i)
        {
            out << j.age % 256 << " "
                << (j.age / 256) % 256 << " "
                << (j.age / 65536) % 256 << "\n";
        }
    }
    out.close();
}

void to_png(const std::vector<std::vector<cell>> &grid,
            const std::string &name)
{
    FILE* file;
    png_structp write_struct;
    png_infop info_struct;
    std::vector<unsigned char> data;
    std::string fullname = name + ".png";

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
    png_set_IHDR(write_struct, info_struct, grid.size(), grid.size(), 8,
                 PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(write_struct, info_struct);
    
    for(auto i : grid)
    {
        data.clear();
        for(auto j : i)
        {
            data.push_back(static_cast<unsigned char>(j.age % 256));
            data.push_back(static_cast<unsigned char>((j.age / 256) % 256));
            data.push_back(static_cast<unsigned char>((j.age / 65536) % 256));
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

