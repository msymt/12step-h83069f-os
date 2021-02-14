#include "lib.h"

#include "defines.h"
#include "serial.h"

// メモリを特定パターンで埋める
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

// 長さ制限ありで文字列の比較を行う
int strncmp(const char *s1, const char *s2, int len) {
    while ((*s1 || *s2) && (len > 0)) {
        if (*s1 != *s2) return (*s1 > *s2) ? 1 : -1;
        s1++;
        s2++;
        len--;
    }
    return 0;
}

// 1文字送信
int putc(unsigned char c) {
    if (c == '\n') serial_send_byte(SERIAL_DEFAULT_DEVICE, '\r');
    return serial_send_byte(SERIAL_DEFAULT_DEVICE, c);
}

// 1文字受信
unsigned char getc(void) {
    unsigned char c = serial_recv_byte(SERIAL_DEFAULT_DEVICE);
    c = (c == '\r') ? '\n' : c;  // 改行コードの変換
    putc(c);                     // エコー・バック
    return c;
}

// 文字列送信
int puts(unsigned char *str) {
    while (*str) putc(*(str++));
    return 0;
}

/**
 *  文字列受信
 *  buf: コンソールからの１行受信
 */
int gets(unsigned char *buf) {
    int i = 0;
    unsigned char c;
    do {
        c = getc();               // 1文字受信
        if (c == '\n') c = '\0';  // 改行コード：削る
        buf[i++] = c;
    } while (c);
    return i - 1;
}

/**
 * 数値の16進表示
 * value: 表示したい値
 * column: 表示桁数
 */
int putxval(unsigned long value, int column) {
    char buf[9];  //  文字列出力用バッファ
    char *p;

    // 下の桁から処理するので，バッファの終端から利用
    p = buf + sizeof(buf) - 1;  // 先頭 + サイズ分 - 1
    *(p--) = '\0';

    if (!value || column) column++;

    while (value || column) {
        *(p--) =
            "0123456789abcdef"[value & 0xf];  // 16進数に変換してバッファに格納
        value >>= 4;           // 次の桁に進める(下4ビット)
        if (column) column--;  // 桁数指定がある場合にはカウント
    }

    puts(p + 1);

    return 0;
}
