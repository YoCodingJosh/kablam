project('kablam', 'cpp')

files = [
  'Game.cpp',
  'Game.hpp',
  'Main.cpp',
  'Menu.cpp',
  'Menu.hpp',
  'Assets.cpp',
  'Assets.hpp',
  'FPSLimiter.cpp',
  'FPSLimiter.hpp',
  'Gameplay.cpp',
  'Gameplay.hpp',
  'Utility.cpp',
  'Utility.hpp',
  'Timer.cpp',
  'Timer.hpp',
  'Animation.cpp',
  'Animation.hpp',
  'BadGuy.cpp',
  'BadGuy.hpp',
  'Bomb.cpp',
  'Bomb.hpp',
  'PauseScreen.cpp',
  'PauseScreen.hpp',
]

# Custom command to copy assets
copy = find_program(meson.current_source_dir() / 'copy-assets.py')
assets_dir = meson.current_source_dir() / 'assets'
assets_dest = meson.current_build_dir() / 'assets'
run_command(copy, assets_dir, assets_dest)

# Emscripten dependencies
if meson.is_cross_build()
  sdl2_dep = dependency('sdl2', method: 'pkg-config', required: false)
  sdl2_image_dep = dependency('sdl2_image', method: 'pkg-config', required: false)
  sdl2_ttf_dep = dependency('sdl2_ttf', method: 'pkg-config', required: false)
  sdl2_mixer_dep = dependency('sdl2_mixer', method: 'pkg-config', required: false)
  dependencies = [sdl2_dep, sdl2_image_dep, sdl2_ttf_dep, sdl2_mixer_dep]

  emscripten_args = [
    '-s', 'USE_SDL=2',
    '-s', 'USE_SDL_IMAGE=2',
    '-s', 'USE_SDL_TTF=2',
    '-s', 'USE_SDL_MIXER=2',
    '-s', 'USE_FREETYPE=1',
    '-s', 'USE_HARFBUZZ=1',
  ]

  emscripten_link_args = [
    '-s', 'USE_SDL=2',
    '-s', 'USE_SDL_IMAGE=2',
    '-s', 'USE_SDL_TTF=2',
    '-s', 'USE_SDL_MIXER=2',
    '-s', 'USE_FREETYPE=1',
    '-s', 'USE_HARFBUZZ=1',
    '-s', 'SDL2_IMAGE_FORMATS=["png"]',
    '-o', 'kablam.html',
  ]
else
  sdl2_dep = dependency('sdl2')
  sdl2_image_dep = dependency('sdl2_image')
  sdl2_ttf_dep = dependency('sdl2_ttf')
  sdl2_mixer_dep = dependency('sdl2_mixer')
  dependencies = [sdl2_dep, sdl2_image_dep, sdl2_ttf_dep, sdl2_mixer_dep]
  emscripten_args = []
  emscripten_link_args = []
endif

executable(
  'kablam',
  files,
  dependencies: dependencies,
  override_options: ['cpp_std=c++20'],
  cpp_args: emscripten_args,
  link_args: emscripten_link_args,
)
