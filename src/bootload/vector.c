#include "defines.h"

// start up
extern void start(void); 

/**
 * interrupt vector setting.
 * ��󥫡�������ץȤ�����ˤ�ꡤ��Ƭ���Ϥ����֤����
 * �ְ��ֺǽ�˼¹Գ��Ϥ��륢�ɥ쥹�פ����.
 */

/**
 * start(): CPU�����ֺǽ�˼¹Ԥ򳫻Ϥ������
 */
void (*vectors[])(void) = {
  start, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
};
