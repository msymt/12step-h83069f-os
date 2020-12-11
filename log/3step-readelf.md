```
$ readelf  -a kzload.elf
ELF Header:
  Magic:   7f 45 4c 46 01 02 01 00 00 00 00 00 00 00 00 00
  Class:                             ELF32
  Data:                              2's complement, big endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              EXEC (Executable file)
  Machine:                           Renesas H8/300
  Version:                           0x1
  Entry point address:               0x100
  Start of program headers:          52 (bytes into file)
  Start of section headers:          1212 (bytes into file)
  Flags:                             0x810000
  Size of this header:               52 (bytes)
  Size of program headers:           32 (bytes)
  Number of program headers:         2
  Size of section headers:           40 (bytes)
  Number of section headers:         8
  Section header string table index: 5

Section Headers:
  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al
  [ 0]                   NULL            00000000 000000 000000 00      0   0  0
  [ 1] .vectors          PROGBITS        00000000 000074 000100 00  WA  0   0  4
  [ 2] .text             PROGBITS        00000100 000174 0002e2 00  AX  0   0  2
  [ 3] .rodata           PROGBITS        000003e2 000456 00001f 01 AMS  0   0  1
  [ 4] .data             PROGBITS        00000404 000478 00000c 00  WA  0   0  4
  [ 5] .shstrtab         STRTAB          00000000 000484 000038 00      0   0  1
  [ 6] .symtab           SYMTAB          00000000 0005fc 000400 10      7  48  4
  [ 7] .strtab           STRTAB          00000000 0009fc 00017b 00      0   0  1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),
  L (link order), O (extra OS processing required), G (group), T (TLS),
  C (compressed), x (unknown), o (OS specific), E (exclude),
  p (processor specific)

There are no section groups in this file.

Program Headers:
  Type           Offset   VirtAddr   PhysAddr   FileSiz MemSiz  Flg Align
  LOAD           0x000074 0x00000000 0x00000000 0x00401 0x00401 RWE 0x1
  LOAD           0x000478 0x00000404 0x00000404 0x0000c 0x0000c RW  0x1

 Section to Segment mapping:
  Segment Sections...
   00     .vectors .text .rodata
   01     .data

There is no dynamic section in this file.

There are no relocations in this file.

The decoding of unwind sections for machine type Renesas H8/300 is not currently supported.

Symbol table '.symtab' contains 64 entries:
   Num:    Value  Size Type    Bind   Vis      Ndx Name
     0: 00000000     0 NOTYPE  LOCAL  DEFAULT  UND
     1: 00000000     0 SECTION LOCAL  DEFAULT    1
     2: 00000100     0 SECTION LOCAL  DEFAULT    2
     3: 000003e2     0 SECTION LOCAL  DEFAULT    3
     4: 00000404     0 SECTION LOCAL  DEFAULT    4
     5: 00000000     0 FILE    LOCAL  DEFAULT  ABS vector.c
     6: 0000010a     0 NOTYPE  LOCAL  DEFAULT    2 .L1^B1
     7: 00000000     0 FILE    LOCAL  DEFAULT  ABS main.c
     8: 0000014c     0 NOTYPE  LOCAL  DEFAULT    2 .L2
     9: 00000000     0 FILE    LOCAL  DEFAULT  ABS lib.c
    10: 00000162     0 NOTYPE  LOCAL  DEFAULT    2 .L7
    11: 00000156     0 NOTYPE  LOCAL  DEFAULT    2 .L8
    12: 00000184     0 NOTYPE  LOCAL  DEFAULT    2 .L15
    13: 00000176     0 NOTYPE  LOCAL  DEFAULT    2 .L16
    14: 000001be     0 NOTYPE  LOCAL  DEFAULT    2 .L26
    15: 000001b6     0 NOTYPE  LOCAL  DEFAULT    2 .L21
    16: 000001b0     0 NOTYPE  LOCAL  DEFAULT    2 .L22
    17: 000001c0     0 NOTYPE  LOCAL  DEFAULT    2 .L17
    18: 0000019c     0 NOTYPE  LOCAL  DEFAULT    2 .L27
    19: 000001dc     0 NOTYPE  LOCAL  DEFAULT    2 .L34
    20: 000001d2     0 NOTYPE  LOCAL  DEFAULT    2 .L35
    21: 000001fa     0 NOTYPE  LOCAL  DEFAULT    2 .L38
    22: 000001ec     0 NOTYPE  LOCAL  DEFAULT    2 .L37
    23: 00000210     0 NOTYPE  LOCAL  DEFAULT    2 .L53
    24: 0000022c     0 NOTYPE  LOCAL  DEFAULT    2 .L50
    25: 00000226     0 NOTYPE  LOCAL  DEFAULT    2 .L45
    26: 00000220     0 NOTYPE  LOCAL  DEFAULT    2 .L46
    27: 0000022e     0 NOTYPE  LOCAL  DEFAULT    2 .L41
    28: 00000208     0 NOTYPE  LOCAL  DEFAULT    2 .L55
    29: 0000025e     0 NOTYPE  LOCAL  DEFAULT    2 .L57
    30: 00000258     0 NOTYPE  LOCAL  DEFAULT    2 .L60
    31: 00000252     0 NOTYPE  LOCAL  DEFAULT    2 .L61
    32: 0000026c     0 NOTYPE  LOCAL  DEFAULT    2 .L56
    33: 00000266     0 NOTYPE  LOCAL  DEFAULT    2 .L59
    34: 0000026a     0 NOTYPE  LOCAL  DEFAULT    2 .L58
    35: 00000244     0 NOTYPE  LOCAL  DEFAULT    2 .L63
    36: 00000290     0 NOTYPE  LOCAL  DEFAULT    2 .L65
    37: 000002bc     0 NOTYPE  LOCAL  DEFAULT    2 .L71
    38: 000002b0     0 NOTYPE  LOCAL  DEFAULT    2 .L72
    39: 000002e8     0 NOTYPE  LOCAL  DEFAULT    2 .L75
    40: 000002ea     0 NOTYPE  LOCAL  DEFAULT    2 .L74
    41: 000002f2     0 NOTYPE  LOCAL  DEFAULT    2 .L85
    42: 0000031c     0 NOTYPE  LOCAL  DEFAULT    2 .L82
    43: 00000316     0 NOTYPE  LOCAL  DEFAULT    2 .L76
    44: 000002ee     0 NOTYPE  LOCAL  DEFAULT    2 .L86
    45: 00000000     0 FILE    LOCAL  DEFAULT  ABS serial.c
    46: 00000404    12 OBJECT  LOCAL  DEFAULT    4 _regs
    47: 000003b4     0 NOTYPE  LOCAL  DEFAULT    2 .L4
    48: 00000202    50 NOTYPE  GLOBAL DEFAULT    2 _strcmp
    49: 00000000   256 OBJECT  GLOBAL DEFAULT    1 _vectors
    50: 00000276    46 NOTYPE  GLOBAL DEFAULT    2 _putc
    51: 000002a4    36 NOTYPE  GLOBAL DEFAULT    2 _puts
    52: 00000368    36 NOTYPE  GLOBAL DEFAULT    2 _serial_is_send_enable
    53: 00000168    40 NOTYPE  GLOBAL DEFAULT    2 _memcpy
    54: 0000014e    26 NOTYPE  GLOBAL DEFAULT    2 _memset
    55: 00000100     0 NOTYPE  GLOBAL DEFAULT    2 _start
    56: 00000332    54 NOTYPE  GLOBAL DEFAULT    2 _serial_init
    57: 000002c8   106 NOTYPE  GLOBAL DEFAULT    2 _putxval
    58: 000001e4    30 NOTYPE  GLOBAL DEFAULT    2 _strcpy
    59: 00000190    58 NOTYPE  GLOBAL DEFAULT    2 _memcmp
    60: 00000234    66 NOTYPE  GLOBAL DEFAULT    2 _strncmp
    61: 000001ca    26 NOTYPE  GLOBAL DEFAULT    2 _strlen
    62: 0000038c    86 NOTYPE  GLOBAL DEFAULT    2 _serial_send_byte
    63: 0000010c    66 NOTYPE  GLOBAL DEFAULT    2 _main

No version information found in this file.
```
