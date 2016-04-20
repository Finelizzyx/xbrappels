#define MAINFILE

#include <windows.h>
#include <commctrl.h>
#include <shellapi.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "resource.h"
#include "Rappel.h"
#include "xbrappels.h"

using namespace std;

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HMENU hmenu;
    HMENU hpopup;
    POINT pos;
    char *dateHeure;
    char *m;
    char *d;
    // ListView
    HWND hList;
    int nbitems;
    int idRappel;
    char rText[128];
    string sText;
    SYSTEMTIME stList;

    switch(uMsg)
    {
        case WM_INITDIALOG:
            ZeroMemory(&tray, sizeof(NOTIFYICONDATA));
            tray.cbSize = sizeof(tray);
            tray.hWnd = hwndDlg;
            tray.uID = 0;
            tray.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
            tray.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_MAIN));
            tray.uCallbackMessage = XB_WM_NOTIFYICON;
            strcpy(tray.szTip, "XB Rappels");
            Shell_NotifyIcon(NIM_ADD, &tray);

            initDialogRappels(hwndDlg);

            SetTimer(hwndDlg, 1, 1000, NULL);

            return TRUE;

        case WM_CLOSE:
            ShowWindow(hwndDlg, SW_HIDE);
            Shell_NotifyIcon(NIM_ADD, &tray);
            return TRUE;

        case XB_WM_NOTIFYICON:
            if(lParam == WM_LBUTTONUP) {
                ShowWindow(hwndDlg, SW_SHOW);
                Shell_NotifyIcon(NIM_DELETE, &tray);
            }
            if(lParam == WM_RBUTTONUP)
            {
                GetCursorPos(&pos);
                hmenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU_TRAY));
                hpopup = GetSubMenu(hmenu, 0);
                SetForegroundWindow(hwndDlg);
                TrackPopupMenuEx(hpopup, 0, pos.x, pos.y, hwndDlg, NULL);
                DestroyMenu(hmenu);
            }
            return TRUE;

        case WM_TIMER:
            rechercherRappels(hwndDlg);
            return TRUE;

        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDM_QUITTER:
                    KillTimer(hwndDlg, 1);
                    Shell_NotifyIcon(NIM_DELETE, &tray);
                    EndDialog(hwndDlg,0);
                    break;

                case IDM_GERER:
                    SendMessage(hwndDlg, XB_WM_NOTIFYICON, 0, WM_LBUTTONUP);
                    break;

                case IDM_APROPOS:
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_APROPOS), NULL, (DLGPROC)DlgAProposDe);
                    break;

                case IDB_FERMER:
                    SendMessage(hwndDlg, WM_CLOSE, 0, 0);
                    break;

                case IDB_AJOUTER:
                    dateHeure = (char*)calloc(20, 1);
                    m = (char*)calloc(128, 1);
                    d = (char*)calloc(1024,1);
                    GetDlgItemText(hwndDlg, IDE_DATE, dateHeure, 11);
                    dateHeure[10] = 32; // Espace entre date et heure
                    GetDlgItemText(hwndDlg, IDE_HEURE, dateHeure+11, 10);
                    if(SendDlgItemMessage(hwndDlg, IDE_MESSAGE, EM_LINELENGTH, (WPARAM) 0, (LPARAM) 0) == 0) // Taille de ce qui a été saisi dans la zone libellé
                    {
                        // TODO : Faire clignoter la zone de saisie "message" pour montrer qu'elle est vide
                    }
                    else
                    {
                        GetDlgItemText(hwndDlg, IDE_MESSAGE, m, 128);
                        GetDlgItemText(hwndDlg, IDE_DETAIL, d, 1024);
                        sscanf(dateHeure, "%02hu/%02hu/%04hu %02hu:%02hu:%02hu", &st.wDay, &st.wMonth, &st.wYear, &st.wHour, &st.wMinute, &st.wSecond);
                        message=m;
                        detail=d;
                        r = new Rappel(st, message, detail);
                        // On ajoute un élément dans la liste
                        hList = (HWND)GetDlgItem(hwndDlg, IDL_RAPPELS);
                        nbitems = ListView_GetItemCount(hList) + 1;
                        r->setId(nbitems-1); // Nombre d'items -1 => N° du rappel à ajouter !
                        vrappels.push_back(*r);

                        //On reconstruit la liste
                        ListView_DeleteAllItems(hList);
                        initDialogRappels(hwndDlg);

                        // Mise à blanc du message et du détail
                        SetWindowText(GetDlgItem(hwndDlg, IDE_MESSAGE), "" );
                        SetWindowText(GetDlgItem(hwndDlg, IDE_DETAIL), "");


                    }
                    free(dateHeure);
                    free(m);
                    free(d);
                    break;

                }
            return TRUE;

        case WM_NOTIFY:
            switch (((LPNMHDR)lParam)->code)
            {
                case NM_CLICK:
                    if(((LPNMHDR)lParam)->idFrom == IDL_RAPPELS)
                    {
                        hList = GetDlgItem(hwndDlg, IDL_RAPPELS);
                        idRappel = SendMessage(hList, LVM_GETNEXTITEM, -1, LVNI_SELECTED);

                        ListView_GetItemText(hList, idRappel, 0, rText, 128); // Récupération date et heure
                        sText = rText;
                        stList.wDay   = atoi(sText.substr(0, 2).c_str());
                        stList.wMonth = atoi(sText.substr(3, 2).c_str());
                        stList.wYear  = atoi(sText.substr(6, 4).c_str());
                        stList.wHour  = atoi(sText.substr(11, 2).c_str());
                        stList.wMinute= atoi(sText.substr(14, 2).c_str());
                        stList.wSecond= atoi(sText.substr(17, 2).c_str());
                        DateTime_SetSystemtime(GetDlgItem(hwndDlg, IDE_DATE), GDT_VALID, &stList);
                        DateTime_SetSystemtime(GetDlgItem(hwndDlg, IDE_HEURE), GDT_VALID, &stList);

                        ListView_GetItemText(hList, idRappel, 1, rText, 128); // Récupération du message
                        SetWindowText(GetDlgItem(hwndDlg, IDE_MESSAGE), rText);

                        ListView_GetItemText(hList, idRappel, 3, rText, 128); // Récupération du détail
                        SetWindowText(GetDlgItem(hwndDlg, IDE_DETAIL), rText);

                    }
                    break;
            }
            break;

            return TRUE;

        case WM_DRAWITEM:
            MessageBox(NULL, "Message WM_DRAWITEM", "XBRappels", MB_OK);
            return TRUE;


    }
    return FALSE;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst=hInstance;
    InitCommonControls();

    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}
