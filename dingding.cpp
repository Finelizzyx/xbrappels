#include <windows.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include "resource.h"
#include "xbrappels.h"

using namespace std;

BOOL CALLBACK DlgDingDing(HWND hwndDlgDing, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HICON hSonnette = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_SONNETTE));

    switch(uMsg)
    {
        case WM_INITDIALOG:
            SetWindowPos(hwndDlgDing, HWND_TOP, 0, 0, 600, 500, SWP_NOMOVE);
            SendDlgItemMessage(hwndDlgDing, IDSONNETTE, STM_SETICON, (WPARAM)hSonnette, 0); // Afficher la sonnette
            return TRUE;

        case WM_CLOSE:
            EndDialog(hwndDlgDing,0);
            return TRUE;

        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDOK:
                    SendMessage(hwndDlgDing, WM_CLOSE, 0, 0);
                    break;
            }
            return TRUE;
    }
    return FALSE;
}
