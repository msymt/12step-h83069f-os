#include "defines.h"

extern void start(void); /* スタート・アップ */
// 割り込みハンドラ
extern void intr_softerr(void); /* ソフトウエア・エラー */
extern void intr_syscall(void); /* システム・コール */
extern void intr_serintr(void); /* シリアル割込み */

/*
 * 割込みベクタの設定．
 * リンカ・スクリプトの定義により，フラッシュROMの先頭番地に配置される．
 * 8~11:トラップ命令: syscall,softerr,
 * SOFTVEC_TYPE_SYSCALL,SOFTVEC_TYPE_SOFTERR で設定されたハンドラ
 * 52~63: シリアル関連の割り込み:serintr,SOFTVEC_TYPE_SERINTR
 * で設定されたハンドラ
 */
void (*vectors[])(void) = {
    start,        NULL,         NULL,         NULL,         NULL,
    NULL,         NULL,         NULL,         intr_syscall, intr_softerr,
    intr_softerr, intr_softerr, NULL,         NULL,         NULL,
    NULL,         NULL,         NULL,         NULL,         NULL,
    NULL,         NULL,         NULL,         NULL,         NULL,
    NULL,         NULL,         NULL,         NULL,         NULL,
    NULL,         NULL,         NULL,         NULL,         NULL,
    NULL,         NULL,         NULL,         NULL,         NULL,
    NULL,         NULL,         NULL,         NULL,         NULL,
    NULL,         NULL,         NULL,         NULL,         NULL,
    NULL,         NULL,         intr_serintr, intr_serintr, intr_serintr,
    intr_serintr, intr_serintr, intr_serintr, intr_serintr, intr_serintr,
    intr_serintr, intr_serintr, intr_serintr, intr_serintr,
};
