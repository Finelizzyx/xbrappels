#include <windows.h>
#include "resource.h"

BOOL CALLBACK DlgAProposDe(HWND hwndDlgApd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_INITDIALOG:
            return TRUE;

        case WM_CLOSE:
            EndDialog(hwndDlgApd,0);
            return TRUE;

        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDOK:
                    SendMessage(hwndDlgApd, WM_CLOSE, 0, 0);
                    break;
            }
            return TRUE;
    }
    return FALSE;
}
