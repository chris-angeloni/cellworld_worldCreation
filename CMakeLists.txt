cmake_minimum_required( VERSION 3.10 )

set(CMAKE_CXX_STANDARD 20)

project( new_worlds
        VERSION 2021.1.0
        DESCRIPTION "Create worlds for experiments"
        LANGUAGES CXX)

####
#### DEPENDENCIES
####

find_package (Dependencies QUIET)

if (NOT ${Dependencies_FOUND})
    if (NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/DependenciesConfig.cmake)
        file(DOWNLOAD https://raw.githubusercontent.com/germanespinosa/dependencies/main/DependenciesConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/DependenciesConfig.cmake)
    endif()
    set(Dependencies_DIR "${CMAKE_CURRENT_BINARY_DIR}")
    find_package (Dependencies REQUIRED)
endif()

####
#### END DEPENDENCIES
####

string(APPEND CMAKE_CXX_FLAGS " -pthread ")

install_git_dependency(Cellworld
        https://github.com/germanespinosa/cellworld
        CMAKE_PROJECT
        IMPORT_TARGETS cellworld requests json-cpp)

install_git_dependency(Params-cpp https://github.com/germanespinosa/params-cpp
        CMAKE_PROJECT
        IMPORT_TARGETS params-cpp)

###
### UTILITIES SETUP
###

include_directories( include )


add_executable(create_world src/tool/create_world.cpp)
target_link_libraries(create_world PUBLIC cellworld requests json-cpp params-cpp)

add_executable(create_robot_world src/tool/create_robot_world.cpp)
target_link_libraries(create_robot_world PUBLIC cellworld requests json-cpp params-cpp)

add_executable(create_predator_destinations src/tool/create_predator_destinations.cpp)
target_link_libraries(create_predator_destinations PUBLIC cellworld requests json-cpp params-cpp)

add_executable(create_spawn_locations src/tool/create_spawn_locations.cpp)
target_link_libraries(create_spawn_locations PUBLIC cellworld requests json-cpp params-cpp)

add_executable(create_visibility src/tool/create_visibility.cpp)
target_link_libraries(create_visibility PUBLIC cellworld requests json-cpp params-cpp)

add_executable(create_robot_destination_world src/tool/create_robot_destination_world.cpp)
target_link_libraries(create_robot_destination_world PUBLIC cellworld requests json-cpp params-cpp)
