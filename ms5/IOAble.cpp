#define _CRT_SECURE_NO_WARNINGS
#include "IOAble.h"

using namespace seneca;
using namespace std;

namespace seneca {
    ostream& operator<<(ostream& ostr, const IOAble& IO) {
        return IO.write(ostr);
    }
    istream& operator>>(istream& istr, IOAble& IO) {
        return IO.read(istr);
    }
}
