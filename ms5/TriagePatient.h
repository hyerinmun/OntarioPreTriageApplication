#ifndef SENECA_TRIAGEPATIENT_H
#define SENECA_TRIAGEPATIENT_H
#include "Patient.h"

using namespace std;

namespace seneca {
    class TriagePatient : public Patient {
        static int nextTriageTicket;
        char* symptoms;

    public:
        TriagePatient();
        ~TriagePatient();

        virtual char type() const;

        virtual ostream& write(ostream& ostr) const override;
        virtual istream& read(istream& istr) override;
    };
}

#endif
