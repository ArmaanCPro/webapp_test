# TO RUN

1. Clone the repo
2. The project relies on vcpkg. I'd recommend installing it globally on your system and adding VCPKG_ROOT to your environment variables.
3. To make CMAKE use the vcpkg toolchain, you need to set CMAKE_TOOLCHAIN_FILE to the vcpkg.cmake file in your vcpkg directory.
4. If you're using CLion, you can set -DCMAKE_TOOLCHAIN_FILE:STRING=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake in your CMake options
5. Not sure what to do if you're using visual studio directly with cmake, but I'm sure you can figure it out.
6. If you want to build cmake manually, you can run the build_cmake.bat file in the root directory. This will build the project and set the toolchain file for you.
7. Should build and run fine. I'm using CLion and it works on that

Note: if you don't have VCPKG_ROOT set in your environment variables, you can use absolute paths, just replace it wherever you see ${VCPKG_ROOT} with the path to your vcpkg directory.