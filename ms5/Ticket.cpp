#include <iostream>
#include "Ticket.h"

using namespace std;

namespace seneca {
   Ticket::Ticket(int number) {
      m_number = number;
   }

   Time Ticket::time() const
   {
      return m_time;
   }

   int Ticket::number() const {
      return m_number;
   }

   void Ticket::resetTime() {
      m_time.reset();
   }

   ostream& Ticket::write(ostream& ostr) const {
      if (&ostr != &cout) {
         ostr << m_number << "," << m_time;
      }
      else {
         ostr << "Ticket No: " << m_number << ", Issued at: " << m_time;
      }
      return  ostr;
   }

   istream& Ticket::read(istream& istr) {
       if (&istr != &cin) { 
           istr >> m_number;
           istr.ignore(1000, ',');
           istr >> m_time;
       }
       return istr;
   }
}
