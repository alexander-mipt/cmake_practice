#include "TutorialConfig.hpp"
#include <iostream>

#ifdef USE_LIB_PRINT
#include "lib_print.hpp"
#endif
#ifdef USE_LIB_CALC
#include "lib_calc.hpp"
#endif
#ifdef USE_LIB_ARCH
#include "lib_arch.hpp"
#endif

int main(int argc, char *argv[]) {
#ifdef USE_LIB_ARCH
	std::cout << arch_result() << std::endl;
#endif
#ifdef USE_LIB_PRINT
	print_hi();
#endif
#ifdef USE_LIB_CALC
	std::cout << calc() << std::endl;
#endif
	std::cout << "Hello " << Tutorial_VERSION_MAJOR << std::endl;
	if (argc > 1) {
		std::cout << argv[1] << std::endl;
		return std::atoi(argv[1]);
	}
	return 0;
}
