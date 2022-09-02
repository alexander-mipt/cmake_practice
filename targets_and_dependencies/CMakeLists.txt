cmake_minimum_required(VERSION 3.10)

# set the project name
project(Tutorial VERSION 1.0)

# add cache bool vars
option(USE_LIB_PRINT "Use print lib" ON)
option(USE_LIB_CALC "USe calc lib" ON)

set(INCLUDE_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(LIB_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/src)

list(APPEND INCLUDE_DIRS "${INCLUDE_PREFIX}")
list(APPEND LIBS "")
if(USE_LIB_PRINT)
	list(APPEND INCLUDE_DIRS "${INCLUDE_PREFIX}/lib_print")
	add_subdirectory("${LIB_PREFIX}/lib_print")
	list(APPEND LIBS lib_print)
endif()
if(USE_LIB_CALC)
	# alt: use INTERFACE option in subdirectory
	#list(APPEND INCLUDE_DIRS "${INCLUDE_PREFIX}/lib_calc")
	add_subdirectory("${LIB_PREFIX}/lib_calc")
	list(APPEND LIBS lib_calc)
endif()

configure_file(${INCLUDE_PREFIX}/TutorialConfig.hpp.in ${INCLUDE_PREFIX}/TutorialConfig.hpp)

# add the executable
add_executable(Tutorial src/tutorial.cxx)
target_include_directories(Tutorial PRIVATE ${INCLUDE_DIRS})
target_link_directories(Tutorial PRIVATE ${LIB_DIRS})
target_link_libraries(Tutorial PRIVATE ${LIBS})

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#install bugs
#set(CMAKE_INSTALL_PREFIX CACHE STRING "${CMAKE_SOURCE_DIR}/install" FORCE) 
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install" CACHE PATH "Install path for mylib package-related CMake files" FORCE)
install(TARGETS Tutorial RUNTIME COMPONENT Tutorial)
install(TARGETS lib_calc LIBRARY COMPONENT lib_calc)
install(DIRECTORY ${INCLUDE_PREFIX} DESTINATION ${CMAKE_INSTALL_PREFIX})
#install(TARGETS ${LIBS} DESTINATION lib)


# debug print
message(STATUS ${CMAKE_BINARY_DIR})
message(STATUS ${CMAKE_CURRENT_BINARY_DIR})
message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
