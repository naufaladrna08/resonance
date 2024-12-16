cmake_minimum_required(VERSION 3.5)

project(DAWgong)

set(CMAKE_CXX_STANDARD 17)

# Find Packages
find_package(glfw3 REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)
pkg_check_modules(GL REQUIRED gl)
pkg_check_modules(JACK REQUIRED jack)
pkg_check_modules(RTMIDI REQUIRED rtmidi)

add_subdirectory(vendor/imgui)
add_subdirectory(vendor/imnodes)

# Include directories
include_directories(include)
include_directories(vendor/imgui)
include_directories(vendor/imnodes)

# Add source files
set(SOURCES
  src/main.cpp
  src/Application.cpp
  src/AudioEngine.cpp
  src/MIDIHandler.cpp
  src/GUI/MainWindow.cpp
  src/GUI/Components/Toolbar.cpp
  src/Callbacks/Passthrough.cpp
)

# Add header files
set(HEADERS
  include/Application.h
  include/AudioEngine.h
  include/MIDIHandler.h
  include/GUI/MainWindow.h
  include/GUI/Components/Toolbar.h
)

# Add executable
add_executable(DAWgong ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(DAWgong glfw imgui ${GLFW_LIBRARIES} ${GL_LIBRARIES} ${JACK_LIBRARIES} ${RTMIDI_LIBRARIES} imnodes)

# Copy resources
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})