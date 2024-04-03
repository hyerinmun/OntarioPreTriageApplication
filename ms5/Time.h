#ifndef SENECA_TIME_H
#define SENECA_TIME_H
#include <iostream>

using namespace std;
namespace seneca {
    class Time {
        unsigned int minutes;
    public:
        Time& reset();
        Time(unsigned int min = 0u);

        ostream& write(ostream& ostr = cout) const;
        istream& read(istream& istr = cin);

        operator unsigned int() const;
        Time& operator*=(int val);
        Time& operator-=(const Time& D);
        Time operator-(const Time& T) const;

        friend ostream& operator<<(ostream& ostr, const Time& time);
        friend istream& operator>>(istream& istr, Time& time);
    };
}

#endif // SENECA_TIME_H