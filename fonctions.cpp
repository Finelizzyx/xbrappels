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
    ifstream f;
    string lrappel;
    LVCOLUMN col;
    LVITEM lig;
    string lentete;
    string ldate;
    string llibelle;
    string lactive;
    string ldetail;
    int i; // compteur des rappels lus
    int p, q; // Position des recherches dans la chaine lrappel
    Rappel rtemp;
    HWND hList = (HWND)GetDlgItem(hwndDlg, IDL_RAPPELS);
    LPSTR titre = (LPSTR)calloc(30, 1);
    SYSTEMTIME stemp;

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
    i = 0;
    f.open("XBRappels.dat", fstream::in);
    if(!f.fail())
    {


        getline(f, lentete);
        while(getline(f, lrappel)) // Lecture ligne d'entête du rappel - Si KO c'est que fin de fichier
        {
            rtemp.setId(atoi(lrappel.substr(22, 5).c_str()));
            getline(f, lrappel);
            lig.mask = LVIF_TEXT;
            lig.iItem = i;
            lig.iSubItem = 0;
            p = lrappel.find(";");
            ldate = lrappel.substr(0, p);
            lig.pszText = (LPSTR)ldate.c_str();
            ListView_InsertItem(hList, &lig);

            stemp.wDay    = atoi(ldate.substr(0, 2).c_str());
            stemp.wMonth  = atoi(ldate.substr(3, 2).c_str());
            stemp.wYear   = atoi(ldate.substr(6, 4).c_str());
            stemp.wHour   = atoi(ldate.substr(11, 2).c_str());
            stemp.wMinute = atoi(ldate.substr(14, 2).c_str());
            stemp.wSecond = atoi(ldate.substr(17, 2).c_str());
            rtemp.setDate(stemp);

            // Insérer la raison du rappel en colonne 2
            lig.iSubItem = 1;
            q = lrappel.find(";", p+1);
            llibelle = lrappel.substr(p+1, q-p-1);
            lig.pszText = (LPSTR)llibelle.c_str();
            SendMessage(hList, LVM_SETITEM, 0, (LPARAM)&lig);
            rtemp.setMessage(llibelle);

            // Insérer le statut en colonne 2
            lig.iSubItem = 2;
            lactive = lrappel.substr(q+1, 1);
            lig.pszText = (LPSTR)lactive.c_str();
            SendMessage(hList, LVM_SETITEM, 0, (LPARAM)&lig);
            rtemp.setStatus(atoi(lactive.c_str()));

            // On tourne jusque #####
            ldetail.erase(0, ldetail.length());
            getline(f, lrappel);
            while(lrappel != "#####") {
                ldetail+=lrappel;
                getline(f, lrappel);
                if(lrappel != "#####") ldetail+='\x0A'; // Retour chariot à la fin des lignes lues sauf la dernière
            }

            // Insérer le détail en colonne 3
            lig.iSubItem = 3;
            lig.pszText = (LPSTR)ldetail.c_str();
            SendMessage(hList, LVM_SETITEM, 0, (LPARAM)&lig);
            rtemp.setDetail(ldetail);
            rtemp.setEncours(0);

            vrappels.push_back(rtemp);

            i++;
        }
    }


    f.close();
    free(titre);
}

void rechercherRappels(HWND hwndDlg)
{
    string srappels;
    char *actualTime = (char*)calloc(32, 1);
    char *rappelTime = (char*)calloc(32, 1);
    Rappel rtemp;
    SYSTEMTIME ast;
    SYSTEMTIME rst;
    char logmessage[1024];

    GetLocalTime(&ast);
    sprintf(actualTime, "%04hu%02hu%02hu%02hu%02hu", ast.wYear, ast.wMonth, ast.wDay, ast.wHour, ast.wMinute);

    alarmes.clear();

    for(unsigned int i = 0; i < vrappels.size(); i++)
    {
        rtemp = vrappels[i];
        rst = rtemp.getDate();
        sprintf(rappelTime, "%04hu%02hu%02hu%02hu%02hu", rst.wYear, rst.wMonth, rst.wDay, rst.wHour, rst.wMinute);
        if(strcmp(actualTime, rappelTime) >= 0)
        {
            if(rtemp.getEncours() == 0 && rtemp.getStatus() == 1) // Le rappel détecté n'est pas déjà en cours et est actif
            {
                vrappels[i].setEncours(1);
                sprintf(logmessage, "Rappel %05u détecté pour alarme. Message : %s", rtemp.getId(), rtemp.getMessage().c_str());
                ecrireLog(INFO, logmessage);
                alarmes.push_back(rtemp);
            }
        }
    }
    if(alarmes.size() > 0)
        DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_RAPPEL), hwndDlg, (DLGPROC)DlgDingDing);
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
