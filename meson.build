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
]

# copy assets from the assets directory to the build directory by using our custom command `copy_assets`
copy = find_program(meson.current_source_dir() / 'copy-assets.py')
assets_dir = meson.current_source_dir() / 'assets'
assets_dest = meson.current_build_dir() / 'assets'
run_command(copy, assets_dir, assets_dest)

sdl2_dep = dependency('sdl2')
# sdl2_main_dep = dependency('sdl2main')
sdl2_image_dep = dependency('sdl2_image')
sdl2_ttf_dep = dependency('sdl2_ttf')
sdl2_mixer_dep = dependency('sdl2_mixer')

dependencies = [sdl2_dep, sdl2_image_dep, sdl2_ttf_dep, sdl2_mixer_dep]

executable('kablam', files, dependencies: dependencies, gui_app: true, override_options: ['cpp_std=c++20'])
