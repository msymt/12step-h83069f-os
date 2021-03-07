#ifndef _INTERRUPT_H_INCLUDED_
#define _INTERRUPT_H_INCLUDED_

/* �ʲ��ϥ�󥫡�������ץȤ�������Ƥ��륷��ܥ� */
extern char softvec;
#define SOFTVEC_ADDR (&softvec)

// ���եȥ������������ߥ٥����μ��̤�ɽ���������
typedef short softvec_type_t;
// �����ߥϥ�ɥ�η������
typedef void (*softvec_handler_t)(softvec_type_t type, unsigned long sp);
// ���եȥ������������ߥ٥����ΰ���
#define SOFTVECS ((softvec_handler_t *)SOFTVEC_ADDR)

#define INTR_ENABLE asm volatile("andc.b #0x3f,ccr")  // ������ͭ����
#define INTR_DISABLE asm volatile("orc.b #0xc0,ccr")  // ����̵�����ʶػߡ�

/* ���եȥ�����������ߥ٥����ν���� */
int softvec_init(void);

/* ���եȥ�����������ߥ٥��������� */
int softvec_setintr(softvec_type_t type, softvec_handler_t handler);

/* ���̳���ߥϥ�ɥ� */
void interrupt(softvec_type_t type, unsigned long sp);

#endif