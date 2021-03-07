# 割り込みハンドラの入り口・出口
# .S: プリ・プロセスが行われる
# .s: 行われない
#include "intr.h"
    .h8300h
    .section .text

    .global _intr_softerr
#   .type   _intr_softerr,@function
# software error
_intr_softerr:
    # 汎用レジスタの値をスタックに保存
	mov.l	er6,@-er7
	mov.l	er5,@-er7
	mov.l	er4,@-er7
	mov.l	er3,@-er7
	mov.l	er2,@-er7
	mov.l	er1,@-er7
	mov.l	er0,@-er7
    mov.l	er7,er1     # 第二引数にスタックポインタを設定(32bit, ポインタ値(H8/3069Fのアドレス範囲:24bit))
	mov.w	#SOFTVEC_TYPE_SOFTERR,r0    # 第一引数にintr.hのSOFTVEC_TYPE_softerrを設定(16bit)
	jsr	@_interrupt # interrupt()の呼び出し(interrupt.c)
	# スタックから汎用レジスタの値を復旧
    mov.l	@er7+,er0
	mov.l	@er7+,er1
	mov.l	@er7+,er2
	mov.l	@er7+,er3
	mov.l	@er7+,er4
	mov.l	@er7+,er5
	mov.l	@er7+,er6
	# 割り込み復帰命令
    rte

	.global	_intr_syscall
#	.type	_intr_syscall,@function
# システムコール
_intr_syscall:
	mov.l	er6,@-er7
	mov.l	er5,@-er7
	mov.l	er4,@-er7
	mov.l	er3,@-er7
	mov.l	er2,@-er7
	mov.l	er1,@-er7
	mov.l	er0,@-er7
	mov.l	er7,er1
	mov.w	#SOFTVEC_TYPE_SYSCALL,r0
	jsr	@_interrupt
	mov.l	@er7+,er0
	mov.l	@er7+,er1
	mov.l	@er7+,er2
	mov.l	@er7+,er3
	mov.l	@er7+,er4
	mov.l	@er7+,er5
	mov.l	@er7+,er6
	rte

	.global	_intr_serintr
#	.type	_intr_serintr,@function
# シリアル割り込み
_intr_serintr:
	mov.l	er6,@-er7
	mov.l	er5,@-er7
	mov.l	er4,@-er7
	mov.l	er3,@-er7
	mov.l	er2,@-er7
	mov.l	er1,@-er7
	mov.l	er0,@-er7
	mov.l	er7,er1
	mov.w	#SOFTVEC_TYPE_SERINTR,r0
	jsr	@_interrupt
	mov.l	@er7+,er0
	mov.l	@er7+,er1
	mov.l	@er7+,er2
	mov.l	@er7+,er3
	mov.l	@er7+,er4
	mov.l	@er7+,er5
	mov.l	@er7+,er6
	rte
