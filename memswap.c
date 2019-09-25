#include "./include/memswap.h"

#include <assert.h>
#include <errno.h>

typedef int (*memswap_fn)(void*, void*, size_t);

/* the following is copied from rapidstring - thanks to John Boyer <john.boyer@tutanota.com> */
#ifdef __GNUC__
#	define MEMSWAP_GCC_VERSION \
		(__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
#	define MEMSWAP_GCC_VERSION (0)
#endif

/* GCC version 2.96 required for branch prediction expectation. */
#if MEMSWAP_GCC_VERSION > 29600
#	define MEMSWAP_EXPECT(expr, val) __builtin_expect((expr), val)
#else
#	define MEMSWAP_EXPECT(expr, val) (expr)
#endif

/* note that `expr` must be either 0 or 1 for this to work - the 1/0 are not
   booleans but instead literal integral values.*/
/* https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html#index-_005f_005fbuiltin_005fexpect */
#define MEMSWAP_LIKELY(expr) MEMSWAP_EXPECT((expr), 1)
#define MEMSWAP_UNLIKELY(expr) MEMSWAP_EXPECT((expr), 0)

static int memswap__select_best(void *p1, void *p2, size_t count);
static memswap_fn memswap__implementation = &memswap__select_best;

static int memswap__impl_dumb(void *p1, void *p2, size_t count) {
	size_t tmp_bulk;
	char tmp_char;
	size_t bulk_iters;
	size_t leftover;
	size_t i;
	size_t *p1_bulk;
	size_t *p2_bulk;
	char *p1_chr;
	char *p2_chr;

	bulk_iters = count / sizeof(size_t);
	leftover = count % sizeof(size_t);

	p1_bulk = p1;
	p2_bulk = p2;

	p1_chr = p1;
	p2_chr = p2;

	p1_chr += count - leftover;
	p2_chr += count - leftover;

	for (i = 0; i < bulk_iters; i++) {
		tmp_bulk = p1_bulk[i];
		p1_bulk[i] = p2_bulk[i];
		p2_bulk[i] = tmp_bulk;
	}

	for (i = 0; i < leftover; i++) {
		tmp_char = p1_chr[i];
		p1_chr[i] = p2_chr[i];
		p2_chr[i] = tmp_char;
	}

	return 0;
}

static int memswap__select_best(void *p1, void *p2, size_t count) {
	memswap__implementation = &memswap__impl_dumb;

	assert(
		memswap__implementation != NULL
		&& memswap__implementation != memswap__select_best
	);

	return memswap__implementation(p1, p2, count);
}

int memswap(void *p1, void *p2, size_t count) {
	assert(memswap__implementation != NULL);

	if (MEMSWAP_UNLIKELY(p1 == NULL || p2 == NULL)) {
		errno = EINVAL;
		return 1;
	}

	return memswap__implementation(p1, p2, count);
}
