#include "serial.h"

#include "defines.h"

#define SERIAL_SCI_NUM 3

// SCI(シリアル・コントローラ)の定義
#define H8_3069F_SCI0 ((volatile struct h8_3069f_sci *)0xffffb0)
#define H8_3069F_SCI1 ((volatile struct h8_3069f_sci *)0xffffb8)
#define H8_3069F_SCI2 ((volatile struct h8_3069f_sci *)0xffffc0)

/**
 * SCI各種レジスタの定義
 * smr: シリアルモードレジスタ，シリアル入出力のパラメータ設定を行う
 * scr: シリアルコントロールレジスタ，シリアル入出力の制御を行う
 * (制御: 送受信の有効/無効の切り替え，割り込みの有効/無効の切り替えなど)
 * brr: ビットレートレジスタ，シリアル通信の速度(ポーレート)の設定
 * tdr: トレンスミットデータレジスタ
 * ssr: シリアルステータスレジスタ
 */
struct h8_3069f_sci {
    volatile uint8 smr;  // シリアル通信のモード設定
    volatile uint8 brr;  // シリアルの転送速度(ポーレート)の設定
    volatile uint8 scr;  // 送受信の有効/無効など
    volatile uint8 tdr;  // 送信したい１文字を書き込む
    volatile uint8 ssr;  // 送信完了/受信完了などを表す
    volatile uint8 rdr;  // 受信した１文字を読み出す
    volatile uint8 scmr;
};

// SMRの各ビットの定義
#define H8_3069F_SCI_SMR_CKS_PER1 (0 << 0)
#define H8_3069F_SCI_SMR_CKS_PER4 (1 << 0)
#define H8_3069F_SCI_SMR_CKS_PER16 (2 << 0)
#define H8_3069F_SCI_SMR_CKS_PER64 (3 << 0)
#define H8_3069F_SCI_SMR_MP (1 << 2)
#define H8_3069F_SCI_SMR_STOP (1 << 3)
#define H8_3069F_SCI_SMR_OE (1 << 4)
#define H8_3069F_SCI_SMR_PE (1 << 5)
#define H8_3069F_SCI_SMR_CHR (1 << 6)
#define H8_3069F_SCI_SMR_CA (1 << 7)

// SCRの各ビットの定義
#define H8_3069F_SCI_SCR_CKE0 (1 << 0)
#define H8_3069F_SCI_SCR_CKE1 (1 << 1)
#define H8_3069F_SCI_SCR_TEIE (1 << 2)
#define H8_3069F_SCI_SCR_MPIE (1 << 3)
#define H8_3069F_SCI_SCR_RE (1 << 4)  /* 受信有効 */
#define H8_3069F_SCI_SCR_TE (1 << 5)  /* 送信有効 */
#define H8_3069F_SCI_SCR_RIE (1 << 6) /* 受信割込み有効 */
#define H8_3069F_SCI_SCR_TIE (1 << 7) /* 送信割込み有効 */

// SSRの各ビットの定義
#define H8_3069F_SCI_SSR_MPBT (1 << 0)
#define H8_3069F_SCI_SSR_MPB (1 << 1)
#define H8_3069F_SCI_SSR_TEND (1 << 2)
#define H8_3069F_SCI_SSR_PER (1 << 3)
#define H8_3069F_SCI_SSR_FERERS (1 << 4)
#define H8_3069F_SCI_SSR_ORER (1 << 5)
#define H8_3069F_SCI_SSR_RDRF (1 << 6) /* 受信完了 */
#define H8_3069F_SCI_SSR_TDRE (1 << 7) /* 送信完了 */

static struct {
    volatile struct h8_3069f_sci *sci;
} regs[SERIAL_SCI_NUM] = {
    // メンバ：SCIレジスタ群の先頭アドレスを指す
    {H8_3069F_SCI0},
    {H8_3069F_SCI1},
    {H8_3069F_SCI2},
};

// デバイス初期化, index:SCIの番号
int serial_init(int index) {
    volatile struct h8_3069f_sci *sci = regs[index].sci;

    // 以下SCIのレジスタの設定
    sci->scr = 0;  // シリアル送受信と割り込みを無効化
    sci->smr = 0;
    sci->brr = 64;  // 20MHzのクロックから9600bpsを生成(25MHzの場合は80にする)
    sci->scr = H8_3069F_SCI_SCR_RE | H8_3069F_SCI_SCR_TE;  // 送受信可能
    sci->ssr = 0;

    return 0;
}

// 送信可能か
int serial_is_send_enable(int index) {
    volatile struct h8_3069f_sci *sci = regs[index].sci;
    return (sci->ssr & H8_3069F_SCI_SSR_TDRE);
}

// 1文字送信
int serial_send_byte(int index, unsigned char c) {
    volatile struct h8_3069f_sci *sci = regs[index].sci;

    // 送信可能になるまで待つ(送信完了ビットが落ちていないなら次へ)
    while (!serial_is_send_enable(index))
        ;
    sci->tdr = c;  // 送信したい文字の書き込み
    sci->ssr &=
        ~H8_3069F_SCI_SSR_TDRE;  // 送信開始，ssrの送信完了ビットを立てる

    return 0;
}

/* 受信可能か？ */
int serial_is_recv_enable(int index) {
    volatile struct h8_3069f_sci *sci = regs[index].sci;
    return (sci->ssr & H8_3069F_SCI_SSR_RDRF);
}

/* １文字受信 */
unsigned char serial_recv_byte(int index) {
    volatile struct h8_3069f_sci *sci = regs[index].sci;
    unsigned char c;

    /* 受信文字が来るまで待つ */
    while (!serial_is_recv_enable(index))
        ;
    c = sci->rdr;
    // データの受信後，SSRのRDRFビットを落とすことで，SCIに受信完了を通知
    sci->ssr &= ~H8_3069F_SCI_SSR_RDRF; /* 受信完了 */

    return c;
}
