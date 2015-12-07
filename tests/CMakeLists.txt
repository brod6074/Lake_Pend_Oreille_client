project(tests)

# Build test executable
include_directories(${PROJECT_SOURCE_DIR}/include)
set(SOURCE_FILES src/tests.cpp ../src/mylib.cpp)
add_executable(tests ${SOURCE_FILES})

# Locate and link required Boost headers/libraries
find_package(Boost 1.59 COMPONENTS system REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
target_link_libraries(tests ${Boost_LIBRARIES})