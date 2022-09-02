set(LIB_SRC lib_arch.cxx)
add_library(lib_arch ${LIB_SRC})
target_include_directories(lib_calc INTERFACE ${CMAKE_SOURCE_DIR}/include/lib_arch)

# does this system provide the log and exp functions?
include(CheckCXXSourceCompiles)
check_cxx_source_compiles("
  #include <cmath>
  int main() {
    double val = M_PI;
    return 0;
  }
" HAVE_PI)

if(HAVE_PI)
  target_compile_definitions(lib_arch
                             PRIVATE "HAVE_PI")
endif()
