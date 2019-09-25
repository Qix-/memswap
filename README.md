# memswap

A general purpose memory swapping function.

Self-selects the best implementation available given the architecture (compile-time)
and supported features (runtime). This includes SIMD implementations.

```c
#include <memswap.h>

/*
	Takes two pointers and swaps `count' bytes
	of memory.

	Memory regions that overlap are Undefined
	Behavior.

	If either pointers are NULL, returns non-zero
	and sets `errno' to EINVAL.

	Upon success, returns 0.
*/
int memswap(void *p1, void *p2, size_t count);
```
