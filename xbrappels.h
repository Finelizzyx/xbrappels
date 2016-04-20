#ifndef XBRAPPELS_H_INCLUDED
#define XBRAPPELS_H_INCLUDED

#ifdef MAINFILE
#define EXTERN
#else
#define EXTERN extern
#endif // MAINFILE

#define XB_WM_NOTIFYICON WM_USER+1

#define ERREUR  1
#define WARNING 2
#define INFO    3
#define DEBUG   4

#include <vector>
#include "Rappel.h"

// Notification area
EXTERN NOTIFYICONDATA tray;

// Divers
EXTERN HINSTANCE hInst;
EXTERN SYSTEMTIME st;
EXTERN std::string message;
EXTERN std::string detail;

EXTERN std::vector<Rappel> vrappels;
EXTERN std::vector<Rappel> alarmes;
EXTERN Rappel *r;

BOOL CALLBACK DlgAProposDe(HWND hwndDlgApd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgDingDing(HWND hwndDlgDing, UINT uMsg, WPARAM wParam, LPARAM lParam);

void initDialogRappels(HWND hwndDlg);
void rechercherRappels(HWND hwndDlg);
void ecrireLog(UINT gravite, const char* texte);


#endif // XBRAPPELS_H_INCLUDED
