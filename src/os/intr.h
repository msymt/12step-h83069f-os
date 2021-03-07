// 割り込み種別の定義
#ifndef _INTR_H_INCLUDED_
#define _INTR_H_INCLUDED_

// ソフトウェア割り込みベクタの定義

// ソフトウェア割り込みベクタの種別個数
#define SOFTVEC_TYPE_NUM 3

// ソフトウェア・割り込みベクタの種別の定義
#define SOFTVEC_TYPE_SOFTERR 0  // software error
#define SOFTVEC_TYPE_SYSCALL 0  // system call
#define SOFTVEC_TYPE_SERINTR 0  // serial割り込み

#endif
