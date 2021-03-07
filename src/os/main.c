#include "defines.h"
#include "interrupt.h"
#include "intr.h"
#include "lib.h"
#include "serial.h"

// �����ߥϥ�ɥ�
static void intr(softvec_type_t type, unsigned long sp) {
    int c;
    static char buf[32];  // �����Хåե������
    static int len;

    c = getc();  // ���������ߤ����ä��Τǡ����󥽡��뤫��1ʸ������

    if (c != '\n') {  // ���������Τ����ԤǤʤ���硤�����Хåե�����¸
        buf[len++] = c;
    } else {  // ���Ԥ����������硤���ޥ�ɽ�����Ԥ�
        buf[len++] = '\0';
        if (!strncmp(buf, "echo", 4)) {  // echo���ޥ�ɤξ��
            // ��³��ʸ��������
            puts(buf + 4);
            puts("\n");
        } else {
            // �����ʥ��ޥ�ɻ�
            puts("unknown.\n");
        }
        puts("> ");
        len = 0;
    }
}

int main(void) {
    INTR_DISABLE; /* �����̵���ˤ��� */

    puts("kozos boot succeed!\n");

    // ���եȥ����������ߥ٥����˥��ꥢ������ߤΥϥ�ɥ������
    softvec_setintr(SOFTVEC_TYPE_SERINTR, intr);
    // ���ꥢ����������ߤ�ͭ����
    serial_intr_recv_enable(SERIAL_DEFAULT_DEVICE);
    puts("> ");

    INTR_ENABLE; /* �����ͭ���ˤ��� */
    while (1) {
        asm volatile("sleep"); /* �����ϥ⡼�ɤ˰ܹ� */
    }
    return 0;
}
