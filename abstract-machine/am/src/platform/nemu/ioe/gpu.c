#include <am.h>
#include <nemu.h>
#include <klib.h>

#define SYNC_ADDR (VGACTL_ADDR + 4)

void __am_gpu_init() {
    // int w = io_read(AM_GPU_CONFIG).width;
    // int h = io_read(AM_GPU_CONFIG).height;
    // printf("%d, %d", w, h);
    // uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
    // for (int i = 0; i < w * h; i ++) fb[i] = i * rand();
    // outl(SYNC_ADDR, 1);
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
    // width 与 height 共占 32 bits, width 占据高 16 bits, height 占据低 16 bits
    uint32_t info = inl(VGACTL_ADDR);
    uint16_t height = (uint16_t)(info & 0xFFFF);
    uint16_t width = (uint16_t)(info >> 16);
    *cfg = (AM_GPU_CONFIG_T) {
        .present = true, .has_accel = false,
        .width = width, .height = height,
        .vmemsz = 0
    };
}

// 以像素为单位绘图
void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {
    if (!ctl->sync && (ctl->w == 0 || ctl->h == 0)) return;
    uint32_t* pixels = ctl->pixels;
    uint32_t width = inl(VGACTL_ADDR) >> 16;
    uint32_t* fb = (uint32_t *)(uintptr_t)FB_ADDR;
    for (int pi = 0, fi = ctl->y; pi < ctl->h; ++fi, ++pi) {
        for (int pj = 0, fj = ctl->x; pj < ctl->w; ++fj, ++pj) {
            fb[fi*width+fj] = pixels[pi*ctl->w+pj];
        }
    }
    if (ctl->sync) {
        outl(SYNC_ADDR, 1);
    }
}

// 以像素为单位拷贝
void __am_gpu_memcpy(AM_GPU_MEMCPY_T *gpu_memcpy) {
    uint32_t* src = (uint32_t *)gpu_memcpy->src;
    uint32_t* fb = (uint32_t *)((uintptr_t)FB_ADDR + gpu_memcpy->dest);
    for (int i = 0; i < gpu_memcpy->size; ++ i) {
        // outb(FB_ADDR + i + gpu_memcpy->dest, src[i]);
        fb[i] = src[i];
    }
    outl(SYNC_ADDR, 1);
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
    status->ready = true;
}

