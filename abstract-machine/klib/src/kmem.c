#include <am.h>
#include <klib.h>
#include <klib-macros.h>

extern Area heap;

#define NR_AREA 256
Area areas[NR_AREA];

uint64_t areas_top = 0;
uint64_t offset = 0;

void new_area(void* start, void* end, bool used) {
    areas[areas_top].start = start;
    areas[areas_top].end = end;
    areas[areas_top].used = used;
    areas_top += 1;
}

void* kmalloc(size_t size) {
    if (size == 0) return NULL;
    // 内存对齐
    size  = (size_t)ROUNDUP(size, 8);
    for (int i = 0; i < areas_top; ++i) {
        if (areas[i].used == false && AREA_SIZE(areas[i]) >= size) {
            areas[i].used = true;
            return areas[i].start + (uint64_t)heap.start;
        }
    }
    size = ROUNDUP(size, 64);
    new_area((void*)offset, (void*)(offset+size), true);

    uint64_t ret = (uint64_t)heap.start + offset;
    
    offset += size;
    return (void*)ret;
}

void kfree(void *ptr) {
    if (ptr == NULL) return;
    assert(ptr >= heap.start);
    ptr = ptr - (uint64_t)heap.start;
    for (int i = 0; i < areas_top; ++i) {
        if (IN_RANGE(ptr, areas[i])) {
            areas[i].used = false;
            return;
        }
    }
}
