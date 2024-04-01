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

         ostream& write(ostream& ostr) const ;
         istream& read(istream& istr) ;
        ostream& csvWrite(std::ostream& ostr) const ;
        istream& csvRead(istream& istr) ;
   
    };
}

#endif
