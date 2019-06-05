#include "pmdk.h"
#include <assert.h>

typedef uintptr_t RootObject;
typedef char DataObject;

POBJ_LAYOUT_BEGIN(LEVEL_HASH);
POBJ_LAYOUT_ROOT(LEVEL_HASH, RootObject);
POBJ_LAYOUT_TOID(LEVEL_HASH, DataObject);
POBJ_LAYOUT_END(LEVEL_HASH);

static PMEMobjpool *pop = NULL;

__attribute__((constructor)) void pmdk_init() {
    pop = pmemobj_create(POOL_PATH, POBJ_LAYOUT_NAME(LEVEL_HASH), POOL_SIZE, 0666);
    assert(pop != NULL);
}

__attribute__((destructor)) void pmdk_finalize() {
    pmemobj_close(pop);
}

void* pmalloc(size_t sz) {
    PMEMoid oid;
    pmemobj_zalloc(pop, &oid, sz, TOID_TYPE_NUM(DataObject));
    return pmemobj_direct(oid);
}

void pfree(void* ptr, size_t sz) {
    PMEMoid oid = pmemobj_oid(ptr);
    pmemobj_free(&oid);
}

void pflush(uint64_t *addr) {
    pmemobj_persist(pop, (const void*)addr, 64);
}
