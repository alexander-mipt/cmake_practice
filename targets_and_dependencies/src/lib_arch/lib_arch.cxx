#ifdef HAVE_PI
#include <cmath>
#endif

double arch_result() {
#ifdef HAVE_PI
	return M_PI;
#else
	return 3.14;
#endif
}
