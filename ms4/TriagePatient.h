#ifndef SENECA_TRIAGEPATIENT_H
#define SENECA_TRIAGEPATIENT_H
#include "Patient.h"

namespace seneca {
    class TriagePatient : public Patient {
        static int nextTriageTicket;
        char* symptoms;

    public:
        TriagePatient();
        ~TriagePatient();

        virtual char type() const;

        virtual ostream& write(ostream& ostr) const;
        virtual istream& read(istream& istr);
    };
}

#endif
