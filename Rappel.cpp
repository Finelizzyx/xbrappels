#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include "Rappel.h"
#include "xbrappels.h"

using namespace std;

Rappel::Rappel(SYSTEMTIME pdate, string message, string detail) : m_date(pdate), m_message(message), m_detail(detail)
{
    tRappel.m_encours = 0;
    tRappel.m_status  = 1;
    ajouter();
}

Rappel::Rappel()
{
 // Constructeur que ne fait rien
}

Rappel::~Rappel()
{
    //dtor
}

UINT Rappel::getId()
{
    return tRappel.m_id;
}

void Rappel::setId(UINT id)
{
    tRappel.m_id = id;
}

SYSTEMTIME Rappel::getDate()
{
    return tRappel.m_date;
}

void Rappel::setDate(SYSTEMTIME st)
{
    tRappel.m_date = st;
}

string Rappel::getMessage()
{
    return tRappel.m_message;
}

void Rappel::setMessage(string message)
{
    tRappel.m_message = message;
}

string Rappel::getDetail()
{
    return tRappel.m_detail;
}

void Rappel::setDetail(string detail)
{
    tRappel.m_detail = detail;
}

UINT Rappel::getStatus()
{
    return tRappel.m_status;
}

void Rappel::setStatus(UINT status)
{
    tRappel.m_status = status;
}

UINT Rappel::getEncours()
{
    return tRappel.m_encours;
}

void Rappel::setEncours(UINT encours)
{
    tRappel.m_encours = encours;
}


void Rappel::ajouter()
{

}

void Rappel::miseAJour()
{

}

