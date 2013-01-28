dla
===

dla is a simple diffusion limited aggregation simulator. It is written in C++11
and licensed under the MIT License. See LICENSE for more details.

Usage
-----

Options:
  -h [ --help ]                   Prints the help message
  -s [ --seed ] arg (=0)          RNG seed
  -n [ --size ] arg (=500)        Grid size
  -p [ --particles ] arg (=15000) Particle count
  -o [ --output ] arg (=output)   Output name

After running dla will output a png image of the generated fractal, using the
name specified on the command line if available. If the size of the grid is 
small then the fractal will also be output to screen.

Note that particles may be killed if they drift too far from the fractal and so
the final number in the fractal will likely be significantly less than the 
specified particle count.

