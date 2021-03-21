#ifndef _DEFINES_H_INCLUDED_
#define _DEFINES_H_INCLUDED_

#define NULL ((void *)0)
#define SERIAL_DEFAULT_DEVICE 1

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;

/* OS�����Ѥ���뷿����� */
typedef uint32 kz_thread_id_t;                     // ����å�ID
typedef int (*kz_func_t)(int argc, char *argv[]);  // ����åɤΥᥤ��ؿ��η�
typedef void (*kz_handler_t)(void);  // �����ߥϥ�ɥ�η�

#endif
