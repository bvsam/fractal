# fractal

Visualizing fractals using C++ and SFML.

## Running

Controls:

- **A** - zoom in
- **E** - zoom out

## Building

### Locally

Note: Building the code locally requires both [SFML](https://www.sfml-dev.org/) and [CMake](https://cmake.org/) to be installed. The following instructions are meant for Linux/WSL.

To build and run the code, do the following:

1. Make a `build` directory and cd into it

```bash
mkdir build
cd build
```

2. While in the `build` directory, run `cmake` with the `CMakeLists.txt` in the root directory of this repo.

```bash
cmake ..
```

3. Run make

```bash
make
```

4. Run the generated binary

```
./fractal
```

## References and Attribution

- [_Understanding Julia and Mandelbrot Sets_](https://www.karlsims.com/julia.html) by _Karl Sims_
- [_Simple Fractal Rendering_](https://youtu.be/uc2yok_pLV4) by _Pezzza's Work_
- [_From Newton’s method to Newton’s fractal (which Newton knew nothing about)_](https://youtu.be/-RdOwhmqP5s) by _3Blue1Brown_
  - idea inspiration
