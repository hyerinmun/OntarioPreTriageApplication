#ifndef SENECA_PATIENT_H
#define SENECA_PATIENT_H

#include "IOAble.h"
#include "Ticket.h"

using namespace std;
namespace seneca {

    //inherits from the IOAble interface
    //Attributes and behaviours of a generic patient 
    //ms4 it will serve as a base class for two derived classes: TestPatient and Triage Patient
    class Patient : public IOAble {
        char* m_name; //dynamically allocated C_string char ptr var
        int m_OHIP; //exactly 9 digits
        Ticket m_ticket;
        bool m_fileIO;

    public:
        Patient(int ticketNumber = 0, bool fileIO = false); //constructor
        Patient(const Patient& src);//cpying
        Patient& operator=(const Patient& src);  //assignment
        virtual ~Patient(); //destructor

        //pure virtual function = 0       
        virtual char type() const = 0;

        //Patient Comparison to a Character
        bool operator==(char c) const;
        //Comparing to Another Patient
        bool operator==(const Patient& other) const;

        void setArrivalTime();
        Time time() const;
        int number() const;

        explicit operator bool() const;
        //If a patient is casted to a constant character pointer, return the address of the patient's name
        operator const char* () const;

        virtual ostream& write(ostream& ostr) const;

        virtual istream& read(istream& istr);
    };

}

#endif // SDDS_PATIENT_H
