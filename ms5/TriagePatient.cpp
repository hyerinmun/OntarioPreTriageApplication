#include <iostream>
#include <fstream>
#include "TriagePatient.h"
#include "Utils.h"

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

    Patient::read(istr); 

    char tempSymptoms[512];
    if (&istr != &cin) {
        istr.ignore(1000, ',');
        istr.getline(tempSymptoms, 512, '\n');

        U.aloCopy(symptoms, tempSymptoms);
        nextTriageTicket = number() + 1;
    }
    else {
        cout << "Symptoms: ";
        istr.getline(tempSymptoms, 512);
        U.aloCopy(symptoms, tempSymptoms);
    }
    if (istr.fail()) {
        delete[] symptoms;
        symptoms = nullptr;
    }
    return istr;
}
}
