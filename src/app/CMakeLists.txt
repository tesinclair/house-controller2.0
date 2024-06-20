cmake_minimum_required(VERSION 3.0)

project(
    House-Controller-2.0
    VERSION 0.7
    DESCRIPTION "An app for controlling, and creating custom led strip controls" 
    LANGUAGES C
)

# Find pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED "gtk+-3.0")
pkg_check_modules(LIGHTS_DSL REQUIRED "lights-dsl")

set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -rdynamic")

set(UTIL_DIR src/utils)

add_library(util_client STATIC ${UTIL_DIR}/utilClient.c ${UTIL_DIR}/utillib.h)
add_library(util_stack STATIC ${UTIL_DIR}/utilStack.c ${UTIL_DIR}/utillib.h)
add_library(util_error STATIC ${UTIL_DIR}/utilError.c ${UTIL_DIR}/utillib.h)
add_library(util_light STATIC ${UTIL_DIR}/utilLight.c ${UTIL_DIR}/utillib.h)

# Link GTK+ libraries to utility libraries
target_link_libraries(util_client PRIVATE ${GTK3_LIBRARIES})
target_link_libraries(util_stack PRIVATE ${GTK3_LIBRARIES})
target_link_libraries(util_error PRIVATE ${GTK3_LIBRARIES})
target_link_libraries(util_light PRIVATE ${GTK3_LIBRARIES})

# Include directories for utility libraries
target_include_directories(util_client PRIVATE ${GTK3_INCLUDE_DIRS})
target_include_directories(util_stack PRIVATE ${GTK3_INCLUDE_DIRS})
target_include_directories(util_error PRIVATE ${GTK3_INCLUDE_DIRS})
target_include_directories(util_light PRIVATE ${GTK3_INCLUDE_DIRS})

add_executable(house-controller src/main.c)

target_link_libraries(
    house-controller
    PRIVATE
    util_client
    util_stack
    util_error
    util_light
    ${GTK3_LIBRARIES}
    ${LIGHTS_DSL_LIBRARIES}
    m
)

target_link_directories(
    house-controller
    PRIVATE
    ${LIGHTS_DSL_LIBDIR}
)

target_include_directories(
    house-controller
    PRIVATE
    ${GTK3_INCLUDE_DIRS}
    ${LIGHTS_DSL_INCLUDE_DIRS}
)

target_compile_options(
    house-controller
    PRIVATE
    ${GTK3_CFLAGS_OTHER}
    ${LIGHTS_DSL_CFLAGS_OTHER}
)

# Clean rule
add_custom_target(clean-all
    COMMAND ${CMAKE_BUILD_TOOL} clean
    COMMAND rm -rf *.glade~
    COMMENT "Cleaning..."
)
