#include "defines.h"

extern void start(void); /* �������ȡ����å� */
// �����ߥϥ�ɥ�
extern void intr_softerr(void); /* ���եȥ����������顼 */
extern void intr_syscall(void); /* �����ƥࡦ������ */
extern void intr_serintr(void); /* ���ꥢ������ */

/*
 * ����ߥ٥��������ꡥ
 * ��󥫡�������ץȤ�����ˤ�ꡤ�ե�å���ROM����Ƭ���Ϥ����֤���롥
 * 8~11:�ȥ�å�̿��: syscall,softerr,
 * SOFTVEC_TYPE_SYSCALL,SOFTVEC_TYPE_SOFTERR �����ꤵ�줿�ϥ�ɥ�
 * 52~63: ���ꥢ���Ϣ�γ�����:serintr,SOFTVEC_TYPE_SERINTR
 * �����ꤵ�줿�ϥ�ɥ�
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
