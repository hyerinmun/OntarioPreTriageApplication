#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include <fstream>
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
            Patient::write(ostr); 
            ostr << ',' << (symptoms ? symptoms : ""); 
        }
        return ostr;
    }

    istream& TriagePatient::read(istream& istr) {
   
    delete[] symptoms;
    symptoms = nullptr;

    Patient::read(istr); // Call base class's read function

    char tempSymptoms[512];
    if (&istr != &cin) {
        istr.ignore(1000, ',');
        istr.getline(tempSymptoms, 512, '\n');

        symptoms = new char[strlen(tempSymptoms) + 1];
        strcpy(symptoms, tempSymptoms);

        //if (number() >= nextTriageTicket) {
            nextTriageTicket = number() + 1;
        //}
    }
    else {
        cout << "Symptoms: ";
        istr.getline(tempSymptoms, 512);
        symptoms = new char[strlen(tempSymptoms) + 1];
        strcpy(symptoms, tempSymptoms);
    }
    if (istr.fail()) {
        delete[] symptoms;
        symptoms = nullptr;
    }
    return istr;
}
}
