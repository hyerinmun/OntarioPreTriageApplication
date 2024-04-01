#ifndef SENECA_TESTPATIENT_H
#define SENECA_TESTPATIENT_H

#include "Patient.h"

namespace seneca {
    class TestPatient : public Patient {
        static int nextTestTicket;

    public:
        TestPatient();
        virtual char type() const;
        ostream& csvWrite(ostream& ostr) const;
        istream& csvRead(istream& istr);
        ostream& write(ostream& ostr) const ;
        istream& read(istream& istr) ;
    };
}

#endif
