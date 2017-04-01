/**
 * @file
 *
 * @brief Assertions macros.
 *
 * @copyright BSD License (see doc/LICENSE.md or https://www.libelektra.org)
 */

#include <kdbconfig.h>

#ifdef __cplusplus
extern "C" {
#endif


void elektraAbort (const char * expression, const char * function, const char * file, const int line, const char * msg, ...)
#ifdef __GNUC__
	__attribute__ ((format (printf, 5, 6)))
#endif
	;

#ifdef __cplusplus
}
#endif

#ifndef STRINGIFY
#define STRINGIFY(x) STRINGIFY2 (x)
#define STRINGIFY2(x) #x
#endif

#ifdef ELEKTRA_BMC
#undef NDEBUG
#include <assert.h>
#define ELEKTRA_ASSERT(EXPR, ...) assert (EXPR)
#else
#if DEBUG
#define ELEKTRA_ASSERT(EXPR, ...) ((EXPR)) ? (void)(0) : elektraAbort (STRINGIFY (EXPR), __func__, __FILE__, __LINE__, __VA_ARGS__)
#else
#define ELEKTRA_ASSERT(EXPR, ...)
#endif
#endif
