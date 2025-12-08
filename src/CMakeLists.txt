
add_executable(VTQuiz main.cpp utils.cpp gui.cpp state.cpp)

if (UNIX)
set_target_properties(VTQuiz PROPERTIES
    BUILD_RPATH "\$ORIGIN"
)

endif()

target_link_libraries(VTQuiz PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf)