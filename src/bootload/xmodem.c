#include "xmodem.h"

#include "defines.h"
#include "lib.h"
#include "serial.h"

/**
 * ���楳���ɤ����
 */
#define XMODEM_SOH 0x01
#define XMODEM_STX 0x02
#define XMODEM_EOT 0x04
#define XMODEM_ACK 0x06
#define XMODEM_NAK 0x15
#define XMODEM_CAN 0x18
#define XMODEM_EOF 0x1a /* Ctrl-Z */

#define XMODEM_BLOCK_SIZE 128

// �������Ϥ����ޤ������׵��Ф�
static int xmodem_wait(void) {
    long cnt = 0;

    // �������Ϥ���ޤǡ�NAK�����Ū������, ����8�ôֳ֤�NAK������
    while (!serial_is_recv_enable(SERIAL_DEFAULT_DEVICE)) {
        if (++cnt >= 2000000) {
            cnt = 0;
            serial_send_byte(SERIAL_DEFAULT_DEVICE, XMODEM_NAK);
        }
    }

    return 0;
}

// �֥�å�ñ�̤Ǥμ���
static int xmodem_read_block(unsigned char block_number, char *buf) {
    unsigned char c, block_num, check_sum;
    int i;

    block_num = serial_recv_byte(SERIAL_DEFAULT_DEVICE);  // �֥�å��ֹ�μ���
    if (block_num != block_number) return -1;

    block_num ^= serial_recv_byte(
        SERIAL_DEFAULT_DEVICE);  // ȿž�����֥�å��ֹ�μ���, ^: XOR
    if (block_num != 0xff) return -1;

    check_sum = 0;
    // 128�Х��ȤΥǡ��������
    for (i = 0; i < XMODEM_BLOCK_SIZE; i++) {
        c = serial_recv_byte(SERIAL_DEFAULT_DEVICE);
        *(buf++) = c;
        check_sum += c;
    }

    check_sum ^= serial_recv_byte(SERIAL_DEFAULT_DEVICE);
    // ���פ��Ƥ��ʤ����Τߥ���ʳ��Ȥʤ�
    if (check_sum) return -1;

    return i;
}

/**
 * �������Хåե�
 * XMODEM�ˤ������򳫻Ϥ�����������ɤ����ե������Хåե��˳�Ǽ
 * ����͡��ե�����Υ����������顼����-1
 */
long xmodem_recv(char *buf) {
    int r, receiving = 0;
    long size = 0;
    unsigned char c, block_number = 1;

    while (1) {
        if (!receiving)
            xmodem_wait();  // �������Ϥ����ޤ������׵��Ф�,
                            // ���Ū��NAK������

        c = serial_recv_byte(SERIAL_DEFAULT_DEVICE);  // 1ʸ���μ���

        if (c == XMODEM_EOT) {  // ������λ, EOT����������齪λ
            serial_send_byte(SERIAL_DEFAULT_DEVICE, XMODEM_ACK);
            break;
        } else if (c == XMODEM_CAN) {  // CAN���������������
            return -1;
        } else if (c == XMODEM_SOH) {  // SOH�����������ǡ��������򳫻�
            receiving++;
            r = xmodem_read_block(block_number, buf); /* �֥�å�ñ�̤Ǥμ��� */
            if (r < 0) {                              /* �������顼 */
                serial_send_byte(SERIAL_DEFAULT_DEVICE, XMODEM_NAK);
            } else { /* ������� */
                // ������ˤϥХåե��Υݥ��󥿤�ʤ�ACK���֤�
                block_number++;
                size += r;
                buf += r;
                serial_send_byte(SERIAL_DEFAULT_DEVICE, XMODEM_ACK);
            }
        } else {
            if (receiving) return -1;
        }
    }

    return size;
}
