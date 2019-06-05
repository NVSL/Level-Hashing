#include <libpmemobj.h>
#ifndef _PMDK_H_
#define _PMDK_H_
#define POOL_PATH   "/mnt/ram/hash.pop"
#define POOL_SIZE   ((size_t)32 << 30)

#define asm_mfence() ({ __asm__ __volatile__ ("mfence":::"memory"); })

void* pmalloc(size_t);
void pfree(void*, size_t);
void pflush(uint64_t *);

#endif // _PMDK_H_
