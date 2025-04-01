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
  src/application.cpp
  src/audio_engine.cpp
  src/midi_handler.cpp
  src/ui/main_window.cpp
  src/ui/components/toolbar.cpp
  src/callbacks/passthrough.cpp
)

# Add header files
set(HEADERS
  include/application.h
  include/audio_engine.h
  include/midi_handler.h
  include/ui/main_window.h
  include/ui/components/toolbar.h
)

# Add executable
add_executable(DAWgong ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(DAWgong glfw imgui ${GLFW_LIBRARIES} ${GL_LIBRARIES} ${JACK_LIBRARIES} ${RTMIDI_LIBRARIES} imnodes)

# Copy resources
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})