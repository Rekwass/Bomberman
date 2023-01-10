cmake_minimum_required(VERSION 3.17)

###############################################################################
# BUILD RAYLIB
###############################################################################

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/raylib")

find_package(raylib REQUIRED)

###############################################################################
# BUILD FMT
###############################################################################

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/fmt")

find_package(fmt REQUIRED)

###############################################################################
# BUILD NLOHMANN_JSON
###############################################################################

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/nlohmann_json")

find_package(nlohmann_json REQUIRED)

###############################################################################
# BUILD GOOGLETEST
###############################################################################

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/googletest")

find_package(googletest REQUIRED)
