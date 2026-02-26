# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/home/vietexa/Desktop/vtquiz/build-web/_deps/sdl3_ttf-src")
  file(MAKE_DIRECTORY "/home/vietexa/Desktop/vtquiz/build-web/_deps/sdl3_ttf-src")
endif()
file(MAKE_DIRECTORY
  "/home/vietexa/Desktop/vtquiz/build-web/_deps/sdl3_ttf-build"
  "/home/vietexa/Desktop/vtquiz/build-web/_deps/sdl3_ttf-subbuild/sdl3_ttf-populate-prefix"
  "/home/vietexa/Desktop/vtquiz/build-web/_deps/sdl3_ttf-subbuild/sdl3_ttf-populate-prefix/tmp"
  "/home/vietexa/Desktop/vtquiz/build-web/_deps/sdl3_ttf-subbuild/sdl3_ttf-populate-prefix/src/sdl3_ttf-populate-stamp"
  "/home/vietexa/Desktop/vtquiz/build-web/_deps/sdl3_ttf-subbuild/sdl3_ttf-populate-prefix/src"
  "/home/vietexa/Desktop/vtquiz/build-web/_deps/sdl3_ttf-subbuild/sdl3_ttf-populate-prefix/src/sdl3_ttf-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/vietexa/Desktop/vtquiz/build-web/_deps/sdl3_ttf-subbuild/sdl3_ttf-populate-prefix/src/sdl3_ttf-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/vietexa/Desktop/vtquiz/build-web/_deps/sdl3_ttf-subbuild/sdl3_ttf-populate-prefix/src/sdl3_ttf-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
