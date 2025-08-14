cmake_minimum_required(VERSION 3.10)
project(GamePI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(RELEASE_BIN_FOLDER "${CMAKE_SOURCE_DIR}/bin/release")
set(DEBUG_BIN_FOLDER "${CMAKE_SOURCE_DIR}/bin/debug")
set(OUTFILE "sfml-app.out")

# Source files
set(CODE_FILES
    Demo_main.cpp
    libs/SFMLBoost/BoostSFML.cpp
    libs/SFMLBoost/ObjectsGroup.cpp
    Core/AssetsCacheManager.cpp
    Core/ConfigLoader.cpp
    Core/Scenes/Scene.cpp
    Core/Scenes/SceneManager.cpp
    Scenes/SplashScreen.cpp
    Scenes/MainMenu.cpp
    Scenes/GameShowCase.cpp
)

# MacroFlags header file
set(COMPILING_MODE_HEADER "MacroFlags.hpp")

# SFML link flags
set(DYNAMIC_SFML_LIBS sfml-audio sfml-graphics sfml-window sfml-system)
set(STATIC_SFML_LIBS sfml-audio-s sfml-graphics-s sfml-window-s sfml-system-s)

# Option for static SFML linking
option(USE_STATIC_SFML "Link with static SFML libraries" OFF)

# Find SFML
if(USE_STATIC_SFML)
    find_package(SFML 2.5.1 COMPONENTS audio graphics window system REQUIRED STATIC)
    set(SFML_LIBS ${STATIC_SFML_LIBS})
else()
    find_package(SFML 2.5.1 COMPONENTS audio graphics window system REQUIRED)
    set(SFML_LIBS ${DYNAMIC_SFML_LIBS})
endif()

# Create MacroFlags.hpp for the build type
add_custom_command(
    OUTPUT ${COMPILING_MODE_HEADER}
    COMMAND ${CMAKE_COMMAND} -E echo "#define $<$<CONFIG:Release>:RELEASE>$<$<CONFIG:Debug>:DEBUG>" > ${COMPILING_MODE_HEADER}
    VERBATIM
)

add_custom_target(generate_macroflags DEPENDS ${COMPILING_MODE_HEADER})

# Add executable
add_executable(${OUTFILE} ${CODE_FILES} ${COMPILING_MODE_HEADER})
add_dependencies(${OUTFILE} generate_macroflags)
target_include_directories(${OUTFILE} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${OUTFILE} PRIVATE ${SFML_LIBS})

# Set output directories for debug/release
set_target_properties(${OUTFILE} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${DEBUG_BIN_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${RELEASE_BIN_FOLDER}
)

add_custom_command(
    TARGET ${OUTFILE}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/../assets
        $<TARGET_FILE_DIR:${OUTFILE}>/assets
)

# Optional: run target
add_custom_target(run
    COMMAND $<TARGET_FILE:${OUTFILE}>
    DEPENDS ${OUTFILE}
    WORKING_DIRECTORY $<TARGET_FILE_DIR:${OUTFILE}>
)