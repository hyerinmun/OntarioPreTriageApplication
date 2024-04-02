#include <iomanip> 
#include <iostream> 
#include "Time.h"
#include "Utils.h" 

using namespace seneca;

namespace seneca {
    Time& Time::reset() {
        minutes = U.getTime();
        return *this;
    }

    Time::Time(unsigned int min) : minutes(min) {}

    std::ostream& Time::write(std::ostream& ostr) const {
        ostr << std::setw(2) << std::setfill('0') << minutes / 60 << ":" << std::setw(2) << minutes % 60;
        return ostr;
    }

    std::istream& Time::read(std::istream& istr) {
        int hours, minutes;
        char colon[2];

        if (!(istr >> hours)) {
            istr.setstate(std::ios::failbit);
        }
        else {
            istr.get(colon, 2, '\n');
            if (colon[0] != ':') {
                istr.setstate(std::ios::failbit);
            }
            else {
                if (!(istr >> minutes)) {
                    istr.setstate(std::ios::failbit);
                }
                else {

                    this->minutes = hours * 60 + minutes;
                    return istr;
                }
            }

        }
        return istr;
    }

    Time::operator unsigned int() const {
        return minutes;
    }

    Time& Time::operator*=(int val) {
        minutes *= val;
        return *this;
    }

    Time& Time::operator-=(const Time& D) {
        if (minutes < D.minutes) {
            minutes += 1440;
        }
        minutes -= D.minutes;
        return *this;
    }

    Time Time::operator-(const Time& T) const {
        Time temp;
        if (minutes >= T.minutes) {
            temp.minutes = minutes - T.minutes;
        }
        else {
            temp.minutes = (minutes + 1440) - T.minutes;
        }
        return temp;
    }

    std::ostream& operator<<(std::ostream& ostr, const Time& time) {
        return time.write(ostr);
    }

    std::istream& operator>>(std::istream& istr, Time& time) {
        return time.read(istr);
    }
}
