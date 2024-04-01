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

    std::ostream& Patient::write(std::ostream& ostr) const {
        if (*this) { // Valid patient
            if (&ostr == &std::cout) {
                m_ticket.write(ostr) << std::endl;
                if (strlen(m_name) > 50) {
                    char truncatedName[51];
                    strncpy(truncatedName, m_name, 50);
                    truncatedName[50] = '\0'; // Ensure null termination
                    ostr << truncatedName;
                }
                else {
                    ostr << m_name;
                }
                ostr << ", OHIP: " << m_OHIP << std::endl;
            }
            else if (&ostr == &std::clog) {
                ostr << std::left << std::setw(53) << std::setfill('.') << m_name
                    << std::right << std::setw(9) << m_OHIP
                    << std::setfill(' ') << std::setw(5) << m_ticket.number() << " " << m_ticket.time();
            }
            else {
                // For other ostream types, defer to csvWrite
                return csvWrite(ostr);
            }
        }
        else {
            ostr << "Invalid Patient Record" << std::endl;
        }
        return ostr;
    }

    ostream& Patient::csvWrite(std::ostream& ostr) const {
        if (*this) { 
            ostr << type() << ',' << m_name << ',' << m_OHIP << ',';
            m_ticket.write(ostr); 
        }
        else {
            ostr << "Invalid Patient Record"; 
        }
        return ostr;
    }

   istream& Patient::read(istream& istr) {
        if (&istr == &std::cin) {
            char buffer[51];
            cout << "Name: ";
            istr.get(buffer, 51, '\n');
            istr.clear();
            istr.ignore(1000, '\n');

            delete[] m_name;
            m_name = new char[strlen(buffer) + 1];
            strcpy(m_name, buffer);

            cout << "OHIP: ";
            while (true) {
                istr >> m_OHIP;
                if (istr.fail()) {
                    cout << "Bad integer value, try again: ";
                    istr.clear();
                    istr.ignore(50, '\n');
                }
                else if (m_OHIP < 100000000 || m_OHIP > 999999999) {
                    cout << "Invalid value enterd, retry[100000000 <= value <= 999999999]: ";
                    istr.ignore(50, '\n');
                }
                else {
                    istr.ignore(50, '\n');
                    break;
                }
            }
        }
        else {
            // For non-interactive input, use csvRead
            return csvRead(istr);
        }
        return istr;
   }

    istream& Patient::csvRead(std::istream & istr) {
    char tempName[100];

    // Read the name
    istr.get(tempName, 100, ',');
    delete[] m_name;
    m_name = new char[strlen(tempName) + 1];
    strcpy(m_name, tempName);
    istr.ignore(1000, ','); // Skip past the comma

    // Read OHIP
    istr >> m_OHIP;
    if (istr.fail() || m_OHIP < 100000000 || m_OHIP > 999999999) {
        istr.clear();
        m_OHIP = 0;
    }
    istr.ignore(1000, ',');

    m_ticket.read(istr);

    return istr;
}

}
