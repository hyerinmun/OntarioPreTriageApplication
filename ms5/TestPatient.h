#ifndef SENECA_TESTPATIENT_H
#define SENECA_TESTPATIENT_H

#include "Patient.h"

namespace seneca {
    class TestPatient : public Patient {
        static int nextTestTicket;

    public:
        TestPatient();
        virtual char type() const;
      
        virtual ostream& write(ostream& ostr) const override;
        virtual istream& read(istream& istr) override;
    };
}

#endif
