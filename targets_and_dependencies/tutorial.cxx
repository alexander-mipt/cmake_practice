#include "TutorialConfig.hpp"
#include <iostream>

#ifdef USE_LIB_PRINT
#include "lib_print.hpp"
#endif
#ifdef USE_LIB_CALC
#include "lib_calc.hpp"
#endif

int main() {
#ifdef USE_LIB_PRINT
	print_hi();
#endif
#ifdef USE_LIB_CALC
	std::cout << calc() << std::endl;
#endif
	std::cout << "Hello " << Tutorial_VERSION_MAJOR << std::endl;
}
