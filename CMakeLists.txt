cmake_minimum_required(VERSION 4.0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Flabee
    VERSION 0.1.0
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
add_subdirectory(External/SDL_image)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        Include
)

target_sources(${PROJECT_NAME}
    PRIVATE
        Source/Bee.c
        Source/Obstacle.c
        Source/Collision.c
        Source/Assets.c
        Source/Game.c
        Source/Main.c
)

if (APPLE AND CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_BUNDLE_NAME "Flabee"
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.alihakankurt.flabee"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION}"
        MACOSX_BUNDLE_LONG_VERSION_STRING "${PROJECT_VERSION}"
        MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}"
        MACOSX_BUNDLE_COPYRIGHT "Copyright (C) 2025 Ali Hakan Kurt"
    )

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/Assets
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/../Resources/Assets
    )

    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework CoreFoundation")
endif()
