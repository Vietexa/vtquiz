# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/home/vietexa/Desktop/vtquiz/build-web/_deps/sdl3_image-src")
  file(MAKE_DIRECTORY "/home/vietexa/Desktop/vtquiz/build-web/_deps/sdl3_image-src")
endif()
file(MAKE_DIRECTORY
  "/home/vietexa/Desktop/vtquiz/build-web/_deps/sdl3_image-build"
  "/home/vietexa/Desktop/vtquiz/build-web/_deps/sdl3_image-subbuild/sdl3_image-populate-prefix"
  "/home/vietexa/Desktop/vtquiz/build-web/_deps/sdl3_image-subbuild/sdl3_image-populate-prefix/tmp"
  "/home/vietexa/Desktop/vtquiz/build-web/_deps/sdl3_image-subbuild/sdl3_image-populate-prefix/src/sdl3_image-populate-stamp"
  "/home/vietexa/Desktop/vtquiz/build-web/_deps/sdl3_image-subbuild/sdl3_image-populate-prefix/src"
  "/home/vietexa/Desktop/vtquiz/build-web/_deps/sdl3_image-subbuild/sdl3_image-populate-prefix/src/sdl3_image-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/vietexa/Desktop/vtquiz/build-web/_deps/sdl3_image-subbuild/sdl3_image-populate-prefix/src/sdl3_image-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/vietexa/Desktop/vtquiz/build-web/_deps/sdl3_image-subbuild/sdl3_image-populate-prefix/src/sdl3_image-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
