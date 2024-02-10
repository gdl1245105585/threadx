#include <am.h>
#include <nemu.h>
#include <klib.h>

#define AUDIO_FREQ_ADDR      (AUDIO_ADDR + 0x00)
#define AUDIO_CHANNELS_ADDR  (AUDIO_ADDR + 0x04)
#define AUDIO_SAMPLES_ADDR   (AUDIO_ADDR + 0x08)
#define AUDIO_SBUF_SIZE_ADDR (AUDIO_ADDR + 0x0c)
#define AUDIO_INIT_ADDR      (AUDIO_ADDR + 0x10)
#define AUDIO_COUNT_ADDR     (AUDIO_ADDR + 0x14)

static uint32_t front = 0;
static uint32_t bufsize = 0;

/**
 * io_read(AM_AUDIO_CONFIG).present
 * io_write(AM_AUDIO_CTRL, 8000, 1, 1024);
 * io_write(AM_AUDIO_PLAY, sbuf);
 * io_read(AM_AUDIO_STATUS).count
 **/ 

static void audio_write(uint8_t* buf, int len) {
    uint8_t* sbuf = (void*)AUDIO_SBUF_ADDR;
    // 若当前流缓冲区的空闲空间少于即将写入的音频数据, 此次写入将会一直等待, 直到有足够的空闲空间将音频数据完全写入流缓冲区才会返回.
    volatile uint32_t count = inl(AUDIO_COUNT_ADDR);
    while ((bufsize - count) < len) count = inl(AUDIO_COUNT_ADDR);

    uint32_t write_len = len;

    // 写环形缓冲区 sbuf 不需要折回
    if (write_len + front < bufsize) {
        // 拷贝数据
        memcpy(sbuf+front, buf, write_len);
        // 更新队首
        front += write_len;
    }
    // 写 sbuf 环形缓冲区需要折回
    else {
        // 拷贝数据
        uint32_t first = bufsize - front;
        memcpy(sbuf+front, buf, first);
        memcpy(sbuf, buf+first, write_len - first);
        // 更新队首
        front = write_len - first;
    }
    // 更新 count 寄存器
    count += write_len;
    outl(AUDIO_COUNT_ADDR, count);
}

void __am_audio_init() {
    front = 0;
}

void __am_audio_config(AM_AUDIO_CONFIG_T *cfg) {
    cfg->bufsize = inl(AUDIO_SBUF_SIZE_ADDR);
    cfg->present = cfg->bufsize != 0;
    bufsize = cfg->bufsize;
}

void __am_audio_ctrl(AM_AUDIO_CTRL_T *ctrl) {
    outl(AUDIO_FREQ_ADDR, ctrl->freq);
    outl(AUDIO_CHANNELS_ADDR, ctrl->channels);
    outl(AUDIO_SAMPLES_ADDR, ctrl->samples);
    outl(AUDIO_INIT_ADDR, 1); // 通知 NEMU 可以初始化音频了
    front = 0;
}

void __am_audio_status(AM_AUDIO_STATUS_T *stat) {
    stat->count = inl(AUDIO_COUNT_ADDR);
}

// 写数据到 流缓冲区 sbuf
void __am_audio_play(AM_AUDIO_PLAY_T *ctl) {
    int len = ctl->buf.end - ctl->buf.start;
    audio_write(ctl->buf.start, len);
}
