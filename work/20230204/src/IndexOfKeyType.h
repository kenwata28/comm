#ifndef INDEX_OF_KEY_TYPE_H_
#define INDEX_OF_KEY_TYPE_H_

#include <windows.h>

#include <string>

/// どの virtual key を カウントするか決める flag.
/// true のものだけを 数える.
constexpr bool enable_to_log_keytype[] = {
    false,  // "non",           // 0x00 non
    false,  // "L_BTN",         // 0x01 mouse left click
    false,  // "R_BTN",         // 0x02 mouse left click
    false,  // "CANCEL",        // 0x03 cancel
    false,  // "MBTN",          // 0x04 mouse center Button (3 Button mouse)
    false,  // "XBTN1",         // 0x05 X1 mouse Button
    false,  // "XBTN2",         // 0x06 X2 mouse Button
    false,  // "non",           // 0x07 undefined
    false,  // "BS",            // 0x08 BACKSPACE
    false,  // "Tab",           // 0x09 Tab
    false,  // "non",           // 0x0A reserved
    false,  // "non",           // 0x0B reservedd
    false,  // "Clr",           // 0x0C CLEAR
    false,  // "Ent",           // 0x0D Enter
    false,  // "non",           // 0x0E 0x0E-0F undefined
    false,  // "non",           // 0x0F
    false,  // "Shift",         // 0x10 Shift
    false,  // "Ctrl",          // 0x11 Ctrl
    false,  // "Alt",           // 0x12 ALT
    false,  // "Pause",         // 0x13 PAUSE
    false,  // "Caps",          // 0x14 CAPS LOCK
    false,  // "Kana",          // 0x15 IME kana mode  or "Hang"?
    false,  // "IME_ON",        // 0x16 IME On
    false,  // "JUNJA",         // 0x17 IME Junja mode
    false,  // "FINAL",         // 0x18 IME Final mode or "HANJA"?
    false,  // "KANJI",         // 0x19 IME Kanji mode
    false,  // "IME_OFF",       // 0x1A IME off
    false,  // "Esc",           // 0x1B Escape
    false,  // "Convert",       // 0x1C IME convert
    false,  // "NonConvert",    // 0x1D IME no convert
    false,  // "Acc",           // 0x1E IME accept
    false,  // "ModeChange",    // 0x1F IME mode change
    false,  // "Space",         // 0x20 Space
    false,  // "PgUp",          // 0x21 PAGE UP
    false,  // "PgDw",          // 0x22 PAGE DOWN
    false,  // "End",           // 0x23 END
    false,  // "Home",          // 0x24 HOME
    false,  // "Left",          // 0x25 ←
    false,  // "Up",            // 0x26 ↑
    false,  // "Right",         // 0x27 →
    false,  // "Down",          // 0x28 ↓
    false,  // "Select",        // 0x29
    false,  // "Print",         // 0x2A
    false,  // "Exec",          // 0x2B
    false,  // "SNAPSHOT",      // 0x2C snapshot
    false,  // "Ins",           // 0x2D INS キー
    false,  // "Del",           // 0x2E DEL キー
    false,  // "Help",          // 0x2F HELP キー
    true,   // "0",             // 0x30  key
    true,   // "1",             // 0x31  key
    true,   // "2",             // 0x32  key
    true,   // "3",             // 0x33  key
    true,   // "4",             // 0x34  key
    true,   // "5",             // 0x35  key
    true,   // "6",             // 0x36  key
    true,   // "7",             // 0x37  key
    true,   // "8",             // 0x38  key
    true,   // "9",             // 0x39  key
    false,  // "non",           // 0x3A 0x3A-40 undefined
    false,  // "non",           // 0x3B
    false,  // "non",           // 0x3C
    false,  // "non",           // 0x3D
    false,  // "non",           // 0x3E
    false,  // "non",           // 0x3F
    false,  // "non",           // 0x40 0x3A-40 undefined
    true,   // "A",             // 0x41
    true,   // "B",             // 0x42
    true,   // "C",             // 0x43
    true,   // "D",             // 0x44
    true,   // "E",             // 0x45
    true,   // "F",             // 0x46
    true,   // "G",             // 0x47
    true,   // "H",             // 0x48
    true,   // "I",             // 0x49
    true,   // "J",             // 0x4A
    true,   // "K",             // 0x4B
    true,   // "L",             // 0x4C
    true,   // "M",             // 0x4D
    true,   // "N",             // 0x4E
    true,   // "O",             // 0x4F
    true,   // "P",             // 0x50
    true,   // "Q",             // 0x51
    true,   // "R",             // 0x52
    true,   // "S",             // 0x53
    true,   // "T",             // 0x54
    true,   // "U",             // 0x55
    true,   // "V",             // 0x56
    true,   // "W",             // 0x57
    true,   // "X",             // 0x58
    true,   // "Y",             // 0x59
    true,   // "Z",             // 0x5A
    false,  // "LWin",          // 0x5B
    false,  // "RWin",          // 0x5C
    false,  // "Apps",          // 0x5D
    false,  // "non",           // 0x5E reserved
    false,  // "Sleep",         // 0x5F sleep key
    false,  // "NumPad0",       // 0x60 テンキー 0
    false,  // "NumPad1",       // 0x61 テンキー 1
    false,  // "NumPad2",       // 0x62 テンキー 2
    false,  // "NumPad3",       // 0x63 テンキー 3
    false,  // "NumPad4",       // 0x64 テンキー 4
    false,  // "NumPad5",       // 0x65 テンキー 5
    false,  // "NumPad6",       // 0x66 テンキー 6
    false,  // "NumPad7",       // 0x67 テンキー 7
    false,  // "NumPad8",       // 0x68 テンキー 8
    false,  // "NumPad9",       // 0x69 テンキー 9
    false,  // "Multiply",      // 0x6A 乗算 key
    false,  // "Add",           // 0x6B
    false,  // "Separate",      // 0x6C 区切り記号key
    false,  // "Subtract",      // 0x6D 減算key
    false,  // "Decimal",       // 0x6E 10 進key
    false,  // "Divide",        // 0x6F
    false,  // "F1",            // 0x70 F1
    false,  // "F2",            // 0x71 F2
    false,  // "F3",            // 0x72 F3
    false,  // "F4",            // 0x73 F4
    false,  // "F5",            // 0x74 F5
    false,  // "F6",            // 0x75 F6
    false,  // "F7",            // 0x76 F7
    false,  // "F8",            // 0x77 F8
    false,  // "F9",            // 0x78 F9
    false,  // "F10",           // 0x79 F10
    false,  // "F11",           // 0x7A F11
    false,  // "F12",           // 0x7B F12
    false,  // "F13",           // 0x7C F13
    false,  // "F14",           // 0x7D F14
    false,  // "F15",           // 0x7e F15
    false,  // "F16",           // 0x7F F16
    false,  // "F17",           // 0x80 F17
    false,  // "F18",           // 0x81 F18
    false,  // "F19",           // 0x82 F19
    false,  // "F20",           // 0x83 F20
    false,  // "F21",           // 0x84 F21
    false,  // "F22",           // 0x85 F22
    false,  // "F23",           // 0x86 F23
    false,  // "F24",           // 0x87 F24
    false,  // "non",           // 0x88 0x88-8F Unassigned
    false,  // "non",           // 0x89
    false,  // "non",           // 0x8A
    false,  // "non",           // 0x8B
    false,  // "non",           // 0x8C
    false,  // "non",           // 0x8D
    false,  // "non",           // 0x8E
    false,  // "non",           // 0x8F 0x88-8F Unassigned
    false,  // "NumLk",              // 0x90
    false,  // "ScrLk",              // 0x91
    false,  // "non",                // 0x92    0x92-96
    false,  // "non",                // 0x93
    false,  // "non",                // 0x94
    false,  // "non",                // 0x95
    false,  // "non",                // 0x96
    false,  // "non",                // 0x97    0x97-9F Unassigned
    false,  // "non",                // 0x98
    false,  // "non",                // 0x99
    false,  // "non",                // 0x9A
    false,  // "non",                // 0x9B
    false,  // "non",                // 0x9C
    false,  // "non",                // 0x9D
    false,  // "non",                // 0x9E
    false,  // "non",                // 0x9F
    false,  // "LShift",             // 0xA0
    false,  // "RShift",             // 0xA1
    false,  // "LCtrl",              // 0xA2
    false,  // "RCtrl",              // 0xA3
    false,  // "LAlt",               // 0xA4
    false,  // "RAlt",               // 0xA5
    false,  // "BROWSER_BACK",       // 0xA6 browser
    false,  // "BROWSER_FORWARD",    // 0xA7
    false,  // "BROWSER_REFRESH",    // 0xA8
    false,  // "BROWSER_STOP",       // 0xA9
    false,  // "BROWSER_SEARCH",     // 0xAA
    false,  // "BROWSER_FAVORITES",  // 0xAB
    false,  // "BROWSER_HOME",       // 0xAC
    false,  // "VolMute",            // 0xAD vol
    false,  // "VolDw",              // 0xAE
    false,  // "VolUp",              // 0xAF
    false,  // "MEDIA_NEXT_TRACK",   // 0xB0 next track
    false,  // "MEDIA_PREV_TRACK",   // 0xB1 previout track
    false,  // "MEDIA_STOP",         // 0xB2 stop
    false,  // "MEDIA_PLAY_PAUSE",   // 0xB3 play/pause
    false,  // "LaunchMail",         // 0xB4 mail
    false,  // "LaunchMediaSel",     // 0xB5 media select
    false,  // "LaunchApp1",         // 0xB6 application 1
    false,  // "LaunchApp2",         // 0xB7 application 2
    false,  // "non",                // 0xB8 0xB8-B9 reserved
    false,  // "non",                // 0xB9
    true,   // ":",                  // 0xBA '*:'
    true,   // ";",                  // 0xBB '+;'
    true,   // ",",                  // 0xBC どの国/地域の場合も、'<,'
    true,   // "-",                  // 0xBD どの国/地域の場合も、'=-'
    true,  // ".",                  // 0xBE 任意の国/地域の場合は、'>.'
    true,   // "/",                  // 0xBF
    true,   // "@",                  // 0xC0 @`
    false,  // "non",                // 0xC1 0xC1-D7 reserved
    false,  // "non",                // 0xC2
    false,  // "non",                // 0xC3
    false,  // "non",                // 0xC4
    false,  // "non",                // 0xC5
    false,  // "non",                // 0xC6
    false,  // "non",                // 0xC7
    false,  // "non",                // 0xC8
    false,  // "non",                // 0xC9
    false,  // "non",                // 0xCA
    false,  // "non",                // 0xCB
    false,  // "non",                // 0xCC
    false,  // "non",                // 0xCD
    false,  // "non",                // 0xCE
    false,  // "non",                // 0xCF
    false,  // "non",                // 0xD0
    false,  // "non",                // 0xD1
    false,  // "non",                // 0xD2
    false,  // "non",                // 0xD3
    false,  // "non",                // 0xD4
    false,  // "non",                // 0xD5
    false,  // "non",                // 0xD6
    false,  // "non",                // 0xD7 ↑ 0xC1-D7 reserved
    false,  // "non",                // 0xD8 ↓ 0xD8-DA unsigned
    false,  // "non",                // 0xD9
    false,  // "non",                // 0xDA ↑ 0xD8-DA unsigned
    true,   // "[",                  // 0xDB '[{'
    true,   // "|",                  // 0xDC '|\'
    true,   // "]",                  // 0xDD ']}'
    true,   // "^",                  // 0xDE '^~'
    false,  // "non",                // 0xDF
    false,  // "non",                // 0xE0 reserved
    false,  // "non",                // 0xE1 OEM
    true,   // "_",                  // 0xE2 '\_'
    false,  // "non",                // 0xE3 OEM
    false,  // "non",                // 0xE4 OEM
    false,  // "ProcessKey"          // 0xE5 IME PROCESS KEY
    false,  // "non",                // 0xE6   OEM
    false,  // "Packet",             // 0xE7
    false,  // "non",     // 0xE8 Unassigned
    false,  // "non",     // 0xE9   E9-F5 OEM
    false,  // "non",     // 0xEA
    false,  // "non",     // 0xEB
    false,  // "non",     // 0xEC
    false,  // "non",     // 0xED
    false,  // "non",     // 0xEE
    false,  // "non",     // 0xEF
    false,  // "non",     // 0xF0
    false,  // "non",     // 0xF1
    false,  // "non",     // 0xF2
    false,  // "non",     // 0xF3
    false,  // "non",     // 0xF4
    false,  // "non",     // 0xF5
    false,  // "Attn",    // 0xF6 Attn
    false,  // "CrSel",   // 0xF7 CrSel
    false,  // "ExSel",   // 0xF8 ExSel
    false,  // "ErEOF",   // 0xF9 delete EOF
    false,  // "Play",    // 0xFA play
    false,  // "Zoom",    // 0xFB zoom
    false,  // "NoName",  // 0xFC reserved
    false,  // "PA1",     // 0xFD PA1
    false,  // "OEM_CLEAR"  // 0xFE clear key
};

#endif  // INDEX_OF_KEY_TYPE_H_