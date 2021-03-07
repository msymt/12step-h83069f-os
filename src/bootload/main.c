#include "defines.h"
#include "elf.h"
#include "interrupt.h"
#include "lib.h"
#include "serial.h"
#include "xmodem.h"

static int init(void) {
    /* 以下はリンカ・スクリプトで定義してあるシンボル */
    extern int erodata, data_start, edata, bss_start, ebss;

    /*
     * データ領域とBSS領域を初期化する．この処理以降でないと，
     * グローバル変数が初期化されていないので注意．
     */
    memcpy(&data_start, &erodata, (long)&edata - (long)&data_start);
    memset(&bss_start, 0, (long)&ebss - (long)&bss_start);

    // ソフトウェア・割り込みベクタの初期化
    softvec_init();

    /* シリアルの初期化 */
    serial_init(SERIAL_DEFAULT_DEVICE);

    return 0;
}

/* メモリの16進ダンプ出力 */
static int dump(char *buf, long size) {
    long i;

    if (size < 0) {
        puts("no data.\n");
        return -1;
    }
    for (i = 0; i < size; i++) {
        putxval(buf[i], 2);
        if ((i & 0xf) == 15) {
            puts("\n");
        } else {
            if ((i & 0xf) == 7) puts(" ");
            puts(" ");
        }
    }
    puts("\n");

    return 0;
}

static void wait() {
    volatile long i;
    for (i = 0; i < 300000; i++)
        ;
}

int main(void) {
    static char buf[16];
    static long size = -1;
    static unsigned char *loadbuf = NULL;
    extern int buffer_start; /* リンカ・スクリプトで定義されているバッファ */
    char *entry_point;
    void (*f)(void);

    // 割込み無効にする
    INTR_DISABLE; /* 最初の初期化処理は割り込み無効の状態で行う */

    init();

    puts("kzload (kozos boot loader) started.\n");

    while (1) {
        puts("kzload> "); /* プロンプト表示 */
        gets(buf);        /* シリアルからのコマンド受信 */

        if (!strcmp(buf, "load")) { /* XMODEMでのファイルのダウンロード */
            loadbuf = (char *)(&buffer_start);
            size = xmodem_recv(loadbuf);
            wait(); /* 転送アプリが終了し端末アプリに制御が戻るまで待ち合わせる
                     */
            if (size < 0) {
                puts("\nXMODEM receive error!\n");
            } else {
                puts("\nXMODEM receive succeeded.\n");
            }
        } else if (!strcmp(buf, "dump")) { /* メモリの16進ダンプ出力 */
            puts("size: ");
            putxval(size, 0);
            puts("\n");
            dump(loadbuf, size);
        } else if (!strcmp(buf, "run")) { /* ELF形式ファイルの実行 */
            /* メモリ上に展開(ロード) */
            entry_point = elf_load(loadbuf);  // エントリポイント
            if (!entry_point) {
                puts("run error!\n");
            } else {
                puts("starting from entry point: ");
                putxval((unsigned long)entry_point, 0);
                puts("\n");
                // 受け取ったエントリ・ポイントを関数へのポインタに代入
                f = (void (*)(void))entry_point;
                f();  // ここでロードしたプログラムに処理を渡す
                // ここには返ってこない
            }
        } else {
            puts("unknown.\n");
        }
    }

    return 0;
}
