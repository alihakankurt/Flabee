cmake_minimum_required(VERSION 4.0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Flabee
    VERSION 0.0.1
    DESCRIPTION "It's a flapping bee."
    LANGUAGES C
)

add_executable(${PROJECT_NAME})

target_compile_features(${PROJECT_NAME}
    PRIVATE
        c_std_11
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        -Wall
        $<$<CONFIG:Release>:
            -Wextra
            -O3
        >
)

add_subdirectory(External/SDL)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        SDL3::SDL3
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        Include
)

target_sources(${PROJECT_NAME}
    PRIVATE
        Source/Bee.c
        Source/Obstacle.c
        Source/Main.c
)
