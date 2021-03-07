#include "interrupt.h"

#include "defines.h"
#include "intr.h"

// ソフトウェア・割り込みベクタの初期化
int softvec_init(void) {
    int type;
    // 全てのソフトウェア・割り込みベクタをNULL
    for (type = 0; type < SOFTVEC_TYPE_NUM; type++) softvec_setintr(type, NULL);
    return 0;
}

// ソフトウェア・割り込みベクタの設定
int softvec_setintr(softvec_type_t type, softvec_handler_t handler) {
    SOFTVECS[type] = handler;
    return 0;
}

// 共通割り込みハンドラ
// ソフトウェア・割り込みベクタをみて，各ハンドラに分岐
void interrupt(softvec_type_t type, unsigned long sp) {
    softvec_handler_t handler = SOFTVECS[type];
    // 設定されているならば，ハンドラを呼び出す
    if (handler) handler(type, sp);
}
