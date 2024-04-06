#ifndef SENECA_TICKET_H_
#define SENECA_TICKET_H_
#include <iostream>
#include "Time.h"
#include "IOAble.h"

namespace seneca {
    class Ticket :public IOAble {
        Time m_time;
        int m_number;
    public:
        Ticket(int number);
        Time time()const;
        int number()const;
        void resetTime();
        std::ostream& write(std::ostream& ostr = std::cout)const;
        std::istream& read(std::istream& istr = std::cin);
    };
}
#endif // !SENECA_TICKET_H_
