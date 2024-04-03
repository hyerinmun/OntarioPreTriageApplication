#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "Patient.h"
#include "Utils.h" 

using namespace std;
namespace seneca {

    Patient::Patient(int ticketNumber, bool fileIO) : m_name(nullptr), m_OHIP(0), m_ticket(ticketNumber), m_fileIO(fileIO) {
    }

    Patient::Patient(const Patient& src) : m_name(nullptr), m_OHIP(src.m_OHIP), m_ticket(src.m_ticket), m_fileIO(src.m_fileIO) {
        if (src.m_name != nullptr) {
            m_name = new char[strlen(src.m_name) + 1];
            strcpy(m_name, src.m_name);
        }
        else {
            m_name = nullptr;
        }
    }
    Patient& Patient::operator=(const Patient& src) {
        if (this != &src) {
            delete[] m_name; // Free existing resource
            m_ticket = src.m_ticket;
            m_fileIO = src.m_fileIO;
            m_OHIP = src.m_OHIP;

            if (src.m_name != nullptr) {
                m_name = new char[strlen(src.m_name) + 1];
                strcpy(m_name, src.m_name);
            }
            else {
                m_name = nullptr;
            }
        }
        return *this;
    }

    Patient::~Patient() {
        delete[] m_name;
    }


    bool Patient::operator==(char c) const {
        return type() == c;
    }

    bool Patient::operator==(const Patient& other) const {
        return type() == other.type();
    }


    void Patient::setArrivalTime() {
        m_ticket.resetTime();
    }

    Time Patient::time() const {
        return m_ticket.time();
    }

    int Patient::number() const {
        return m_ticket.number();
    }

    Patient::operator bool() const {
        return m_name != nullptr && m_OHIP >= 100000000 && m_OHIP <= 999999999;
    }

    Patient::operator const char* () const {
        return m_name;
    }

    ostream& Patient::write(ostream& ostr) const {
        if (*this) { // Valid patient
            if (&ostr == &cout) {
                m_ticket.write(ostr) << endl;
                if (strlen(m_name) > 50) {
                    char truncatedName[51];
                    strncpy(truncatedName, m_name, 50);
                    truncatedName[50] = '\0'; // Ensure null termination
                    ostr << truncatedName;
                }
                else {
                    ostr << m_name;
                }
                ostr << ", OHIP: " << m_OHIP << endl;
            }
            else if (&ostr == &clog) {
                ostr << left << setw(53) << setfill('.') << m_name
                    << right << setw(9) << m_OHIP << setfill(' ') << setw(5) << m_ticket.number() << " " << m_ticket.time();
            }
            else { // For other ostream types, write CSV format
                ostr << type() << ',' << m_name << ',' << m_OHIP << ',';
                m_ticket.write(ostr);
            }
        }
        else {
            ostr << "Invalid Patient Record" << endl;
        }
        return ostr;
    }

   istream& Patient::read(istream& istr) {
        if (&istr == &cin) {
            char buffer[51];
            cout << "Name: ";
            istr.get(buffer, 51, '\n');
            istr.clear();
            istr.ignore(1000, '\n');

            delete[] m_name;
            m_name = new char[strlen(buffer) + 1];
            strcpy(m_name, buffer);

            cout << "OHIP: ";
            m_OHIP = U.getInt(100000000, 999999999);
            
            //when i remove line 139, it put the correct output for ticket number but
            // i dont think it's through the ticket read bc it doesnt read the time
            //when i not comment line 139, it asks me to enter console input for m_number
           // m_ticket.read(istr);
        }
        else {
            char tempName[100];
            istr.get(tempName, 100, ',');
            delete[] m_name;
            m_name = new char[strlen(tempName) + 1];
            strcpy(m_name, tempName);
            istr.ignore(1000, ','); 

            // Read OHIP
            istr >> m_OHIP;
            if (istr.fail() || m_OHIP < 100000000 || m_OHIP > 999999999) {
                delete[] m_name;
                m_name = nullptr;
                m_OHIP = 0;
                istr.clear();
            }
            istr.ignore(1000, ',');

           // m_ticket.read(istr);
        }
        m_ticket.read(istr);
        return istr;
   }

}
