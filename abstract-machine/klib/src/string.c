#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

/* 字符串长度 */
size_t strlen(const char *s) {
    const char* p = s;
    while (*p != '\0') {
        p += 1;
    }
    return p - s;
}
 
/* 将字符串从src复制到dst */
char *strcpy(char *dst, const char *src) {
    assert(dst != NULL && src != NULL);
    char* ret = dst;
    while((*dst++ = *src++));
    return ret;
}

/* 把 rc所指向的字符串复制到dst, 最多复制n个字符. 当src的长度小于n时, dst的剩余部分将用空字节填充. */
char *strncpy(char *dst, const char *src, size_t n) {
    assert(dst != NULL && src != NULL && n > 0);
    char* ret = dst;
    while(n-- && (*dst++ = *src++));
    if (n > 0) {
        while (n > 0) {
            n -= 1;
            *dst++ = '\0';
        }
    }

    return ret;
}

/* 将字符串src拼接到dest后, 返回拼接的串地址 */
char *strcat(char *dst, const char *src) {
    assert(dst != NULL && src != NULL);
    char* ret = dst;
    while(*dst++ != '\0') ;
    -- dst;
    while (*src != '\0') {
        *dst++ = *src++;
    }
    
    return ret;
}

/* 比较两个字符串, s1=b返回0, 若s1>b返回1, s1<s2返回-1 */
int strcmp(const char *s1, const char *s2) {
    assert(s1 != NULL && s2 != NULL);
    while (*s1 != '\0' && *s1 == *s2) {
        s1++; s2++;
    }
    return *s1 - *s2;
}

/* 把str1和str2进行比较, 最多比较前n个字节 */
int strncmp(const char *s1, const char *s2, size_t n) {
    assert(s1 != NULL && s2 != NULL);
    while (n --) {
        if (*s1 == 0 || *s1 != *s2) {
            return *s1 - *s2;
        }
        s1 += 1; s2 += 1;
    }
    return 0;
}

/* 将s起始的n个字节置为c */
void *memset(void *s, int c, size_t n) {
    assert(s != NULL);
    assert(n > 0);
    char* dst = s;
    // *p++ 先取指针p指向的值, 再将指针p自增1.
    while (n-- > 0) {
        *dst++ = c;
    }
    return s;
}

void *memmove(void *dst, const void *src, size_t n) {
    assert(src != NULL && dst != NULL && n > 0);
    char* _dst = NULL;
    char* _src = NULL;
    // 从前往后复制
    if (dst < src) {
        _dst = (char*)dst; _src = (char*)src;
        while (n --) {
            *_dst ++ = *_src ++;
        }
    }
    // 从后往前复制
    else if (dst > src) {
        _dst = (char*)dst + n; _src = (char*)src + n;
        while (n --) {
            * --_dst = * --_src;
        }
    }
    return dst;
}

/* 将in起始的n个字节复制到out */
void *memcpy(void *out, const void *in, size_t n) {
    assert(out != NULL && in != NULL);

    char* dst = out;
    const char* src = in;
    while (n-- > 0) {
        *dst++ = *src++;
    }
    return out;
}

/* 连续比较以地址a和地址b开头的n个字节; 若a==b返回0, 若a>b返回+1, 若a<b返回-1 */
int memcmp(const void *s1, const void *s2, size_t n) {
    assert(s1 != NULL && s2 != NULL && n > 0);
    const char* a = s1;
    const char* b = s2;
    while (n-- > 0) {
        if (*a != *b) {
            return (*a > *b) ? 1 : -1;
        }
        ++a; ++b;
    }
    return 0;
}

#endif
