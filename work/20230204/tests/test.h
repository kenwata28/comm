

#include <windows.h>
#include <string>

const std::string g_str_key[] {
    "-",             // 0x00 
    "VK_LBUTTON",	 // 0x01    マウスの左ボタン
    "VK_RBUTTON",	 // 0x02    マウスの右ボタン
    "VK_CANCEL",	 // 0x03	制御中断処理
    "VK_MBUTTON",	 // 0x04	マウスの中央ボタン (3 ボタン マウス)
    "VK_XBUTTON1",	 // 0x05	X1 マウス ボタン
    "VK_XBUTTON2",	 // 0x06	X2 マウス ボタン
    "-"	,            // 0x07	未定義。
    "VK_BACK",       //	0x08	BACKSPACE
    "VK_TAB",        //	0x09	Tab
    "-" ,            //	0x0A    reserved 
    "-" ,            //	0x0B    reservedd
    "VK_CLEAR",      //	0x0C	CLEAR
    "VK_RETURN",     //	0x0D	Enter
    "-" ,            //	0x0E    0x0E-0F	未定義。
    "-" ,            //	0x0F
    "VK_SHIFT",      //	0x10	Shift
    "VK_CONTROL",    //	0x11	Ctrl
    "VK_MENU",       //	0x12	ALT
    "VK_PAUSE",      //	0x13	PAUSE
    "VK_CAPITAL",    //	0x14	CAPS LOCK
    "VK_KANA",       //	0x15	IME かなモード
    "VK_HANGUEL",    //	0x15	IME ハングエル モード (互換性のために維持され、使用 VK_HANGUL)
    "VK_HANGUL",     //	0x15	IME ハングル モード
    "VK_IME_ON",     //	0x16	IME On
    "VK_JUNJA",      //	0x17	IME Junja モード
    "VK_FINAL",      //	0x18	IME Final モード
    "VK_HANJA",      //	0x19	IME Hanja モード
    "VK_KANJI",      //	0x19	IME 漢字モード
    "VK_IME_OFF",    //	0x1A	IME オフ
    "VK_ESCAPE",     //	0x1B	ESC キー
    "VK_CONVERT",    //	0x1C	IME 変換
    "VK_NONCONVERT", //	0x1D	IME 無変換
    "VK_ACCEPT",     //	0x1E	IME 使用可能
    "VK_MODECHANGE", //	0x1F	IME モード変更要求
    "VK_SPACE",      //	0x20	Space キー
    "VK_PRIOR",      //	0x21	PAGE UP キー
    "VK_NEXT",       //	0x22	PAGE DOWN キー
    "VK_END",        //	0x23	END キー
    "VK_HOME",       //	0x24	HOME キー
    "VK_LEFT",       //	0x25	左方向キー
    "VK_UP",         //	0x26	上方向キー
    "VK_RIGHT",      //	0x27	右方向キー
    "VK_DOWN",       //	0x28	下方向キー
    "VK_SELECT",     //	0x29	SELECT キー
    "VK_PRINT",      //	0x2A	PRINT キー
    "VK_EXECUTE",    //	0x2B	EXECUTE キー
    "VK_SNAPSHOT",   //	0x2C	画面の印刷キー
    "VK_INSERT",     //	0x2D	INS キー
    "VK_DELETE",     //	0x2E	DEL キー
    "VK_HELP",       //	0x2F	HELP キー
    "key_0",         // 0x30	
    "key_1",         // 0x31	
    "key_2",         // 0x32	
    "key_3",         // 0x33	
    "key_4",         // 0x34	
    "key_5",         // 0x35	
    "key_6",         // 0x36	
    "key_7",         // 0x37	
    "key_8",         // 0x38	
    "key_9",         // 0x39	
    "-" ,            // 0x3A 0x3A-40 未定義。
    "-" ,            // 0x3B
    "-" ,            // 0x3C
    "-" ,            // 0x3D
    "-" ,            // 0x3E
    "-" ,            // 0x3F
    "-" ,            // 0x40 0x3A-40 未定義。
    "key_A",         // 0x41	
    "key_B",         // 0x42	
    "key_C",         // 0x43	
    "key_D",         // 0x44	
    "key_E",         // 0x45	
    "key_F",         // 0x46	
    "key_G",         // 0x47	
    "key_H",         // 0x48	
    "key_I",         // 0x49	
    "key_J",         // 0x4A	
    "key_K",         // 0x4B	
    "key_L",         // 0x4C	
    "key_M",         // 0x4D	
    "key_N",         // 0x4E	
    "key_O",         // 0x4F	
    "key_P",         // 0x50	
    "key_Q",         // 0x51	
    "key_R",         // 0x52	
    "key_S",         // 0x53	
    "key_T",         // 0x54	
    "key_U",         // 0x55	
    "key_V",         // 0x56	
    "key_W",         // 0x57	
    "key_X",         // 0x58	
    "key_Y",         // 0x59	
    "key_Z",         // 0x5A	
    "VK_LWIN",       //	0x5B	左Windowsキー (ナチュラル キーボード)
    "VK_RWIN",       //	0x5C	右Windowsキー (ナチュラル キーボード)
    "VK_APPS",       //	0x5D	アプリケーション キー (ナチュラル キーボード)
    "-" ,            //	0x5E	予約されています。
    "VK_SLEEP",      //	0x5F	コンピューターのスリープ キー
    "VK_NUMPAD0",    //	0x60	テンキー 0 キー
    "VK_NUMPAD1",    //	0x61	テンキー 1 キー
    "VK_NUMPAD2",    //	0x62	テンキー 2 キー
    "VK_NUMPAD3",    //	0x63	テンキー 3 キー
    "VK_NUMPAD4",    //	0x64	テンキー 4 キー
    "VK_NUMPAD5",    //	0x65	テンキー 5 キー
    "VK_NUMPAD6",    //	0x66	テンキー 6 キー
    "VK_NUMPAD7",    //	0x67	テンキー 7 キー
    "VK_NUMPAD8",    //	0x68	テンキー 8 キー
    "VK_NUMPAD9",    //	0x69	テンキー 9 キー
    "VK_MULTIPLY",   //	0x6A	乗算キー
    "VK_ADD",        // 0x6B	キーの追加
    "VK_SEPARATOR",  //	0x6C	区切り記号キー
    "VK_SUBTRACT",   //	0x6D	減算キー
    "VK_DECIMAL",    //	0x6E	10 進キー
    "VK_DIVIDE",     //	0x6F	キーの分割
    "VK_F1",         //	0x70	F1 キー
    "VK_F2",         //	0x71	F2 キー
    "VK_F3",         //	0x72	F3 キー
    "VK_F4",         //	0x73	F4 キー
    "VK_F5",         //	0x74	F5 キー
    "VK_F6",         //	0x75	F6 キー
    "VK_F7",         //	0x76	F7 キー
    "VK_F8",         //	0x77	F8 キー
    "VK_F9",         //	0x78	F9 キー
    "VK_F10",        //	0x79	F10 キー
    "VK_F11",        //	0x7A	F11 キー
    "VK_F12",        //	0x7B	F12 キー
    "VK_F13",        //	0x7C	F13 キー
    "VK_F14",        //	0x7D	F14 キー
    "VK_F15",        //	0x7e	F15 キー
    "VK_F16",        //	0x7F	F16 キー
    "VK_F17",        //	0x80	F17 キー
    "VK_F18",        //	0x81	F18 キー
    "VK_F19",        //	0x82	F19 キー
    "VK_F20",        //	0x83	F20 キー
    "VK_F21",        //	0x84	F21 キー
    "VK_F22",        //	0x85	F22 キー
    "VK_F23",        //	0x86	F23 キー
    "VK_F24",        //	0x87	F24 キー
    "-" ,            //	0x88    0x88-8F	Unassigned
    "-" ,            //	0x89
    "-" ,            //	0x8A
    "-" ,            //	0x8B
    "-" ,            //	0x8C
    "-" ,            //	0x8D
    "-" ,            //	0x8E
    "-" ,            //	0x8F    0x88-8F	Unassigned
    "VK_NUMLOCK",    //	0x90	NUM LOCK キー
    "VK_SCROLL",     //	0x91	SCROLL LOCK キー
    "-",             // 0x92    0x92-96	OEM 固有
    "-",             // 0x93
    "-",             // 0x94
    "-",             // 0x95
    "-",             // 0x96
    "-" ,            //	0x97    0x97-9F	Unassigned
    "-" ,            //	0x98
    "-" ,            //	0x99
    "-" ,            //	0x9A
    "-" ,            //	0x9B
    "-" ,            //	0x9C
    "-" ,            //	0x9D
    "-" ,            //	0x9E
    "-" ,            //	0x9F
    "VK_LSHIFT",     //	0xA0	左 Shift キー
    "VK_RSHIFT",     //	0xA1	右 Shift キー
    "VK_LCONTROL",   //	0xA2	左 Ctrl キー
    "VK_RCONTROL",   //	0xA3	右 Ctrl キー
    "VK_LMENU",      //	0xA4	左 Alt キー
    "VK_RMENU",      //	0xA5	右 Alt キー
    "VK_BROWSER_BACK",        // 0xA6	ブラウザーの戻るキー
    "VK_BROWSER_FORWARD",     // 0xA7	ブラウザーの進むキー
    "VK_BROWSER_REFRESH",     // 0xA8	ブラウザーの更新キー
    "VK_BROWSER_STOP",        // 0xA9	ブラウザーの停止キー
    "VK_BROWSER_SEARCH",      // 0xAA	ブラウザーの検索キー
    "VK_BROWSER_FAVORITES",   // 0xAB	ブラウザーのお気に入りキー
    "VK_BROWSER_HOME",        // 0xAC	ブラウザーのスタートとホーム キー
    "VK_VOLUME_MUTE",         // 0xAD	音量ミュート キー
    "VK_VOLUME_DOWN",         // 0xAE	音量下げるキー
    "VK_VOLUME_UP",           // 0xAF	音量上げるキー
    "VK_MEDIA_NEXT_TRACK",    // 0xB0	次のトラックキー
    "VK_MEDIA_PREV_TRACK",    // 0xB1	前のトラック
    "VK_MEDIA_STOP",          // 0xB2	メディアの停止キー
    "VK_MEDIA_PLAY_PAUSE",    // 0xB3	メディアの再生/一時停止キー
    "VK_LAUNCH_MAIL",         // 0xB4 メール開始キー
    "VK_LAUNCH_MEDIA_SELECT", // 0xB5	メディアの選択キー
    "VK_LAUNCH_APP1",         // 0xB6	アプリケーション 1 の起動キー
    "VK_LAUNCH_APP2",         // 0xB7	アプリケーション 2 の起動キー
    "-",              // 0xB8   0xB8-B9	reserved
    "-",              // 0xB9
    "VK_OEM_1",       // 0xBA	その他の文字に使用されます。キーボードによって異なる場合があります。 米国標準キーボードの場合、';:' キー
    "VK_OEM_PLUS",    // 0xBB	任意の国/地域の場合、'+' キー
    "VK_OEM_COMMA",   // 0xBC	どの国/地域の場合も、',' キー
    "VK_OEM_MINUS",   // 0xBD	どの国/地域の場合も、'-' キー
    "VK_OEM_PERIOD",  // 0xBE	任意の国/地域の場合は、'.' キー
    "VK_OEM_2",       // 0xBF	その他の文字に使用されます。キーボードによって異なる場合があります。 米国標準キーボードの場合、'/?' key
    "VK_OEM_3",       // 0xC0	その他の文字に使用されます。キーボードによって異なる場合があります。 米国標準キーボードの場合、''~' キー
    "-",              // 0xC1   0xC1-D7	reserved
    "-",              // 0xC2
    "-",              // 0xC3
    "-",              // 0xC4
    "-",              // 0xC5
    "-",              // 0xC6
    "-",              // 0xC7
    "-",              // 0xC8
    "-",              // 0xC9
    "-",              // 0xCA
    "-",              // 0xCB
    "-",              // 0xCD
    "-",              // 0xCE
    "-",              // 0xCF
    "-",              // 0xD0
    "-",              // 0xD1  
    "-",              // 0xD2
    "-",              // 0xD3
    "-",              // 0xD4
    "-",              // 0xD5
    "-",              // 0xD6
    "-",              // 0xD7    
    "-",              // 0xD8 0xD8-DA unsigned
    "-",              // 0xD9
    "-",              // 0xDA    
    "VK_OEM_4",       // 0xDB	その他の文字に使用されます。キーボードによって異なる場合があります。 米国標準キーボードの場合、'[{' キー
    "VK_OEM_5",       // 0xDC	その他の文字に使用されます。キーボードによって異なる場合があります。 米国標準キーボードの場合、'\|' キー
    "VK_OEM_6",       // 0xDD	その他の文字に使用されます。キーボードによって異なる場合があります。 米国標準キーボードの場合、']}' キー
    "VK_OEM_7",       // 0xDE	その他の文字に使用されます。キーボードによって異なる場合があります。 米国標準キーボードの場合、"単一引用符/二重引用符" キー
    "VK_OEM_8",       // 0xDF	その他の文字に使用されます。キーボードによって異なる場合があります。
    "-",              // 0xE0	reserved
    "-",              // 0xE1	OEM 固有
    "VK_OEM_102",     // 0xE2	<>米国標準キーボードのキー、または米国以外の \\| 102 キー キーボードのキー
    "-",              // 0xE3	OEM 固有
    "-",              // 0xE4	OEM 固有    
    "VK_PROCESSKEY"   // 0xE5	IME PROCESS キー
    "-",              // 0xE6  	OEM 固有
    "VK_PACKET",      // 0xE7	Unicode 文字がキーストロークであるかのように渡されます。 キーは VK_PACKET 、キーボード以外の入力メソッドに使用される 32 ビット仮想キー値の下位ワードです。 詳細については、「解説」、、およびSendInputWM_KEYDOWN「KEYBDINPUT〗」を参照してください。WM_KEYUP
    "-",              // 0xE8	Unassigned
    "-",              // 0xE9   E9-F5 OEM 固有
    "-",              // 0xEA
    "-",              // 0xEB
    "-",              // 0xEC
    "-",              // 0xED
    "-",              // 0xEE
    "-",              // 0xEF
    "-",              // 0xF0
    "-",              // 0xF1  
    "-",              // 0xF2
    "-",              // 0xF3
    "-",              // 0xF4
    "-",              // 0xF5
    "VK_ATTN",        // 0xF6	Attn キー
    "VK_CRSEL",       // 0xF7	CrSel キー
    "VK_EXSEL",       // 0xF8	ExSel キー
    "VK_EREOF",       // 0xF9	EOF キーを消去する
    "VK_PLAY",        // 0xFA	再生キー
    "VK_ZOOM",        // 0xFB	ズーム キー
    "VK_NONAME",      // 0xFC	予約されています。
    "VK_PA1",         // 0xFD	PA1 キー
    "VK_OEM_CLEAR"   // 0xFE	クリア キー
};