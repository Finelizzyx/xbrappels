#ifndef RAPPEL_H
#define RAPPEL_H

#include <windows.h>
#include <string>
#include "FichierRappel.h"

class Rappel : public FichierRappel
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


    protected:
    private:
        UINT m_id;
        SYSTEMTIME m_idate;
        SYSTEMTIME m_rdate;
        UINT m_status;
        std::string m_message;
        std::string m_detail;
        UINT m_encours;
};

#endif // RAPPEL_H
