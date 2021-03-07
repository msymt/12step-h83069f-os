#include "interrupt.h"

#include "defines.h"
#include "intr.h"

// ���եȥ������������ߥ٥����ν����
int softvec_init(void) {
    int type;
    // ���ƤΥ��եȥ������������ߥ٥�����NULL
    for (type = 0; type < SOFTVEC_TYPE_NUM; type++) softvec_setintr(type, NULL);
    return 0;
}

// ���եȥ������������ߥ٥���������
int softvec_setintr(softvec_type_t type, softvec_handler_t handler) {
    SOFTVECS[type] = handler;
    return 0;
}

// ���̳����ߥϥ�ɥ�
// ���եȥ������������ߥ٥�����ߤơ��ƥϥ�ɥ��ʬ��
void interrupt(softvec_type_t type, unsigned long sp) {
    softvec_handler_t handler = SOFTVECS[type];
    // ���ꤵ��Ƥ���ʤ�С��ϥ�ɥ��ƤӽФ�
    if (handler) handler(type, sp);
}
