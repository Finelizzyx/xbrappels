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
    m_idmax = 0; //TODO : A la place, calculer l'idmax par lecteure séquentiel du fichier

    m_frappel.sobjet.objet = (char*)malloc(strlen(objet));
    m_frappel.sdetail.detail = (char*)malloc(strlen(detail));

    strcpy(m_frappel.sentete.fixe, "###RAPPEL");
    sprintf(m_frappel.sentete.id, "%05d", ++m_idmax);
    sprintf(m_frappel.initdate, "%4s%2s%2s%2s%2s", strsub(idate, 6, 4), strsub(idate, 3, 2), strsub(idate, 0, 2),strsub(idate, 10, 2),strsub(idate, 13, 2));
    sprintf(m_frappel.rapdate, "%4s%2s%2s%2s%2s", strsub(idate, 6, 4), strsub(idate, 3, 2), strsub(idate, 0, 2),strsub(idate, 10, 2),strsub(idate, 13, 2));
    strcpy(m_frappel.sobjet.dobjet, "#DEBUT");
    strcpy(m_frappel.sobjet.objet, objet);
    strcpy(m_frappel.sobjet.fobjet, "#FIN");
    strcpy(m_frappel.sdetail.ddetail, "#DEBUT");
    strcpy(m_frappel.sdetail.detail, detail);
    strcpy(m_frappel.sdetail.fdetail, "#FIN");
    m_frappel.statut = '1';
    strcpy(m_frappel.fin, "###FIN");
    m_frappel.retourchariot = '\n';
}

FichierRappel::~FichierRappel()
{
    free(m_frappel.sobjet.objet);
    free(m_frappel.sdetail.detail);

}

int FichierRappel::ecrire() {
    HANDLE hFile;
    PDWORD ecrits = NULL;

    hFile = CreateFile("xbrappels.dat", GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if(hFile == INVALID_HANDLE_VALUE) {
        MessageBox(NULL, "Erreur lors de l'ouverture du fichier de données !", "XBRappels", MB_ICONERROR | MB_OK);
        return 2;
    }

    WriteFile(hFile, &m_frappel, sizeof(m_frappel), ecrits, NULL);
    if(ecrits == 0)
        MessageBox(NULL, "Erreur d'éciriture dans le fichier!", "XBRappels", MB_ICONERROR | MB_OK);
    CloseHandle(hFile);
    return 0;
}

char *FichierRappel::strsub(const char *chaine, int d, int n) // Retourne la sous-chaine de "n" caractères depuis la position "d" dans "chaine"
{
    char *retour = (char*)malloc(n+1);
    int i;

    for(i = 0; i < n; i++)
        *(retour+i) = *(chaine+i+d);
    *(retour+n) = 0;
    return retour;
}

