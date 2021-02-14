PREFIX	= /usr/local
ARCH	= h8300-elf
BINDIR	= $(PREFIX)/bin
ADDNAME	= $(ARCH)-

##
# ���Ѥ���ġ�����λ���
##
AR		= $(BINDIR)/$(ADDNAME)ar
AS		= $(BINDIR)/$(ADDNAME)as
CC		= $(BINDIR)/$(ADDNAME)gcc
LD		= $(BINDIR)/$(ADDNAME)ld
NM		= $(BINDIR)/$(ADDNAME)nm
OBJCOPY	= $(BINDIR)/$(ADDNAME)objcopy
OBJDUMP	= $(BINDIR)/$(ADDNAME)objdump
RANLIB	= $(BINDIR)/$(ADDNAME)ranlib
STRIP	= $(BINDIR)/$(ADDNAME)strip

##
# �ե�å���ROM�񤭹��ߥġ���
##
H8WRITE = ../../tool/kz_h8write-v0.2.1/PackageFiles/src/kz_h8write

# FreeBSD-4.x:/dev/cuaaX, FreeBSD-6.x:/dev/cuadX, FreeBSD(USB):/dev/cuaUx
# Linux:/dev/ttySx, Linux(USB):/dev/ttyUSBx, Windows:comX
H8WRITE_SERDEV = /dev/ttyS4

##
# ����ѥ��뤹�륽���������ɷ�
##
OBJS  = vector.o startup.o main.o
OBJS += lib.o serial.o xmodem.o elf.o

# ��������¹Է����Υե�����̾
TARGET = kzload

##
# ����ѥ��롦���ץ����
# -mh: 		H8/300H�ѤΥ����ɤ����
# -nostdinc:�����ƥ�Υإå��ե���������Ѥ��ʤ�
# -nostdlib:�����ƥ�Υ饤�֥������Ѥ��ʤ�
# -fno-builtin:	����ѥ���Υӥ�ȥ���ؿ������Ѥ��ʤ�
# -mint32:	int��32�ӥåȤȤ���
# -I:		�إå��ե�����θ��������ꤹ��
# -g:		�ǥХå�������
# -Os:		����������κ�Ŭ��
##
CFLAGS = -Wall -mh -nostdinc -nostdlib -fno-builtin
#CFLAGS += -mint32 # int��32�ӥåȤˤ���ȳݻ����任���Ǥ��ʤ��ʤ�
CFLAGS += -I.
#CFLAGS += -g
CFLAGS += -Os
CFLAGS += -DKZLOAD

##
# ��󥯡����ץ����
# -T:	��󥫡�������ץȤ����
# -L:	�饤�֥��θ���������
##
LFLAGS = -static -T ld.scr -L.

.SUFFIXES: .c .o
.SUFFIXES: .s .o

all :		$(TARGET)

##
# �¹Է����������롼��
##
$(TARGET) :	$(OBJS)
		$(CC) $(OBJS) -o $(TARGET) $(CFLAGS) $(LFLAGS)
		cp $(TARGET) $(TARGET).elf
		$(STRIP) $(TARGET)

# *.c�ե�����Υ���ѥ��롦�롼��
.c.o :		$<
		$(CC) -c $(CFLAGS) $<

# ������֥顦�ե�����Υ�����֥롦�롼��
.s.o :		$<
		$(CC) -c $(CFLAGS) $<

# ��ȥ�����S�쥳���ɡ��ե����ޥåȤؤ��Ѵ��롼��
$(TARGET).mot :	$(TARGET)
		$(OBJCOPY) -O srec $(TARGET) $(TARGET).mot
# ELF -> mot
image :		$(TARGET).mot

# �ե�å���ROM�ؤ�ž��
write :		$(TARGET).mot
		$(H8WRITE) -3069 -f20 $(TARGET).mot $(H8WRITE_SERDEV)

clean :
		rm -f $(OBJS) $(TARGET) $(TARGET).elf $(TARGET).mot