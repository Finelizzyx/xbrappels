#ifndef RAPPEL_H
#define RAPPEL_H

#include <windows.h>
#include <string>

typedef struct tRappels {
    UINT m_id;
    SYSTEMTIME m_date;
    SYSTEMTIME m_rdate;
    std::string m_message;
    UINT m_status;
    std::string m_detail;
    UINT m_encours;
} tRappel;

class Rappel
{
    public:
        Rappel(SYSTEMTIME pdate, std::string message, std::string detail);
        Rappel();
        virtual ~Rappel();
        UINT getId();
        void setId(UINT id);
        SYSTEMTIME getDate();
        void setDate(SYSTEMTIME st);
        std::string getMessage();
        void setMessage(std::string message);
        std::string getDetail();
        void setDetail(std::string detail);
        UINT getStatus();
        void setStatus(UINT status);
        UINT getEncours();
        void setEncours(UINT encours);

        void ajouter();
        void miseAJour();

    protected:
    private:
        tRappel trappel;
};

#endif // RAPPEL_H
