```
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
```

Addr

* そのセクションが配置されるアドレス,VA(論理アドレス)
* そのセクションが動作するアドレス

Off,Size

* セクションの位置,サイズ
* ELFファイル内でどの部分がそのセクションとなるか
* ELF先頭からOffバイト目をせんとうにして，Sizeバイトの部分が該当するセクション名となる

