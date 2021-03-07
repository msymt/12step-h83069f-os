#include "defines.h"
#include "interrupt.h"
#include "intr.h"
#include "lib.h"
#include "serial.h"

// 割り込みハンドラ
static void intr(softvec_type_t type, unsigned long sp) {
    int c;
    static char buf[32];  // 受信バッファの定義
    static int len;

    c = getc();  // 受信割り込みが入ったので，コンソールから1文字受信

    if (c != '\n') {  // 受信したのが改行でない場合，受信バッファに保存
        buf[len++] = c;
    } else {  // 改行を受信した場合，コマンド処理を行う
        buf[len++] = '\0';
        if (!strncmp(buf, "echo", 4)) {  // echoコマンドの場合
            // 後続の文字列を出力
            puts(buf + 4);
            puts("\n");
        } else {
            // 不明なコマンド時
            puts("unknown.\n");
        }
        puts("> ");
        len = 0;
    }
}

int main(void) {
    INTR_DISABLE; /* 割込み無効にする */

    puts("kozos boot succeed!\n");

    // ソフトウェア割り込みベクタにシリアル割り込みのハンドラを設定
    softvec_setintr(SOFTVEC_TYPE_SERINTR, intr);
    // シリアル受信割り込みを有効化
    serial_intr_recv_enable(SERIAL_DEFAULT_DEVICE);
    puts("> ");

    INTR_ENABLE; /* 割込み有効にする */
    while (1) {
        asm volatile("sleep"); /* 省電力モードに移行 */
    }
    return 0;
}
