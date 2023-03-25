#include <windows.h>
#include <iostream>
//NOTIFYICONDATA ni_data;

BOOL InitIcon() {
    NOTIFYICONDATA data;
    ZeroMemory(&data, sizeof(NOTIFYICONDATA));

    data.cbSize = sizeof(NOTIFYICONDATA);
    data.hWnd = NULL;
    data.uID = 1;      
    //HICON hIcon = LoadIcon(NULL, __TEXT("a.ico"));
    HICON hIcon = (HICON)LoadImage(NULL, __TEXT("./a.ico"), IMAGE_ICON, 16, 16, LR_LOADFROMFILE | LR_SHARED);
    if (hIcon == nullptr) puts("false");
    data.hIcon = hIcon;
    data.uFlags = NIF_ICON | NIF_TIP;

    //BOOL ret = Shell_NotifyIcon(NIM_MODIFY, &data);
    BOOL ret = Shell_NotifyIcon(NIM_ADD, &data);

    printf("init icon done : %d\n", ret);

    return ret;
}
