PREFIX	= /usr/local
ARCH	= h8300-elf
BINDIR	= $(PREFIX)/bin
ADDNAME	= $(ARCH)-

##
# 利用するツール類の指定
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
# フラッシュROM書き込みツール
##
H8WRITE = ../../tool/kz_h8write-v0.2.1/PackageFiles/src/kz_h8write

# FreeBSD-4.x:/dev/cuaaX, FreeBSD-6.x:/dev/cuadX, FreeBSD(USB):/dev/cuaUx
# Linux:/dev/ttySx, Linux(USB):/dev/ttyUSBx, Windows:comX
H8WRITE_SERDEV = /dev/ttyS4

##
# コンパイルするソースコード群
##
OBJS  = vector.o startup.o main.o
OBJS += lib.o serial.o

# 生成する実行形式のファイル名
TARGET = kzload

##
# コンパイル・オプション
# -mh: 		H8/300H用のコードを出力
# -nostdinc:システムのヘッダファイルを利用しない
# -nostdlib:システムのライブラリを利用しない
# -fno-builtin:	コンパイラのビルトイン関数を利用しない
# -mint32:	intを32ビットとする
# -I:		ヘッダファイルの検索先を指定する
# -g:		デバッガを利用
# -Os:		サイズ節約の最適化
##
CFLAGS = -Wall -mh -nostdinc -nostdlib -fno-builtin
#CFLAGS += -mint32 # intを32ビットにすると掛算／割算ができなくなる
CFLAGS += -I.
#CFLAGS += -g
CFLAGS += -Os
CFLAGS += -DKZLOAD

##
# リンク・オプション
# -T:	リンカ・スクリプトを指定
# -L:	ライブラリの検索先を指定
##
LFLAGS = -static -T ld.scr -L.

.SUFFIXES: .c .o
.SUFFIXES: .s .o

all :		$(TARGET)

##
# 実行形式の生成ルール
##
$(TARGET) :	$(OBJS)
		$(CC) $(OBJS) -o $(TARGET) $(CFLAGS) $(LFLAGS)
		cp $(TARGET) $(TARGET).elf
		$(STRIP) $(TARGET)

# *.cファイルのコンパイル・ルール
.c.o :		$<
		$(CC) -c $(CFLAGS) $<

# アセンブラ・ファイルのアセンブル・ルール
.s.o :		$<
		$(CC) -c $(CFLAGS) $<

# モトローラSレコード・フォーマットへの変換ルール
$(TARGET).mot :	$(TARGET)
		$(OBJCOPY) -O srec $(TARGET) $(TARGET).mot
# ELF -> mot
image :		$(TARGET).mot

# フラッシュROMへの転送
write :		$(TARGET).mot
		$(H8WRITE) -3069 -f20 $(TARGET).mot $(H8WRITE_SERDEV)

clean :
		rm -f $(OBJS) $(TARGET) $(TARGET).elf $(TARGET).mot
