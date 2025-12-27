cmake_minimum_required(VERSION 3.10)

# Set some basic project attributes
project (txelrsip
	VERSION 0.1
	DESCRIPTION "Transmit ELRS messages to UDP port")
	
set(CMAKE_VERBOSE_MAKEFILE ON) # Doesn't seem to take effect

# This project will output an executable file
add_executable(${PROJECT_NAME} main.c sender.c)

# Create a simple configuration header
configure_file(config.h.in config.h)

# Include the configuration header in the build
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}" ../crsf)

# Add crsf library
target_link_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/../crsf/build/cmake.run.linux.x86_64.Local") # -L../crsf/build/cmake.run.linux.x86_64.Local
target_link_libraries(${PROJECT_NAME} crsf) # -lcrsf