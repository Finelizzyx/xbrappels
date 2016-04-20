#include <windows.h>
#include <commctrl.h>
#include <shellapi.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <ostream>
#include "resource.h"
#include "xbrappels.h"
#include "Rappel.h"

using namespace std;

// Redessine les contrôles dans la boite de dialogue
void initDialogRappels(HWND hwndDlg)
{
    LVCOLUMN col;
    LVITEM lig;
    HWND hList = (HWND)GetDlgItem(hwndDlg, IDL_RAPPELS);
    LPSTR titre = (LPSTR)calloc(30, 1);

    // Les colonnes de la liste des rappels
    ZeroMemory(&col, sizeof(LVCOLUMN));
    col.mask    = LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

    col.cx      = 115;
    strcpy(titre, "Date - Heure");
    col.pszText = titre;
    ListView_InsertColumn(hList, 0, &col);

    col.cx      = 282;
    strcpy(titre, "Libellé");
    col.pszText = titre;
    ListView_InsertColumn(hList, 1, &col);

    col.cx      = 40;
    strcpy(titre, "Actif");
    col.pszText = titre;
    ListView_InsertColumn(hList, 2, &col);

    col.cx      = 0;
    strcpy(titre, "Détail");
    col.pszText = titre;
    ListView_InsertColumn(hList, 3, &col);

    ListView_SetBkColor(hwndDlg, RGB(100,100,100));

    // Chargement des rappels dans la liste
    ZeroMemory(&lig, sizeof(LVITEM));


    free(titre);
}

void rechercherRappels(HWND hwndDlg)
{
        //DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_RAPPEL), hwndDlg, (DLGPROC)DlgDingDing);
}

void ecrireLog(UINT gravite, const char* texte)
{
    ofstream log;
    SYSTEMTIME st;
    char d[27];
    char g[8];

    log.open("XBRappels.log", ofstream::app);
    if(log.fail()) // Le fichier n'existe pas ?
    {
        log.open("XBRappels.log", ofstream::out); // Création du fichier
        log.close();
        log.open("XBRappels.log", ofstream::app);
    }

    log.clear();

    GetLocalTime(&st);
    sprintf(d, "%02hu/%02hu/%04hu - %02hu:%02hu:%02hu.%03hu ", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

    switch(gravite)
    {
        case 3: strcpy(g, "INFO"); break;

    }

    log << d << "[" << g << "]" << " : " << texte << endl;

    log.close();
}
