#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

char temp_buffer[1024];

/* 将字符数字串转换成整数, 并将指针前移 */
#define is_digit(c) ((c) >= '0' && (c) <= '9')

#define FMT_FLAG_LEFT        1          // 在给定的字段宽度内左对齐
#define FMT_FLAG_SHARP      (1 << 1)    // 与 x/X 说明符一起使用时, 非零值前面会分别显示 0x/0X
#define FMT_FLAG_ZERO       (1 << 2)    // 在指定填充 padding 的数字左边放置零

static char* num2str(char* buf, int num, int base, int width, int flags, int is_small) {
    // 转换字符索引[-15, -14, ...-1, 0, 1, ...., 14, 15]
    static char* digits = {"0123456789ABCDEF"};

    // 使用小写字母
    if (is_small) digits = "0123456789abcdef";
    // 若左对齐则屏蔽类型中的填零标志
    if (flags & FMT_FLAG_LEFT) flags &= ~FMT_FLAG_ZERO;
    // 仅支持部分进制
    if ((base != 2) && (base != 8) && (base != 10) && (base != 16)) return NULL;

    // 填充字符
    char padch = (flags & FMT_FLAG_ZERO) ? '0' : ' ';

    unsigned unum = num;
    // 只支持十进制负数
    int has_sign = 0;
    if ((num < 0) && (base == 10)) {
        has_sign = 1;
        width -= 1;
        unum = -num;
    }

    // 只支持十六进制前导符号0x/0X
    if ((base == 16) && (flags & FMT_FLAG_SHARP)) width -= 2;

    // 根据给定的基数将数值 unum 转换成字符形式
    int index = 0;
    char temp[36];
    do {
        temp[index++] = digits[unum % base];
        unum /= base;
    } while (unum != 0);

    // 宽度值减去用于存放数值字符的个数
    width -= index;

    char* p = buf;
    // 若 flags 中没有 填零 和 左对齐 标志, 则在 buf 中首先填放剩余宽度值指出的空格数
    if (!(flags & (FMT_FLAG_LEFT | FMT_FLAG_ZERO))) {
        while (width-- > 0)
            *p++ = ' ';
    }
    // 若有符号位(仅支持'-')
    if (has_sign) *p++ = '-';
    // 只支持十六进制前导符号0x/0X
    if ((base == 16) && (flags & FMT_FLAG_SHARP)) {
        *p++ = '0';
        *p++ = is_small ? 'x' : 'X';
    }

    // 若 flags 中没有左调整(左对齐)标志, 则在剩余宽度中填充字符
    if (!(flags & FMT_FLAG_LEFT)) {
        while (width-- > 0)
            *p++ = padch;
    }

    // 将转数值换好的数字字符填入 buf 中, 共 index 个
    while (index-- > 0)
        *p++ = temp[index];

    // 若宽度值仍大于零, 则表示 flags 标志中有左对齐标志标志, 则在剩余宽度中放入空格
    while (width-- > 0)
        *p++ = ' ';

    // 标记字符串结束
    *p = '\0';

    return p;
}

// 简化版vsprintf, format: %[flags][width]specifier
int vsprintf(char* out, const char* fmt, va_list ap) {
    enum { NORMAL, FMT_FLAG, FMT_WIDTH, FMT_SPEC } state = NORMAL;
    char* cur = out;
    char ch;
    int flags = 0, width = -1;
    char* str;
    int len;
    while ((ch = *fmt)) {
        switch (state) {
            case NORMAL:
                if (ch == '%') state = FMT_FLAG;
                else           *cur++ = ch;
            break;
            case FMT_FLAG:
                switch (ch) {
                    case '-': flags |= FMT_FLAG_LEFT;  break;
                    case '#': flags |= FMT_FLAG_SHARP; break;
                    case '0': flags |= FMT_FLAG_ZERO;  break;
                    default: state = FMT_WIDTH;        continue;
                }
            break;
            case FMT_WIDTH:
                width = 0;
                while (is_digit(*fmt))
                    width = width * 10 + *(fmt++) - '0';
                state = FMT_SPEC;
                continue;
            break;
            case FMT_SPEC:
                switch (ch) {
                    case 'c':
                        width -= 1; // 宽度减一!!!!!!!!
                        if (!(flags & FMT_FLAG_LEFT)) {
                            while (width-- > 0)
                                *cur++ = ' ';
                        }
                        *cur++ = (unsigned char)va_arg(ap, int);
                        while (width-- > 0)
                            *cur++ = ' ';
                    break;
                    case 's':
                        str = va_arg(ap, char *);
                        len = strlen(str);
                        if (!(flags & FMT_FLAG_LEFT)) {
                            while (len < width--)
                                *cur++ = ' ';
                        }
                        for (int i = 0; i < len; ++i)
                            *cur++ = *str++;
                        while (len < width--)
                            *cur++ = ' ';
                    break;
                    case 'p':
                        flags |= FMT_FLAG_SHARP;
                    case 'x':
                        cur = num2str(cur, va_arg(ap, unsigned), 16, width, flags, 1);
                    break;
                    case 'X':
                        cur = num2str(cur, va_arg(ap, unsigned), 16, width, flags, 0);
                    break;
                    case 'd':
                        cur = num2str(cur, va_arg(ap, unsigned), 10, width, flags, 0);
                    break;
                }
                flags = 0, width = 0; // !!!!!
                state = NORMAL;
            break;
        }
        fmt++;
    }
    *cur = '\0';
    return cur - out;
}

int sprintf(char *out, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int ret = vsprintf(out, fmt, args);
    va_end(args);
    return ret;
}

int printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int ret = vsprintf(temp_buffer, fmt, args);
    putstr(temp_buffer);
    va_end(args);
    return ret;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
    panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
    panic("Not implemented");
}

#endif
