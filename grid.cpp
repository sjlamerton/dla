#include <iostream>

#include <png.h>

#include "grid.h"
#include "output.h"

point_grid::point_grid(int size) : N(size), kR(100), sR(25), angleDist(0, 6.28),
                                   count(0), maxR(1), 
                                   grid(size, std::vector<int>(size))
{
    // Set the central point
    grid[N/2][N/2] = 1;
}

std::pair<int, int> point_grid::get_start()
{
    double angle = angleDist(engine);

    return std::make_pair(static_cast<int>(sR * std::cos(angle) + N/2),
                          static_cast<int>(sR * std::sin(angle) + N/2));
}

bool point_grid::should_kill(std::pair<int, int> p)
{
    int x = N/2 - p.first;
    int y = N/2 - p.second;
    int radius = static_cast<int>(std::sqrt(x * x + y * y));

    // Kill the particle if it strays too near the edge
    return radius >= kR;
}

bool point_grid::should_stick(std::pair<int, int> p)
{
    int x = N/2 - p.first;
    int y = N/2 - p.second;
    int radius = static_cast<int>(std::sqrt(x * x + y * y));

    // Only check if we are near the fractal
    if(radius >= maxR + 5)
        return false;

    // Fix particle if needed
    if(grid[p.second - 1][p.first]
    || grid[p.second + 1][p.first]
    || grid[p.second][p.first - 1]
    || grid[p.second][p.first + 1]
    || grid[p.second - 1][p.first - 1]
    || grid[p.second + 1][p.first + 1]
    || grid[p.second + 1][p.first - 1]
    || grid[p.second - 1][p.first + 1])
    {
        count++;
        grid[p.second][p.first] = count;
        maxR = std::max(maxR, radius);

        // Extend the kill radius if needed
        if(kR <= sR + 100)
        {
            kR = std::min(N/2 - 1, kR + 100);
            if(kR != N/2 -1)
                std::cout << "Expanding kR: " << kR << std::endl;
        }

        // Extend the starting radius if needed
        if(maxR >= sR - 50)
        {
            if(sR != kR)
            {
                sR = std::min(kR, sR + 100);
                std::cout << "Expanding sR: " << sR << std::endl;
            }
        }
        return true;
    }
    return false;
}

void point_grid::to_png(const std::string &filename)
{
    FILE* file;
    png_structp write_struct;
    png_infop info_struct;
    std::vector<unsigned char> data;
    std::string fullname = filename;
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
    png_set_IHDR(write_struct, info_struct, 2 * maxR, 2 * maxR, 8,
                 PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(write_struct, info_struct);
   
    for(int i = N/2 - maxR; i < N/2 + maxR; i++)
    {
        data.clear();
        for(int j = N/2 - maxR; j < N/2 + maxR; j++)
        {
            rgb val = get_colour(grid[i][j]);
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
