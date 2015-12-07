cmake_minimum_required(VERSION 3.3)
project(Lake_Pend_Oreille_client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Build main executable
set(SOURCE_FILES src/main.cpp src/mylib.cpp)
include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(Lake_Pend_Oreille_client ${SOURCE_FILES})

# Locate and link required Boost headers/libraries
find_package(Boost 1.59 COMPONENTS system REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
target_link_libraries(Lake_Pend_Oreille_client ${Boost_LIBRARIES})

# For testing
add_subdirectory(tests)