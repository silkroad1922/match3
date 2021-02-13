# You could change the QUIET above to REQUIRED and remove this if() clause
# This part downloads raylib and builds it if it's not installed on your system
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)

  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/master.tar.gz
  )

  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)

    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples

    # build raylib
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})

  endif()

endif()

project(match3)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(match3 src/main.cpp src/Balls.cpp src/Board.cpp)

target_link_libraries(match3 raylib)
target_compile_options(match3 PRIVATE -Wall )
target_include_directories(match3 PRIVATE ${raylib_SOURCE_DIRS}/include)