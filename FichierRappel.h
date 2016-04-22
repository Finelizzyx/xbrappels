#ifndef FICHIERRAPPEL_H
#define FICHIERRAPPEL_H

#include <string>

typedef struct _frappel {
    struct _sentete {
        char fixe[10];
        char id[6];
    } sentete;
    char initdate[13];
    char rapdate[13];
    struct _sobjet {
        char dobjet[7];
        char *objet;
        char fobjet[5];
    } sobjet;
    struct _sdetail {
        char ddetail[7];
        char *detail;
        char fdetail[5];
    } sdetail;
    char statut;
    char fin[7];
    char retourchariot;
} frappel;

class FichierRappel
{
    public:
        FichierRappel(char *idate, char *objet, char *detail);
        FichierRappel();
        virtual ~FichierRappel();
        int ecrire();
    protected:
    private:
        frappel m_frappel;
        unsigned int m_idmax;

        char *strsub(const char* chaine, int d, int n);
};

#endif // FICHIERRAPPEL_H
