#ifndef _KOZOS_H_INCLUDED_
#define _KOZOS_H_INCLUDED_

#include "defines.h"
#include "syscall.h"

/* �����ƥॳ����*/
// ����åɵ�ư�Υ����ƥॳ����
kz_thread_id_t kz_run(kz_func_t func, char *name, int stacksize, int argc,
                      char *argv[]);
// ����åɽ�λ�Υ����ƥॳ����
void kz_exit(void);

// �饤�֥��ؿ�
// �������åɤ�ư����OS��ư��򳫻Ϥ���
void kz_start(kz_func_t func, char *name, int stacksize, int argc,
              char *argv[]);
// ��̿Ū���顼���˸ƤӽФ�
void kz_sysdown(void);
// �����ƥॳ����μ¹�
void kz_syscall(kz_syscall_type_t type, kz_syscall_param_t *param);

// �桼������åɤΥᥤ��ؿ�
int test08_1_main(int argc, char *argv[]);

#endif
