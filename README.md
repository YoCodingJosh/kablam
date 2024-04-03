# kablam

A fun and exciting game!

## Build Instructions

### Windows

Have Visual Studio 2022 installed along with the C++ development tools.

Download and set up [vcpkg](https://learn.microsoft.com/en-us/vcpkg/get_started/overview), then install the following libraries:

* sdl2
* sdl2-ttf
* sdl2-mixer
* sdl2-image

This may take a hot minute to build.

Once you do that, then open the solution/project in Visual Studio and build. Easy peasy!

### Mac/Linux

Install your compiler (clang/clang++ for macOS, gcc/g++ for Linux).

Install from your package manager (Homebrew for macOS, and whatever apt/yum for Linux):

* `python3`
* `meson`
* `pkg-config`
* `ninja`
  * on Linux this would be `ninja-build`
* `cmake`
* `sdl2`
  * on Linux this would be `libsdl2-dev`
* `sdl2-ttf`
  * on Linux this would be `libsdl2-ttf-dev`
* `sdl2-mixer`
  * on Linux this would be `libsdl2-mixer-dev`
* `sdl2-image`
  * on Linux this would be `libsdl2-image-dev`

Some systems you may have to install:
  * `libogg-dev`
  * `libvorbis-dev`

Once you have that installed, run `meson builddir` then `cd builddir` and then `ninja`. Somewhat easy peasy!
