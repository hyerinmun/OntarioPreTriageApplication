#ifndef SENECA_TIME_H
#define SENECA_TIME_H
#include <iostream>

namespace seneca {
    class Time {
        unsigned int minutes;
    public:
        Time& reset();
        Time(unsigned int min = 0u);

        std::ostream& write(std::ostream& ostr = std::cout) const;
        std::istream& read(std::istream& istr = std::cin);

        operator unsigned int() const;
        Time& operator*=(int val);
        Time& operator-=(const Time& D);
        Time operator-(const Time& T) const;

        friend std::ostream& operator<<(std::ostream& ostr, const Time& time);
        friend std::istream& operator>>(std::istream& istr, Time& time);
    };
}

#endif // SENECA_TIME_H