#include <iomanip> 
#include <iostream> 
#include "Time.h"
#include "Utils.h" 

using namespace std;
using namespace seneca;

namespace seneca {
    Time& Time::reset() {
        minutes = U.getTime();
        return *this;
    }

    Time::Time(unsigned int min) : minutes(min) {}

    ostream& Time::write(ostream& ostr) const {
        ostr << setw(2) << setfill('0') << minutes / 60 << ":" << setw(2) << minutes % 60;
        ostr.fill(' ');
        return ostr;
    }

    istream& Time::read(istream& istr) {
        int hours, minutes;
        char colon[2];

        if (!(istr >> hours)) {
            istr.setstate(ios::failbit);
        }
        else {
            istr.get(colon, 2, '\n');
            if (colon[0] != ':') {
                istr.setstate(ios::failbit);
            }
            else {
                if (!(istr >> minutes)) {
                    istr.setstate(ios::failbit);
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

    ostream& operator<<(ostream& ostr, const Time& time) {
        return time.write(ostr);
    }

    istream& operator>>(istream& istr, Time& time) {
        return time.read(istr);
    }
}
