cmake_minimum_required(VERSION 3.25)




set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "")  # provide a json file with the compile commands so clangd can use it

project(VTQuiz LANGUAGES C CXX)

# Include the fetch content submodule and use it to fetch the dependencies
include(FetchContent)

option (use_static_libs "Make the project be statically linked" ON)

if (use_static_libs)
    message("Attempting to statically link the project")

    if (UNIX)
      set(CMAKE_POSITION_INDEPENDENT_CODE ON )  
    endif()

    set(SDL_SHARED OFF) # Disable Dynamic Linking
    set(SDL_STATIC ON) # Enable Static Linking
    set(BUILD_SHARED_LIBS OFF)

else()
    set(SDL_SHARED ON) # Enable Dynamic Linking
    set(SDL_STATIC OFF) # Disable Static Linking

endif()

# Disable the SDL_Image backends
foreach(loader AVIF BMP GIF JPG LBM PCX PNM QOI SVG TGA TIF WEBP XCF XPM XV STB)
    set(SDLIMAGE_${loader} OFF CACHE BOOL "" FORCE)
endforeach()


set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL_TESTS OFF CACHE BOOL "" FORCE)

# Default to Release if not specified otherwise
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Fetch the dependencies
FetchContent_Declare(SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-3.2.26
)
FetchContent_MakeAvailable(SDL3)


FetchContent_Declare(SDL3_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG        release-3.2.4
)
FetchContent_MakeAvailable(SDL3_image)


FetchContent_Declare(SDL3_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
    GIT_TAG        release-3.2.0
)
FetchContent_MakeAvailable(SDL3_ttf)



add_executable(VTQuiz src/main.cpp src/utils.cpp src/gui.cpp src/state.cpp src/event.cpp)


target_include_directories(VTQuiz PRIVATE src)

target_link_libraries(VTQuiz PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf)
