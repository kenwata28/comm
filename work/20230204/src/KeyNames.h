#ifndef KEY_NAMES_H_
#define KEY_NAMES_H_

#include <windows.h>

#include <string>

const std::string g_str_key[]{
    "non",                // 0x00 non
    "L_BTN",              // 0x01 mouse left click
    "R_BTN",              // 0x02 mouse left click
    "CANCEL",             // 0x03 cancel
    "MBTN",               // 0x04 mouse center Button (3 Button mouse)
    "XBTN1",              // 0x05 X1 mouse Button
    "XBTN2",              // 0x06 X2 mouse Button
    "non",                // 0x07 undefined
    "BS",                 // 0x08 BACKSPACE
    "Tab",                // 0x09 Tab
    "non",                // 0x0A reserved
    "non",                // 0x0B reservedd
    "Clr",                // 0x0C CLEAR
    "Ent",                // 0x0D Enter
    "non",                // 0x0E 0x0E-0F undefined
    "non",                // 0x0F
    "Shift",              // 0x10 Shift
    "Ctrl",               // 0x11 Ctrl
    "Alt",                // 0x12 ALT
    "Pause",              // 0x13 PAUSE
    "Caps",               // 0x14 CAPS LOCK
    "Kana",               // 0x15 IME kana mode  or "Hang"?
    "IME_ON",             // 0x16 IME On
    "JUNJA",              // 0x17 IME Junja mode
    "FINAL",              // 0x18 IME Final mode or "HANJA"?
    "KANJI",              // 0x19 IME Kanji mode
    "IME_OFF",            // 0x1A IME off
    "Esc",                // 0x1B Escape
    "Convert",            // 0x1C IME convert
    "NonConvert",         // 0x1D IME no convert
    "Acc",                // 0x1E IME accept
    "ModeChange",         // 0x1F IME mode change
    "Space",              // 0x20 Space
    "PgUp",               // 0x21 PAGE UP
    "PgDw",               // 0x22 PAGE DOWN
    "End",                // 0x23 END
    "Home",               // 0x24 HOME
    "Left",               // 0x25 ←
    "Up",                 // 0x26 ↑
    "Right",              // 0x27 →
    "Down",               // 0x28 ↓
    "Select",             // 0x29
    "Print",              // 0x2A
    "Exec",               // 0x2B
    "SNAPSHOT",           // 0x2C snapshot
    "Ins",                // 0x2D INS キー
    "Del",                // 0x2E DEL キー
    "Help",               // 0x2F HELP キー
    "0",                  // 0x30  key
    "1",                  // 0x31  key
    "2",                  // 0x32  key
    "3",                  // 0x33  key
    "4",                  // 0x34  key
    "5",                  // 0x35  key
    "6",                  // 0x36  key
    "7",                  // 0x37  key
    "8",                  // 0x38  key
    "9",                  // 0x39  key
    "non",                // 0x3A 0x3A-40 undefined
    "non",                // 0x3B
    "non",                // 0x3C
    "non",                // 0x3D
    "non",                // 0x3E
    "non",                // 0x3F
    "non",                // 0x40 0x3A-40 undefined
    "A",                  // 0x41
    "B",                  // 0x42
    "C",                  // 0x43
    "D",                  // 0x44
    "E",                  // 0x45
    "F",                  // 0x46
    "G",                  // 0x47
    "H",                  // 0x48
    "I",                  // 0x49
    "J",                  // 0x4A
    "K",                  // 0x4B
    "L",                  // 0x4C
    "M",                  // 0x4D
    "N",                  // 0x4E
    "O",                  // 0x4F
    "P",                  // 0x50
    "Q",                  // 0x51
    "R",                  // 0x52
    "S",                  // 0x53
    "T",                  // 0x54
    "U",                  // 0x55
    "V",                  // 0x56
    "W",                  // 0x57
    "X",                  // 0x58
    "Y",                  // 0x59
    "Z",                  // 0x5A
    "LWin",               // 0x5B
    "RWin",               // 0x5C
    "Apps",               // 0x5D
    "non",                // 0x5E reserved
    "Sleep",              // 0x5F sleep key
    "NumPad0",            // 0x60 テンキー 0
    "NumPad1",            // 0x61 テンキー 1
    "NumPad2",            // 0x62 テンキー 2
    "NumPad3",            // 0x63 テンキー 3
    "NumPad4",            // 0x64 テンキー 4
    "NumPad5",            // 0x65 テンキー 5
    "NumPad6",            // 0x66 テンキー 6
    "NumPad7",            // 0x67 テンキー 7
    "NumPad8",            // 0x68 テンキー 8
    "NumPad9",            // 0x69 テンキー 9
    "Multiply",           // 0x6A 乗算 key
    "Add",                // 0x6B
    "Separate",           // 0x6C 区切り記号key
    "Subtract",           // 0x6D 減算key
    "Decimal",            // 0x6E 10 進key
    "Divide",             // 0x6F
    "F1",                 // 0x70 F1
    "F2",                 // 0x71 F2
    "F3",                 // 0x72 F3
    "F4",                 // 0x73 F4
    "F5",                 // 0x74 F5
    "F6",                 // 0x75 F6
    "F7",                 // 0x76 F7
    "F8",                 // 0x77 F8
    "F9",                 // 0x78 F9
    "F10",                // 0x79 F10
    "F11",                // 0x7A F11
    "F12",                // 0x7B F12
    "F13",                // 0x7C F13
    "F14",                // 0x7D F14
    "F15",                // 0x7e F15
    "F16",                // 0x7F F16
    "F17",                // 0x80 F17
    "F18",                // 0x81 F18
    "F19",                // 0x82 F19
    "F20",                // 0x83 F20
    "F21",                // 0x84 F21
    "F22",                // 0x85 F22
    "F23",                // 0x86 F23
    "F24",                // 0x87 F24
    "non",                // 0x88 0x88-8F Unassigned
    "non",                // 0x89
    "non",                // 0x8A
    "non",                // 0x8B
    "non",                // 0x8C
    "non",                // 0x8D
    "non",                // 0x8E
    "non",                // 0x8F 0x88-8F Unassigned
    "NumLk",              // 0x90
    "ScrLk",              // 0x91
    "non",                // 0x92    0x92-96
    "non",                // 0x93
    "non",                // 0x94
    "non",                // 0x95
    "non",                // 0x96
    "non",                // 0x97    0x97-9F Unassigned
    "non",                // 0x98
    "non",                // 0x99
    "non",                // 0x9A
    "non",                // 0x9B
    "non",                // 0x9C
    "non",                // 0x9D
    "non",                // 0x9E
    "non",                // 0x9F
    "LShift",             // 0xA0
    "RShift",             // 0xA1
    "LCtrl",              // 0xA2
    "RCtrl",              // 0xA3
    "LAlt",               // 0xA4
    "RAlt",               // 0xA5
    "BROWSER_BACK",       // 0xA6 browser
    "BROWSER_FORWARD",    // 0xA7
    "BROWSER_REFRESH",    // 0xA8
    "BROWSER_STOP",       // 0xA9
    "BROWSER_SEARCH",     // 0xAA
    "BROWSER_FAVORITES",  // 0xAB
    "BROWSER_HOME",       // 0xAC
    "VolMute",            // 0xAD vol
    "VolDw",              // 0xAE
    "VolUp",              // 0xAF
    "MEDIA_NEXT_TRACK",   // 0xB0 next track
    "MEDIA_PREV_TRACK",   // 0xB1 previout track
    "MEDIA_STOP",         // 0xB2 stop
    "MEDIA_PLAY_PAUSE",   // 0xB3 play/pause
    "LaunchMail",         // 0xB4 mail
    "LaunchMediaSel",     // 0xB5 media select
    "LaunchApp1",         // 0xB6 application 1
    "LaunchApp2",         // 0xB7 application 2
    "non",                // 0xB8 0xB8-B9 reserved
    "non",                // 0xB9
    ":",                  // 0xBA '*:'
    ";",                  // 0xBB '+;'
    ",",                  // 0xBC どの国/地域の場合も、'<,'
    "-",                  // 0xBD どの国/地域の場合も、'=-'
    ".",                  // 0xBE 任意の国/地域の場合は、'>.'
    "/",                  // 0xBF
    "@",                  // 0xC0 @`
    "non",                // 0xC1 0xC1-D7 reserved
    "non",                // 0xC2
    "non",                // 0xC3
    "non",                // 0xC4
    "non",                // 0xC5
    "non",                // 0xC6
    "non",                // 0xC7
    "non",                // 0xC8
    "non",                // 0xC9
    "non",                // 0xCA
    "non",                // 0xCB
    "non",                // 0xCC
    "non",                // 0xCD
    "non",                // 0xCE
    "non",                // 0xCF
    "non",                // 0xD0
    "non",                // 0xD1
    "non",                // 0xD2
    "non",                // 0xD3
    "non",                // 0xD4
    "non",                // 0xD5
    "non",                // 0xD6
    "non",                // 0xD7 ↑ 0xC1-D7 reserved
    "non",                // 0xD8 ↓ 0xD8-DA unsigned
    "non",                // 0xD9
    "non",                // 0xDA ↑ 0xD8-DA unsigned
    "[",                  // 0xDB '[{'
    "|",                  // 0xDC '|\'
    "]",                  // 0xDD ']}'
    "^",                  // 0xDE '^~'
    "non",                // 0xDF
    "non",                // 0xE0 reserved
    "non",                // 0xE1 OEM 固有
    "_",                  // 0xE2 '\_'
    "non",                // 0xE3 OEM
    "non",                // 0xE4 OEM
    "ProcessKey"          // 0xE5 IME PROCESS キー
    "non",                // 0xE6   OEM
    "Packet",  // 0xE7 Unicode 文字がキーストロークであるかのように渡されます。
               // キーは PACKET 、キーボード以外の入力メソッドに使用される 32
               // ビット仮想キー値の下位ワードです。
               // 詳細については、「解説」、、およびSendInputWM_KEYDOWN「KEYBDINPUT〗」を参照してください。WM_KEYUP
    "non",     // 0xE8 Unassigned
    "non",     // 0xE9   E9-F5 OEM
    "non",     // 0xEA
    "non",     // 0xEB
    "non",     // 0xEC
    "non",     // 0xED
    "non",     // 0xEE
    "non",     // 0xEF
    "non",     // 0xF0
    "non",     // 0xF1
    "non",     // 0xF2
    "non",     // 0xF3
    "non",     // 0xF4
    "non",     // 0xF5
    "Attn",    // 0xF6 Attn
    "CrSel",   // 0xF7 CrSel
    "ExSel",   // 0xF8 ExSel
    "ErEOF",   // 0xF9 EOF を消去する
    "Play",    // 0xFA play
    "Zoom",    // 0xFB zoom
    "NoName",  // 0xFC reserved
    "PA1",     // 0xFD PA1
    "OEM_CLEAR"  // 0xFE clear key
};

#endif  // KEY_NAMES_H_