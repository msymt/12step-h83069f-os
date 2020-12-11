#include "defines.h"
#include "serial.h"
#include "lib.h"

static int init(void) {
    // 以下，リンカ・スクリプトで定義済みのシンボル
    // リンカ・スクリプトで定義されたシンボルを参照可能にする
    extern int erodata, data_start, edata, bss_start, ebss;
    
    /**
     * データ領域とBSS領域を初期化．
     * 注：この処理以降でないと，グローバル変数が初期化されていない
     */
    memcpy(&data_start, &erodata, (long)&edata - (long)&data_start);
    memset(&bss_start, 0, (long)&ebss - (long)&bss_start);  // zero clear

    // initilize serial device
    serial_init(SERIAL_DEFAULT_DEVICE);
    return 0;
}

int global_data = 0x10;
int global_bss;
static int static_data = 0x20;
static int static_bss;

static void printval(void)
{
  puts("global_data = "); putxval(global_data, 0); puts("\n");
  puts("global_bss  = "); putxval(global_bss,  0); puts("\n");
  puts("static_data = "); putxval(static_data, 0); puts("\n");
  puts("static_bss  = "); putxval(static_bss,  0); puts("\n");
}

int main(void) {
    init();
    puts("Hello World!\n");

    printval();
    puts("overwrite variables.\n");
    global_data = 0x20;
    global_bss = 0x30;
    static_data = 0x40;
    static_bss = 0x50;
    printval();
    
    while (1) ;

    return 0;
}
