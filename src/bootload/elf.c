#include "elf.h"

#include "defines.h"
#include "lib.h"

// ELF�إå�����Ϥ��뤿��
struct elf_header {
    // 16�Х��Ȥμ��̾���
    struct {
        unsigned char magic[4];     // 16�Х��Ȥμ��̾���
        unsigned char class;        // 32/64bit
        unsigned char format;       // ����ǥ��������
        unsigned char version;      // ELF�ե����ޥåȤΥС������
        unsigned char abi;          // OS�μ���
        unsigned char abi_version;  // OS�ΥС������
        unsigned char reserve[7];   // ͽ��
    } id;
    short type;                  // �ե�����μ���
    short arch;                  // CPU�μ���
    long version;                // ELF�����ΥС������
    long entry_point;            // �¹Գ��ϥ��ɥ쥹
    long program_header_offset;  // �ץ����إå��ơ��֥�ΰ���
    long section_header_offset;  // ���������إå��ơ��֥�ΰ���
    long flags;                  // �Ƽ�ե饰
    short header_size;           // ELF�إå��Υ�����
    short program_header_size;   // �ץ����إå��Υ�����
    short program_header_num;    // ~�θĿ�
    short section_header_size;   // ���������إå��Υ�����
    short section_header_num;    // ~�θĿ�
    short section_name_index;  // ���������̾���Ǽ���륻�������
};

// �ץ����إå�����Ϥ��뤿��
struct elf_program_header {
    long type;           // �������Ȥμ���
    long offset;         // �ե�������ΰ���
    long virtual_addr;   // �������ɥ쥹
    long physical_addr;  // ʪ�����ɥ쥹
    long file_size;      // �ե�������Υ�����
    long memory_size;    // �����ǤΥ�����
    long flags;          // �Ƽ�ե饰
    long align;          // ���饤�����
};

// ELF �إå��Υ����å�
// header�Ȥ��������Ǽ�����ä����ɥ쥹���Ф�����¤�� struct
// elf_header���Ѥ��Ƴƥѥ�᡼���򻲾� �ե����ޥåȲ��Ϥμ�ˡ��
// ���ϤΤ���˹�¤�Τ��������¤�ΤΥݥ��󥿤����Ѥ��ƥե����ޥå���Υѥ�᡼���򻲾�
static int elf_check(struct elf_header *header) {
    if (memcmp(header->id.magic,
               "\x7f"
               "ELF",
               4))
        return -1;

    if (header->id.class != 1) return -1;   /* ELF32 */
    if (header->id.format != 2) return -1;  /* Big endian */
    if (header->id.version != 1) return -1; /* version 1 */
    if (header->type != 2) return -1;       /* Executable file */
    if (header->version != 1) return -1;    /* version 1 */

    /* Hitachi H8/300 or H8/300H */
    if ((header->arch != 46) && (header->arch != 47)) return -1;

    return 0;
}

/* ��������ñ�̤ǤΥ��� */
static int elf_load_program(struct elf_header *header) {
    int i;
    struct elf_program_header *phdr;

    for (i = 0; i < header->program_header_num; i++) {
        /* �ץ���ࡦ�إå������ */
        phdr = (struct elf_program_header *)((char *)header +
                                             header->program_header_offset +
                                             header->program_header_size * i);

        if (phdr->type != 1) /* ���ɲ�ǽ�ʥ������Ȥ��� */
            continue;

        /* �Ȥꤢ�����¸��Ѥˡ��ºݤ˥��ɤ����˥������Ⱦ����ɽ������ */
        putxval(phdr->offset, 6);
        puts(" ");
        putxval(phdr->virtual_addr, 8);
        puts(" ");
        putxval(phdr->physical_addr, 8);
        puts(" ");
        putxval(phdr->file_size, 5);
        puts(" ");
        putxval(phdr->memory_size, 5);
        puts(" ");
        putxval(phdr->flags, 2);
        puts(" ");
        putxval(phdr->align, 2);
        puts("\n");
    }

    return 0;
}

int elf_load(char *buf) {
    struct elf_header *header = (struct elf_header *)buf;

    if (elf_check(header) < 0) /* ELF�إå��Υ����å� */
        return -1;

    if (elf_load_program(header) < 0) /* ��������ñ�̤ǤΥ��� */
        return -1;

    return 0;
}
