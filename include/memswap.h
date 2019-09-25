#ifndef QIX_MEMSWAP_H__
#define QIX_MEMSWAP_H__
#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int memswap(void *p1, void *p2, size_t count);

#ifdef __cplusplus
}
#endif
#endif
