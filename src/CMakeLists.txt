file (GLOB_RECURSE sources *.h *.cpp *.hpp *.tpp)
include_directories(solvers)
include_directories(solvers/solvers_1d)
include_directories(solvers/solvers_1d/solver_1D1P)
include_directories(solvers/solvers_1d/solver_1D2P)
include_directories(solvers/solvers_2d)
include_directories(gpl_data_structure)
include_directories(tools)
add_executable(OriSpanner ${sources})

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
   set(CMAKE_INSTALL_RPATH='$ORIGIN')
endif ()


option(CXX "enable C++ compilation" ON)
if(CXX)
    enable_language(CXX)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
message (STATUS "CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}")


if (MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE "/O2 /DNDEBUG")
else ()
	#set(CMAKE_CXX_FLAGS "-Wextra")
	set(CMAKE_CXX_FLAGS_DEBUG "-g")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
	target_compile_features(OriSpanner PUBLIC cxx_std_17) 
	target_link_libraries(OriSpanner PUBLIC stdc++fs)
	
endif()


# Visual Studio compiler with static runtime libraries
if(MSVC AND MT)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MT")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MTd")
	
endif()




find_package(Boost REQUIRED)
target_link_libraries(OriSpanner PRIVATE Boost::boost)


set_property(TARGET OriSpanner PROPERTY CXX_STANDARD 17)
set_property(TARGET OriSpanner PROPERTY CXX_STANDARD_REQUIRED ON)