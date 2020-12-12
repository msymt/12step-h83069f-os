#ifndef _LIB_H_INCLUDED_
#define _LIB_H_INCLUDED_

void *memset(void *b, int c, long len);
void *memcpy(void *dst, const void *src, long len);
int memcmp(const void *b1, const void *b2, long len);
int strlen(const char *s);
char *strcpy(char *dst, const char *scr);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2,
            int len);  // Ĺ�����¤����ʸ�������Ӥ�Ԥ�

int putc(unsigned char c);     // 1ʸ������
unsigned char getc(void);      /* ��ʸ������ */
int gets(unsigned char *buf);  /* ʸ������� */
int puts(unsigned char *str);  // ʸ��������
/**
 * ���ͤ�16��ɽ��
 * value: ɽ����������
 * column: ɽ�����
 */
int putxval(unsigned long value, int column);
#endif
