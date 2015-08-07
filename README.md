# osu-sampler

_Cooper-Frye freeze-out hypersurface sampler_

## Attribution

I am not the author of this software:
it was written by Chun Shen and Zhi Qiu at The Ohio State University.
They call it "iSS" but I do not find that name to be very descriptive.
Alternate versions may be found at https://github.com/chunshen1987/iSS and https://github.com/chunshen1987/iEBE/tree/Chun_dev/EBE-Node/iSS.
The physics is presented in http://inspirehep.net/record/1319339.

## Usage

Compile and install:

    mkdir build && cd build
    cmake ..
    make install

This will place several files in `<prefix>/sampler`: the compiled binary `sampler`, configuration file `sampler.conf`, directory `tables` containing necessary data, and an empty directory `results`.

Place a hydrodynamic freeze-out hypersurface file in the `sampler` directory as `surface.dat`.
The file must be a plain text file with columns

    tau x y dsigma_t dsigma_x dsigma_y v_x v_y e p T pi00 pi01 pi02 pi11 pi12 pi22 pi33 PI

one row for each hypersurface cell.
Note, this is the format produced by my version of the OSU hydro code [jbernhard/vishnew](https://github.com/jbernhard/vishnew).

Edit the configuration `sampler.conf` as desired, then run `./sampler`.
Particle data will be written in OSCAR1997A format to `oscar.dat`.

## Bulk corrections

I have set the default configuration to ignore bulk viscosity, for a couple reasons:

1. The bulk delta\_f corrections are uncertain, especially at large pT.
   They also appear to have limited impact on pT-integrated quantities, which is what I'm primarily interested in.
2. In this code, the "semi-analytic" algorithm (option `MC_sampling = 2`) is much faster (orders of magnitude) than the "full numerical" algorithm (`MC_sampling = 3`).
   However, the semi-analytic method cannot handle bulk delta\_f corrections.
   In the interest of time, I use the fast method and neglect bulk corrections.
