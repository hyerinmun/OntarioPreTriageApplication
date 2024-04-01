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

    Patient::Patient(const Patient& src): m_name(nullptr), m_OHIP(src.m_OHIP), m_ticket(src.m_ticket), m_fileIO(src.m_fileIO) {
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
            //Writing to console
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
            //Writing to logging stream
            else if (&ostr == &clog) {
                ostr << left << setw(53) << setfill('.') << m_name
                    << right << setw(9) << m_OHIP
                    << setfill(' ') << setw(5) << m_ticket.number() << " " << m_ticket.time();
            }

            //Writing to other streams (like CSV output)
            else {
                ostr << type() << ',' << m_name << ',' << m_OHIP << ',';
                m_ticket.write(ostr); // For CSV format
            }
        }
        else {
            ostr << "Invalid Patient Record" << endl;
        }
        return ostr;
    }

    std::istream& Patient::read(std::istream& istr) {
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
            // File input
            string temp;
            getline(istr, temp, ','); //comma-separated
            if (istr) {
                delete[] m_name;
                m_name = new char[temp.length() + 1];
                strcpy(m_name, temp.c_str());
            }

            istr >> m_OHIP;
            if (istr.fail() || m_OHIP < 100000000 || m_OHIP > 999999999) {
                // Handle invalid OHIP
                istr.clear();
                istr.ignore(1000, ',');
                m_OHIP = 0; // Setting a default invalid value
            }

            istr.ignore(1000, ','); // Skip past the comma after OHIP
            m_ticket.read(istr);
        }
        return istr;
    }

}