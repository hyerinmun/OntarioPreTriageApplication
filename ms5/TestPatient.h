#ifndef SENECA_TESTPATIENT_H
#define SENECA_TESTPATIENT_H

#include "Patient.h"

namespace seneca {
    class TestPatient : public Patient {
        static int nextTestTicket;

    public:
        TestPatient();
        virtual char type() const;
      
        virtual std::ostream& write(std::ostream& ostr = std::cout) const override;
        virtual std::istream& read(std::istream& istr = std::cin) override;
    };
}

#endif
