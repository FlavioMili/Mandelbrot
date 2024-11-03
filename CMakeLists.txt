cmake_minimum_required(VERSION 3.5)

# Set IPO policy before project declaration
cmake_policy(SET CMP0069 NEW)

project(MandelbrotSFML VERSION 1.0
    DESCRIPTION "Mandelbrot Set Visualizer using SFML"
    LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable optimization flags for Release builds
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native -flto")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /GL")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

# Find required packages
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
find_package(OpenGL REQUIRED)

# Create executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Set include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SFML_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    OpenGL::GL
)

# Copy shader files to build directory
file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR})

# Install configuration
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
install(DIRECTORY shaders/
    DESTINATION bin/shaders
)

# Enable IPO (Link Time Optimization) if available
include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported OUTPUT ipo_error)
if(ipo_supported)
    set_property(TARGET ${PROJECT_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

# Add build info
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "IPO supported: ${ipo_supported}")
