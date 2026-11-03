#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include "soc/soc_caps.h"
#include <stdint.h>

#define USB_VID 0x303a
#define USB_PID 0x1001

#define HAS_KEYBOARD     // has keyboard to use
#define HAS_KEYBOARD_HID // has keyboard to use
#define KB_HID_EXIT_MSG "fn + Ok to exit"

static const uint8_t TX = 43;
static const uint8_t RX = 44;

static const uint8_t TXD2 = 1;
static const uint8_t RXD2 = 2;

static const uint8_t SDA = 13;
static const uint8_t SCL = 15;

static const uint8_t SS = 12;
static const uint8_t MOSI = 14;
static const uint8_t MISO = 39;
static const uint8_t SCK = 40;

static const uint8_t G0 = 0;
static const uint8_t G1 = 1;
static const uint8_t G2 = 2;
static const uint8_t G3 = 3;
static const uint8_t G4 = 4;
static const uint8_t G5 = 5;
static const uint8_t G6 = 6;
static const uint8_t G7 = 7;
static const uint8_t G8 = 8;
static const uint8_t G9 = 9;
static const uint8_t G10 = 10;
static const uint8_t G11 = 11;
static const uint8_t G12 = 12;
static const uint8_t G13 = 13;
static const uint8_t G14 = 14;
static const uint8_t G15 = 15;
static const uint8_t G39 = 39;
static const uint8_t G40 = 40;
static const uint8_t G41 = 41;
static const uint8_t G42 = 42;
static const uint8_t G43 = 43;
static const uint8_t G44 = 44;
static const uint8_t G46 = 46;

static const uint8_t ADC1 = 7;
static const uint8_t ADC2 = 8;

#define ASTRA_KEY_SHIFT 0x80
#define KEY_LEFT_CTRL 0x80
#define KEY_LEFT_SHIFT 0x81
#define KEY_LEFT_ALT 0x82
#define KEY_FN 0xff
#define KEY_OPT 0x83
#define KEY_BACKSPACE 0x2a
#define KEY_TAB 0x2b
#define KEY_ENTER 0x28

static const uint8_t _kb_asciimap[128] = {
    0x00,          // NUL
    0x00,          // SOH
    0x00,          // STX
    0x00,          // ETX
    0x00,          // EOT
    0x00,          // ENQ
    0x00,          // ACK
    0x00,          // BEL
    KEY_BACKSPACE, // BS	Backspace
    KEY_TAB,       // TAB	Tab
    KEY_ENTER,     // LF	Enter
    0x00,          // VT
    0x00,          // FF
    0x00,          // CR
    0x00,          // SO
    0x00,          // SI
    0x00,          // DEL
    0x00,          // DC1
    0x00,          // DC2
    0x00,          // DC3
    0x00,          // DC4
    0x00,          // NAK
    0x00,          // SYN
    0x00,          // ETB
    0x00,          // CAN
    0x00,          // EM
    0x00,          // SUB
    0x00,          // ESC
    0x00,          // FS
    0x00,          // GS
    0x00,          // RS
    0x00,          // US

    0x2c,         //  ' '
    0x1e | ASTRA_KEY_SHIFT, // !
    0x34 | ASTRA_KEY_SHIFT, // "
    0x20 | ASTRA_KEY_SHIFT, // #
    0x21 | ASTRA_KEY_SHIFT, // $
    0x22 | ASTRA_KEY_SHIFT, // %
    0x24 | ASTRA_KEY_SHIFT, // &
    0x34,         // '
    0x26 | ASTRA_KEY_SHIFT, // (
    0x27 | ASTRA_KEY_SHIFT, // )
    0x25 | ASTRA_KEY_SHIFT, // *
    0x2e | ASTRA_KEY_SHIFT, // +
    0x36,         // ,
    0x2d,         // -
    0x37,         // .
    0x38,         // /
    0x27,         // 0
    0x1e,         // 1
    0x1f,         // 2
    0x20,         // 3
    0x21,         // 4
    0x22,         // 5
    0x23,         // 6
    0x24,         // 7
    0x25,         // 8
    0x26,         // 9
    0x33 | ASTRA_KEY_SHIFT, // :
    0x33,         // ;
    0x36 | ASTRA_KEY_SHIFT, // <
    0x2e,         // =
    0x37 | ASTRA_KEY_SHIFT, // >
    0x38 | ASTRA_KEY_SHIFT, // ?
    0x1f | ASTRA_KEY_SHIFT, // @
    0x04 | ASTRA_KEY_SHIFT, // A
    0x05 | ASTRA_KEY_SHIFT, // B
    0x06 | ASTRA_KEY_SHIFT, // C
    0x07 | ASTRA_KEY_SHIFT, // D
    0x08 | ASTRA_KEY_SHIFT, // E
    0x09 | ASTRA_KEY_SHIFT, // F
    0x0a | ASTRA_KEY_SHIFT, // G
    0x0b | ASTRA_KEY_SHIFT, // H
    0x0c | ASTRA_KEY_SHIFT, // I
    0x0d | ASTRA_KEY_SHIFT, // J
    0x0e | ASTRA_KEY_SHIFT, // K
    0x0f | ASTRA_KEY_SHIFT, // L
    0x10 | ASTRA_KEY_SHIFT, // M
    0x11 | ASTRA_KEY_SHIFT, // N
    0x12 | ASTRA_KEY_SHIFT, // O
    0x13 | ASTRA_KEY_SHIFT, // P
    0x14 | ASTRA_KEY_SHIFT, // Q
    0x15 | ASTRA_KEY_SHIFT, // R
    0x16 | ASTRA_KEY_SHIFT, // S
    0x17 | ASTRA_KEY_SHIFT, // T
    0x18 | ASTRA_KEY_SHIFT, // U
    0x19 | ASTRA_KEY_SHIFT, // V
    0x1a | ASTRA_KEY_SHIFT, // W
    0x1b | ASTRA_KEY_SHIFT, // X
    0x1c | ASTRA_KEY_SHIFT, // Y
    0x1d | ASTRA_KEY_SHIFT, // Z
    0x2f,         // [
    0x31,         // bslash
    0x30,         // ]
    0x23 | ASTRA_KEY_SHIFT, // ^
    0x2d | ASTRA_KEY_SHIFT, // _
    0x35,         // `
    0x04,         // a
    0x05,         // b
    0x06,         // c
    0x07,         // d
    0x08,         // e
    0x09,         // f
    0x0a,         // g
    0x0b,         // h
    0x0c,         // i
    0x0d,         // j
    0x0e,         // k
    0x0f,         // l
    0x10,         // m
    0x11,         // n
    0x12,         // o
    0x13,         // p
    0x14,         // q
    0x15,         // r
    0x16,         // s
    0x17,         // t
    0x18,         // u
    0x19,         // v
    0x1a,         // w
    0x1b,         // x
    0x1c,         // y
    0x1d,         // z
    0x2f | ASTRA_KEY_SHIFT, // {
    0x31 | ASTRA_KEY_SHIFT, // |
    0x30 | ASTRA_KEY_SHIFT, // }
    0x35 | ASTRA_KEY_SHIFT, // ~
    0             // DEL
};

#define HAS_RGB_LED 1
#define LED_TYPE SK6812
#define LED_ORDER GRB
#define LED_TYPE_IS_RGBW 1
#define LED_COUNT 1
#define LED_COLOR_STEP 15

// Deepsleep
#define DEEPSLEEP_WAKEUP_PIN 0
#define DEEPSLEEP_PIN_ACT LOW

#endif /* Pins_Arduino_h */
