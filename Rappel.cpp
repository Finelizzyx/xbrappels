#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include "Rappel.h"
#include "xbrappels.h"

using namespace std;

Rappel::Rappel(SYSTEMTIME pdate, string message, string detail) : m_idate(pdate), m_rdate(pdate), m_message(message), m_detail(detail)
{
    m_encours = 0;
    m_status  = 1;
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
    return m_id;
}

void Rappel::setId(UINT id)
{
    m_id = id;
}

SYSTEMTIME Rappel::getDate()
{
    return m_idate;
}

void Rappel::setDate(SYSTEMTIME st)
{
    m_idate = st;
}

string Rappel::getMessage()
{
    return m_message;
}

void Rappel::setMessage(string message)
{
    m_message = message;
}

string Rappel::getDetail()
{
    return m_detail;
}

void Rappel::setDetail(string detail)
{
    m_detail = detail;
}

UINT Rappel::getStatus()
{
    return m_status;
}

void Rappel::setStatus(UINT status)
{
    m_status = status;
}

UINT Rappel::getEncours()
{
    return m_encours;
}

void Rappel::setEncours(UINT encours)
{
    m_encours = encours;
}



