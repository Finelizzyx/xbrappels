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
    SYSTEMTIME vdateHeure;
    stringstream vcdateHeure;

    switch(uMsg)
    {
        case WM_INITDIALOG:
            SetWindowPos(hwndDlgDing, HWND_TOP, 0, 0, 600, 500, SWP_NOMOVE);
            SendDlgItemMessage(hwndDlgDing, IDSONNETTE, STM_SETICON, (WPARAM)hSonnette, 0); // Afficher la sonnette
            for(unsigned int i = 1; i <= alarmes.size(); i++) // On liste les alarmes
            {

                vdateHeure = alarmes[i].getDate();
                vcdateHeure << setfill('0');
                vcdateHeure << setw(2) << vdateHeure.wDay << "/" << setw(2) << vdateHeure.wMonth << "/" << setw(4) << vdateHeure.wYear << " - " << setw(2) << vdateHeure.wHour << " heures " << setw(2) << vdateHeure.wMinute << " - Objet : " << alarmes[i].getMessage();
                SetDlgItemText(hwndDlgDing, IDE_DING_DATE, vcdateHeure.str().c_str());
                SetDlgItemText(hwndDlgDing, IDE_DING_DETAIL, alarmes[i].getDetail().c_str());
            }
            return TRUE;

        case WM_CLOSE:
            EndDialog(hwndDlgDing,0);
            return TRUE;

        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDOK:
                    //alarmes[i].setStatus(0);
                    //alarmes[i].miseAJour();
                    SendMessage(hwndDlgDing, WM_CLOSE, 0, 0);
                    break;
            }
            return TRUE;
    }
    return FALSE;
}
