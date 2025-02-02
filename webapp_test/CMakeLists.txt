cmake_minimum_required(VERSION 3.20)

project (webapp_test)

#set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -WB_DEBUG" )	#so we can add the DEBUG preprocessor define and other flags to stay in debug mode - see https://cmake.org/Wiki/CMake_Useful_Variables#Compilers_and_Tools
#set( CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -WB_DEBUG" )

if(MSVC)
    add_compile_options(/MP)				#Use multiple processors when building
    #add_compile_options(/W4 /wd4201 /WX)	#Warning level 4, all warnings are errors
else()
    #add_compile_options(-W -Wall -Werror) #All Warnings, all warnings are errors
endif()


# source for the test executable
set  (SOURCES
        "src/main.cpp")

source_group("src" FILES ${SOURCES})

add_executable( webapp_test ${SOURCES} 	)

# Find and link Boost.Asio (via vcpkg)
find_package(boost_system REQUIRED)
find_package(boost_asio REQUIRED)

# Link the Boost libraries and Winsock (ws2_32). winsock is necessary for asio
target_link_libraries(webapp_test PRIVATE Boost::system Boost::asio ws2_32)
