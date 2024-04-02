#ifndef SENECA_TICKET_H_
#define SENECA_TICKET_H_
#include <iostream>
#include "Time.h"
#include "IOAble.h"

using namespace std;

namespace seneca {
    class Ticket :public IOAble {
        Time m_time;
        int m_number;
    public:
        Ticket(int number);
        Time time()const;
        int number()const;
        void resetTime();
        ostream& write(ostream& ostr)const;
        istream& read(istream& istr);
    };
}
#endif // !SENECA_TICKET_H_