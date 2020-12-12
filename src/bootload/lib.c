#include "lib.h"

#include "defines.h"
#include "serial.h"

// ���������ѥ����������
void *memset(void *b, int c, long len) {
    char *p;
    for (p = b; len > 0; len--) *(p++) = c;
    return b;
}

void *memcpy(void *dst, const void *src, long len) {
    char *d = dst;
    const char *s = src;
    for (; len > 0; len--) *(d++) = *(s++);
    return dst;
}

int memcmp(const void *b1, const void *b2, long len) {
    const char *p1 = b1, *p2 = b2;
    for (; len > 0; len--) {
        if (*p1 != *p2) return (*p1 > *p2) ? 1 : -1;
        p1++;
        p2++;
    }
    return 0;
}
int strlen(const char *s) {
    int len;
    for (len = 0; *s; s++, len++)
        ;
    return len;
}
char *strcpy(char *dst, const char *src) {
    char *d = dst;
    for (;; dst++, src++) {
        *dst = *src;
        if (!*src) break;
    }
    return d;
}
int strcmp(const char *s1, const char *s2) {
    while (*s1 || *s2) {
        if (*s1 != *s2) return (*s1 > *s2) ? 1 : -1;
        s1++;
        s2++;
    }
    return 0;
}

// Ĺ�����¤����ʸ�������Ӥ�Ԥ�
int strncmp(const char *s1, const char *s2, int len) {
    while ((*s1 || *s2) && (len > 0)) {
        if (*s1 != *s2) return (*s1 > *s2) ? 1 : -1;
        s1++;
        s2++;
        len--;
    }
    return 0;
}

// 1ʸ������
int putc(unsigned char c) {
    if (c == '\n') serial_send_byte(SERIAL_DEFAULT_DEVICE, '\r');
    return serial_send_byte(SERIAL_DEFAULT_DEVICE, c);
}

// 1ʸ������
unsigned char getc(void) {
    unsigned char c = serial_recv_byte(SERIAL_DEFAULT_DEVICE);
    c = (c == '\r') ? '\n' : c;  // ���ԥ����ɤ��Ѵ�
    putc(c);                     // ���������Хå�
    return c;
}

// ʸ��������
int puts(unsigned char *str) {
    while (*str) putc(*(str++));
    return 0;
}

/**
 *  ʸ�������
 *  buf: ���󥽡��뤫��Σ��Լ���
 */
int gets(unsigned char *buf) {
    int i = 0;
    unsigned char c;
    do {
        c = getc();               // 1ʸ������
        if (c == '\n') c = '\0';  // ���ԥ����ɡ����
        buf[i++] = c;
    } while (c);
    return i - 1;
}

/**
 * ���ͤ�16��ɽ��
 * value: ɽ����������
 * column: ɽ�����
 */
int putxval(unsigned long value, int column) {
    char buf[9];  //  ʸ��������ѥХåե�
    char *p;

    // ���η夫���������Τǡ��Хåե��ν�ü��������
    p = buf + sizeof(buf) - 1;  // ��Ƭ + ������ʬ - 1
    *(p--) = '\0';

    if (!value || column) column++;

    while (value || column) {
        *(p--) =
            "0123456789abcdef"[value & 0xf];  // 16�ʿ����Ѵ����ƥХåե��˳�Ǽ
        value >>= 4;           // ���η�˿ʤ��(��4�ӥå�)
        if (column) column--;  // ������꤬������ˤϥ������
    }

    puts(p + 1);

    return 0;
}
