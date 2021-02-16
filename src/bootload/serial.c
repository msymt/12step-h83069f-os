#include "serial.h"

#include "defines.h"

#define SERIAL_SCI_NUM 3

// SCI(���ꥢ�롦����ȥ���)�����
#define H8_3069F_SCI0 ((volatile struct h8_3069f_sci *)0xffffb0)
#define H8_3069F_SCI1 ((volatile struct h8_3069f_sci *)0xffffb8)
#define H8_3069F_SCI2 ((volatile struct h8_3069f_sci *)0xffffc0)

/**
 * SCI�Ƽ�쥸���������
 * smr: ���ꥢ��⡼�ɥ쥸���������ꥢ�������ϤΥѥ�᡼�������Ԥ�
 * scr: ���ꥢ�륳��ȥ���쥸���������ꥢ�������Ϥ������Ԥ�
 * (����: ��������ͭ��/̵�����ڤ��ؤ��������ߤ�ͭ��/̵�����ڤ��ؤ��ʤ�)
 * brr: �ӥåȥ졼�ȥ쥸���������ꥢ���̿���®��(�ݡ��졼��)������
 * tdr: �ȥ�󥹥ߥåȥǡ����쥸����
 * ssr: ���ꥢ�륹�ơ������쥸����
 */
struct h8_3069f_sci {
    volatile uint8 smr;  // ���ꥢ���̿��Υ⡼������
    volatile uint8 brr;  // ���ꥢ���ž��®��(�ݡ��졼��)������
    volatile uint8 scr;  // ��������ͭ��/̵���ʤ�
    volatile uint8 tdr;  // ������������ʸ����񤭹���
    volatile uint8 ssr;  // ������λ/������λ�ʤɤ�ɽ��
    volatile uint8 rdr;  // ����������ʸ�����ɤ߽Ф�
    volatile uint8 scmr;
};

// SMR�γƥӥåȤ����
#define H8_3069F_SCI_SMR_CKS_PER1 (0 << 0)
#define H8_3069F_SCI_SMR_CKS_PER4 (1 << 0)
#define H8_3069F_SCI_SMR_CKS_PER16 (2 << 0)
#define H8_3069F_SCI_SMR_CKS_PER64 (3 << 0)
#define H8_3069F_SCI_SMR_MP (1 << 2)
#define H8_3069F_SCI_SMR_STOP (1 << 3)
#define H8_3069F_SCI_SMR_OE (1 << 4)
#define H8_3069F_SCI_SMR_PE (1 << 5)
#define H8_3069F_SCI_SMR_CHR (1 << 6)
#define H8_3069F_SCI_SMR_CA (1 << 7)

// SCR�γƥӥåȤ����
#define H8_3069F_SCI_SCR_CKE0 (1 << 0)
#define H8_3069F_SCI_SCR_CKE1 (1 << 1)
#define H8_3069F_SCI_SCR_TEIE (1 << 2)
#define H8_3069F_SCI_SCR_MPIE (1 << 3)
#define H8_3069F_SCI_SCR_RE (1 << 4)  /* ����ͭ�� */
#define H8_3069F_SCI_SCR_TE (1 << 5)  /* ����ͭ�� */
#define H8_3069F_SCI_SCR_RIE (1 << 6) /* ���������ͭ�� */
#define H8_3069F_SCI_SCR_TIE (1 << 7) /* ���������ͭ�� */

// SSR�γƥӥåȤ����
#define H8_3069F_SCI_SSR_MPBT (1 << 0)
#define H8_3069F_SCI_SSR_MPB (1 << 1)
#define H8_3069F_SCI_SSR_TEND (1 << 2)
#define H8_3069F_SCI_SSR_PER (1 << 3)
#define H8_3069F_SCI_SSR_FERERS (1 << 4)
#define H8_3069F_SCI_SSR_ORER (1 << 5)
#define H8_3069F_SCI_SSR_RDRF (1 << 6) /* ������λ */
#define H8_3069F_SCI_SSR_TDRE (1 << 7) /* ������λ */

static struct {
    volatile struct h8_3069f_sci *sci;
} regs[SERIAL_SCI_NUM] = {
    // ���С�SCI�쥸����������Ƭ���ɥ쥹��ؤ�
    {H8_3069F_SCI0},
    {H8_3069F_SCI1},
    {H8_3069F_SCI2},
};

// �ǥХ��������, index:SCI���ֹ�
int serial_init(int index) {
    volatile struct h8_3069f_sci *sci = regs[index].sci;

    // �ʲ�SCI�Υ쥸����������
    sci->scr = 0;  // ���ꥢ���������ȳ����ߤ�̵����
    sci->smr = 0;
    sci->brr = 64;  // 20MHz�Υ���å�����9600bps������(25MHz�ξ���80�ˤ���)
    sci->scr = H8_3069F_SCI_SCR_RE | H8_3069F_SCI_SCR_TE;  // ��������ǽ
    sci->ssr = 0;

    return 0;
}

// ������ǽ��
int serial_is_send_enable(int index) {
    volatile struct h8_3069f_sci *sci = regs[index].sci;
    return (sci->ssr & H8_3069F_SCI_SSR_TDRE);
}

// 1ʸ������
int serial_send_byte(int index, unsigned char c) {
    volatile struct h8_3069f_sci *sci = regs[index].sci;

    // ������ǽ�ˤʤ�ޤ��Ԥ�(������λ�ӥåȤ�����Ƥ��ʤ��ʤ鼡��)
    while (!serial_is_send_enable(index))
        ;
    sci->tdr = c;  // ����������ʸ���ν񤭹���
    sci->ssr &=
        ~H8_3069F_SCI_SSR_TDRE;  // �������ϡ�ssr��������λ�ӥåȤ�Ω�Ƥ�

    return 0;
}

/* ������ǽ���� */
int serial_is_recv_enable(int index) {
    volatile struct h8_3069f_sci *sci = regs[index].sci;
    return (sci->ssr & H8_3069F_SCI_SSR_RDRF);
}

/* ��ʸ������ */
unsigned char serial_recv_byte(int index) {
    volatile struct h8_3069f_sci *sci = regs[index].sci;
    unsigned char c;

    /* ����ʸ�������ޤ��Ԥ� */
    while (!serial_is_recv_enable(index))
        ;
    c = sci->rdr;
    // �ǡ����μ����塤SSR��RDRF�ӥåȤ���Ȥ����Ȥǡ�SCI�˼�����λ������
    sci->ssr &= ~H8_3069F_SCI_SSR_RDRF; /* ������λ */

    return c;
}
