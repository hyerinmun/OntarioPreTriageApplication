#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include "TriagePatient.h"

using namespace std;

namespace seneca {
    int TriagePatient::nextTriageTicket = 1;

    TriagePatient::TriagePatient() : Patient(nextTriageTicket), symptoms(nullptr) {
        nextTriageTicket++;
    }

    TriagePatient::~TriagePatient() {
        delete[] symptoms;
    }

    char TriagePatient::type() const {
        return 'T';
    }

    ostream& TriagePatient::write(ostream& ostr) const {
        if (&ostr == &cout) {
            ostr << "TRIAGE\n";
            Patient::write(ostr);
            ostr << "Symptoms: " << (symptoms ? symptoms : "") << endl;
        }
        else if (&ostr == &clog) {
            Patient::write(ostr);
        }
        else {
            Patient::write(ostr) << ',' << (symptoms ? symptoms : "");
        }
        return ostr;
    }
    ostream& TriagePatient::csvWrite(ostream& ostr) const {
        Patient::csvWrite(ostr); 
        ostr << ',' << (symptoms ? symptoms : ""); 
        return ostr;
    }
    istream& TriagePatient::read(istream& istr) {
        if (&istr == &cin) {
            Patient::read(istr); 

            cout << "Symptoms: ";
            delete[] symptoms;
            symptoms = nullptr;

            char tempSymptoms[100];
            istr.getline(tempSymptoms, 100);
            symptoms = new char[strlen(tempSymptoms) + 1];
            strcpy(symptoms, tempSymptoms);
        }
        else {
         
            Patient::read(istr); 
            istr.ignore(1000, ',');

            delete[] symptoms;
            symptoms = nullptr;

            char tempSymptoms[100];
            istr.getline(tempSymptoms, 100);
            symptoms = new char[strlen(tempSymptoms) + 1];
            strcpy(symptoms, tempSymptoms);
        }

        if (this->number() >= nextTriageTicket) {
            nextTriageTicket = this->number() + 1;
        }
        return istr;
    }

    istream& TriagePatient::csvRead(istream& istr) {
        char buffer[511];
        Patient::csvRead(istr); 
        istr.ignore(1000, ','); 
        istr.getline(buffer, 511);
        delete[] symptoms; 
        symptoms = new char[strlen(buffer) + 1];
        strcpy(symptoms, buffer);
        return istr;
    }
}
