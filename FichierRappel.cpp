#include <string.h>
#include <stdio.h>
#include <windows.h>
#include "FichierRappel.h"

FichierRappel::FichierRappel()
{
    //ctor
}

FichierRappel::FichierRappel(char *idate, char *objet, char *detail)
{
    m_idmax = 0; //TODO : A la place, calucler l'idmax par lecteure séquentiel du fichier

    strcpy(m_frappel.sentete.fixe, "###RAPPEL");
    sprintf(m_frappel.sentete.id, "%50d", ++m_idmax);
    strcpy(m_frappel.initdate, idate);
    strcpy(m_frappel.rapdate, idate);
    strcpy(m_frappel.sobjet.dobjet, "#DEBUT");
    m_frappel.sobjet.objet = objet;
    strcpy(m_frappel.sobjet.fobjet, "#FIN");
    strcpy(m_frappel.sdetail.ddetail, "#DEBUT");
    m_frappel.sdetail.detail = detail;
    strcpy(m_frappel.sdetail.fdetail, "#FIN");
    m_frappel.statut = '1';
    strcpy(m_frappel.fin, "###FIN");
    m_frappel.retourchariot = '\n';
}

FichierRappel::~FichierRappel()
{

}

int FichierRappel::ecrire() {
    LPOFSTRUCT os;
    HFILE hFile;
    HANDLE f;
    PDWORD ecrits;

    hFile = OpenFile("xbrappels.dat", os, OF_EXIST);
    if(hFile == HFILE_ERROR) f = CreateFile("xbrappels.dat", os, OF_CREATE);
    else f = OpenFile("xbrappels.dat", os, OF_WRITE);

    WriteFile(f, &m_frappel, sizeof(m_frappel), ecrits, NULL);
    if(*ecrits == 0) MessageBox(NULL, "Erreur d'éciriture dans le fichier!", "XbRappels", MB_ICONERROR | MB_OK);
    CloseHandle(f);
    return 0;
}
