cmake_minimum_required(VERSION 3.10)

# set the project name
project(Tutorial VERSION 1.0)

# add cache bool vars
option(USE_LIB_PRINT "Use print lib" ON)
option(USE_LIB_CALC "Use calc lib" ON)
option(USE_LIB_ARCH "Use arch lib" ON)

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
if(USE_LIB_ARCH)
	add_subdirectory("${LIB_PREFIX}/lib_arch")
	list(APPEND LIBS lib_arch)
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

# tests
enable_testing()

# does the application run
add_test(NAME Runs COMMAND Tutorial)

# does the usage message work?
add_test(NAME Usage COMMAND Tutorial 3)
set_tests_properties(Usage
  PROPERTIES PASS_REGULAR_EXPRESSION "hi\n2\nHello 1\n3"
  )

# define a function to simplify adding tests
function(do_test target arg result)
  add_test(NAME Comp${arg} COMMAND ${target} ${arg})
  set_tests_properties(Comp${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction()

# do a bunch of result based tests
set(STR "hi\n2\nHello 1\n")
do_test(Tutorial 4 "${STR}4")
do_test(Tutorial 9 "${STR}9")
do_test(Tutorial 5 "${STR}5")
