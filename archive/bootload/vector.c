#include "defines.h"

// start up
extern void start(void); 

/**
 * 割り込みベクタ.
 * リンカ・スクリプトの定義により，先頭番地に配置される
 * 「一番最初に実行開始するアドレス」を定義.
 * 
 * start(): CPUが一番最初に実行を開始する位置(_start)
 */
void (*vectors[])(void) = {
  start, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
};
