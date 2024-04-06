#ifndef SENECA_PATIENT_H
#define SENECA_PATIENT_H
#include "IOAble.h"
#include "Ticket.h"

namespace seneca {
    class Patient : public IOAble {
        char* m_name;
        int m_OHIP; 
        Ticket m_ticket;
        bool m_fileIO;

    public:
        Patient(int ticketNumber = 0, bool fileIO = false); 
        Patient(const Patient& src);
        Patient& operator=(const Patient& src);  
        virtual ~Patient(); 
      
        virtual char type() const = 0;

        bool operator==(char c) const;
        bool operator==(const Patient& other) const;

        void setArrivalTime();
        Time time() const;
        int number() const;

        operator bool() const;
        operator const char* () const;

        virtual std::ostream& write(std::ostream& ostr = std::cout) const;
        virtual std::istream& read(std::istream& istr = std::cin);
    };
}
#endif // SDDS_PATIENT_H
