#include "TestPatient.h"

using namespace std;
namespace seneca {
    int TestPatient::nextTestTicket = 1;

    TestPatient::TestPatient() : Patient(nextTestTicket) {
        nextTestTicket++;
    }

    char TestPatient::type() const {
        return 'C';
    }

    ostream& TestPatient::write(ostream& ostr) const {
        if (&ostr == &cout) {
            ostr << "Contagion TEST\n";
        }
        Patient::write(ostr); 
        return ostr;
    }

    istream& TestPatient::read(istream& istr) {
        Patient::read(istr);
        if (&istr != &cin) {
            nextTestTicket = number() + 1;
        }
        return istr;
    }
}
