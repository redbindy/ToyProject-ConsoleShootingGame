#pragma once

#if _DEBUG

#include <stdio.h>
#include <intrin.h>

#define ASSERT(expr, msg) \
	if (!(expr)) \
	{ \
		fprintf(stderr, (msg)); \
		__debugbreak(); \
	} \
	\

#endif /* _DEBUG */

