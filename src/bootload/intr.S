# �����ߥϥ�ɥ����������и�
# .S: �ץꡦ�ץ��������Ԥ���
# .s: �Ԥ��ʤ�
#include "intr.h"
    .h8300h
    .section .text

    .global _intr_softerr
#   .type   _intr_softerr,@function
# software error
_intr_softerr:
    # ���ѥ쥸�������ͤ򥹥��å�����¸
	mov.l	er6,@-er7
	mov.l	er5,@-er7
	mov.l	er4,@-er7
	mov.l	er3,@-er7
	mov.l	er2,@-er7
	mov.l	er1,@-er7
	mov.l	er0,@-er7
    mov.l	er7,er1     # ��������˥����å��ݥ��󥿤�����(32bit, �ݥ�����(H8/3069F�Υ��ɥ쥹�ϰ�:24bit))
	mov.w	#SOFTVEC_TYPE_SOFTERR,r0    # ��������intr.h��SOFTVEC_TYPE_softerr������(16bit)
	jsr	@_interrupt # interrupt()�θƤӽФ�(interrupt.c)
	# �����å��������ѥ쥸�������ͤ�����
    mov.l	@er7+,er0
	mov.l	@er7+,er1
	mov.l	@er7+,er2
	mov.l	@er7+,er3
	mov.l	@er7+,er4
	mov.l	@er7+,er5
	mov.l	@er7+,er6
	# ����������̿��
    rte

	.global	_intr_syscall
#	.type	_intr_syscall,@function
# �����ƥॳ����
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
# ���ꥢ�������
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