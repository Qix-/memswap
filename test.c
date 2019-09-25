#include "./memswap.c"
#include "./crc_32.c"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void swap_and_compare(memswap_fn impl, void *p1, void *p2, size_t count) {
	uint32_t p1_crc = crc32buf(p1, count);
	uint32_t p2_crc = crc32buf(p2, count);
	/* make sure we're testing uneven boundaries */
	assert((count % 2) != 0);
	impl(p1, p2, count);
	assert(p1_crc == crc32buf(p2, count));
	assert(p2_crc == crc32buf(p1, count));
}

int main(void) {
	size_t i;

	#define TEST_SIZE (4096 * 128) + 3

	/* Don't think too hard, it's not supposed to
	   have perfect distribution. */
	char left[TEST_SIZE];
	char right[TEST_SIZE];
	srand(time(NULL));
	for (i = 0; i < TEST_SIZE; i++) {
		left[i] = (char) (rand() & 0xFF);
		right[i] = (char) (rand() & 0xFF);
	}

	swap_and_compare(&memswap, left, right, TEST_SIZE);
	swap_and_compare(&memswap__impl_dumb, left, right, TEST_SIZE);

	return 0;
}
