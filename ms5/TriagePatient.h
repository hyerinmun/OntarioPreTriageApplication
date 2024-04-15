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
        virtual std::ostream& write(std::ostream& ostr = std::cout) const override;
        virtual std::istream& read(std::istream& istr = std::cin) override;
    };
}
#endif
