```
$ readelf -a kzload.elf
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
  Start of section headers:          1548 (bytes into file)
  Flags:                             0x810000
  Size of this header:               52 (bytes)
  Size of program headers:           32 (bytes)
  Number of program headers:         3
  Size of section headers:           40 (bytes)
  Number of section headers:         9
  Section header string table index: 6

Section Headers:
  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al
  [ 0]                   NULL            00000000 000000 000000 00      0   0  0
  [ 1] .vectors          PROGBITS        00000000 000094 000100 00  WA  0   0  4
  [ 2] .text             PROGBITS        00000100 000194 0003b6 00  AX  0   0  2
  [ 3] .rodata           PROGBITS        000004b6 00054a 000071 01 AMS  0   0  1
  [ 4] .data             PROGBITS        00fffc20 0005bc 000010 00  WA  0   0  4
  [ 5] .bss              NOBITS          00fffc30 0005cc 000004 00  WA  0   0  2
  [ 6] .shstrtab         STRTAB          00000000 0005cc 00003d 00      0   0  1
  [ 7] .symtab           SYMTAB          00000000 000774 000500 10      8  52  4
  [ 8] .strtab           STRTAB          00000000 000c74 00020d 00      0   0  1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),
  L (link order), O (extra OS processing required), G (group), T (TLS),
  C (compressed), x (unknown), o (OS specific), E (exclude),
  p (processor specific)

There are no section groups in this file.

Program Headers:
  Type           Offset   VirtAddr   PhysAddr   FileSiz MemSiz  Flg Align
  LOAD           0x000094 0x00000000 0x00000000 0x00100 0x00100 RW  0x1
  LOAD           0x000194 0x00000100 0x00000100 0x00427 0x00427 R E 0x1     
  LOAD           0x0005bc 0x00fffc20 0x00000527 0x00010 0x00014 RW  0x1     <- VirtAddr != PhysAddr¡¤.data and .bss

# 0x00000000: .vectors addr
# 0x00000100: .text addr

 Section to Segment mapping:
  Segment Sections...
   00     .vectors
   01     .text .rodata
   02     .data .bss

There is no dynamic section in this file.

There are no relocations in this file.

The decoding of unwind sections for machine type Renesas H8/300 is not currently supported.

Symbol table '.symtab' contains 80 entries:
   Num:    Value  Size Type    Bind   Vis      Ndx Name
     0: 00000000     0 NOTYPE  LOCAL  DEFAULT  UND
     1: 00000000     0 SECTION LOCAL  DEFAULT    1
     2: 00000100     0 SECTION LOCAL  DEFAULT    2
     3: 000004b6     0 SECTION LOCAL  DEFAULT    3
     4: 00fffc20     0 SECTION LOCAL  DEFAULT    4
     5: 00fffc30     0 SECTION LOCAL  DEFAULT    5
     6: 00000000     0 FILE    LOCAL  DEFAULT  ABS vector.c
     7: 0000010a     0 NOTYPE  LOCAL  DEFAULT    2 .L1^B1
     8: 00000000     0 FILE    LOCAL  DEFAULT  ABS main.c
     9: 00fffc22     2 OBJECT  LOCAL  DEFAULT    4 _static_data
    10: 0000010c   148 NOTYPE  LOCAL  DEFAULT    2 _printval
    11: 00fffc30     2 OBJECT  LOCAL  DEFAULT    5 _static_bss
    12: 00000220     0 NOTYPE  LOCAL  DEFAULT    2 .L4
    13: 00000000     0 FILE    LOCAL  DEFAULT  ABS lib.c
    14: 00000236     0 NOTYPE  LOCAL  DEFAULT    2 .L7
    15: 0000022a     0 NOTYPE  LOCAL  DEFAULT    2 .L8
    16: 00000258     0 NOTYPE  LOCAL  DEFAULT    2 .L15
    17: 0000024a     0 NOTYPE  LOCAL  DEFAULT    2 .L16
    18: 00000292     0 NOTYPE  LOCAL  DEFAULT    2 .L26
    19: 0000028a     0 NOTYPE  LOCAL  DEFAULT    2 .L21
    20: 00000284     0 NOTYPE  LOCAL  DEFAULT    2 .L22
    21: 00000294     0 NOTYPE  LOCAL  DEFAULT    2 .L17
    22: 00000270     0 NOTYPE  LOCAL  DEFAULT    2 .L27
    23: 000002b0     0 NOTYPE  LOCAL  DEFAULT    2 .L34
    24: 000002a6     0 NOTYPE  LOCAL  DEFAULT    2 .L35
    25: 000002ce     0 NOTYPE  LOCAL  DEFAULT    2 .L38
    26: 000002c0     0 NOTYPE  LOCAL  DEFAULT    2 .L37
    27: 000002e4     0 NOTYPE  LOCAL  DEFAULT    2 .L53
    28: 00000300     0 NOTYPE  LOCAL  DEFAULT    2 .L50
    29: 000002fa     0 NOTYPE  LOCAL  DEFAULT    2 .L45
    30: 000002f4     0 NOTYPE  LOCAL  DEFAULT    2 .L46
    31: 00000302     0 NOTYPE  LOCAL  DEFAULT    2 .L41
    32: 000002dc     0 NOTYPE  LOCAL  DEFAULT    2 .L55
    33: 00000332     0 NOTYPE  LOCAL  DEFAULT    2 .L57
    34: 0000032c     0 NOTYPE  LOCAL  DEFAULT    2 .L60
    35: 00000326     0 NOTYPE  LOCAL  DEFAULT    2 .L61
    36: 00000340     0 NOTYPE  LOCAL  DEFAULT    2 .L56
    37: 0000033a     0 NOTYPE  LOCAL  DEFAULT    2 .L59
    38: 0000033e     0 NOTYPE  LOCAL  DEFAULT    2 .L58
    39: 00000318     0 NOTYPE  LOCAL  DEFAULT    2 .L63
    40: 00000364     0 NOTYPE  LOCAL  DEFAULT    2 .L65
    41: 00000390     0 NOTYPE  LOCAL  DEFAULT    2 .L71
    42: 00000384     0 NOTYPE  LOCAL  DEFAULT    2 .L72
    43: 000003bc     0 NOTYPE  LOCAL  DEFAULT    2 .L75
    44: 000003be     0 NOTYPE  LOCAL  DEFAULT    2 .L74
    45: 000003c6     0 NOTYPE  LOCAL  DEFAULT    2 .L85
    46: 000003f0     0 NOTYPE  LOCAL  DEFAULT    2 .L82
    47: 000003ea     0 NOTYPE  LOCAL  DEFAULT    2 .L76
    48: 000003c2     0 NOTYPE  LOCAL  DEFAULT    2 .L86
    49: 00000000     0 FILE    LOCAL  DEFAULT  ABS serial.c
    50: 00fffc24    12 OBJECT  LOCAL  DEFAULT    4 _regs
    51: 00000488     0 NOTYPE  LOCAL  DEFAULT    2 .L4
    52: 000002d6    50 NOTYPE  GLOBAL DEFAULT    2 _strcmp
    53: 00fffc32     2 OBJECT  GLOBAL DEFAULT    5 _global_bss
    54: 00000000   256 OBJECT  GLOBAL DEFAULT    1 _vectors
    55: 0000034a    46 NOTYPE  GLOBAL DEFAULT    2 _putc
    56: 000004b6     0 NOTYPE  GLOBAL DEFAULT    2 _etext
    57: 00000378    36 NOTYPE  GLOBAL DEFAULT    2 _puts
    58: 00fffc30     0 NOTYPE  GLOBAL DEFAULT    5 _bss_start
    59: 00000100     0 NOTYPE  GLOBAL DEFAULT    2 _text_start
    60: 0000043c    36 NOTYPE  GLOBAL DEFAULT    2 _serial_is_send_enable
    61: 00fffc34     0 NOTYPE  GLOBAL DEFAULT    5 _ebss
    62: 0000023c    40 NOTYPE  GLOBAL DEFAULT    2 _memcpy
    63: 00000222    26 NOTYPE  GLOBAL DEFAULT    2 _memset
    64: 00000100     0 NOTYPE  GLOBAL DEFAULT    2 _start
    65: 00fffc20     0 NOTYPE  GLOBAL DEFAULT    4 _data_start
    66: 00000406    54 NOTYPE  GLOBAL DEFAULT    2 _serial_init
    67: 0000039c   106 NOTYPE  GLOBAL DEFAULT    2 _putxval
    68: 000002b8    30 NOTYPE  GLOBAL DEFAULT    2 _strcpy
    69: 00fffc20     2 OBJECT  GLOBAL DEFAULT    4 _global_data
    70: 00000264    58 NOTYPE  GLOBAL DEFAULT    2 _memcmp
    71: 00000308    66 NOTYPE  GLOBAL DEFAULT    2 _strncmp
    72: 000004b6     0 NOTYPE  GLOBAL DEFAULT    3 _rodata_start
    73: 00fffc30     0 NOTYPE  GLOBAL DEFAULT    4 _edata
    74: 00fffc34     0 NOTYPE  GLOBAL DEFAULT  ABS _end
    75: 0000029e    26 NOTYPE  GLOBAL DEFAULT    2 _strlen
    76: 00000460    86 NOTYPE  GLOBAL DEFAULT    2 _serial_send_byte
    77: 00ffff00     0 NOTYPE  GLOBAL DEFAULT    5 _stack
    78: 000001a0   130 NOTYPE  GLOBAL DEFAULT    2 _main
    79: 00000527     0 NOTYPE  GLOBAL DEFAULT    3 _erodata

No version information found in this file.
```
