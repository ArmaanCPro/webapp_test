cmake_minimum_required(VERSION 3.20)

# link vcpkg packages. TODO: this bullshit doesn't work :(
set(VCPKG_ROOT $ENV{VCPKG_ROOT})
message(STATUS "Using VCPKG_ROOT: ${VCPKG_ROOT}")
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

project(webapp_test)

# Turn on the ability to create folders to organize projects (.vcproj)
# It creates "CMakePredefinedTargets" folder by default and adds CMake
# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(webapp_test)