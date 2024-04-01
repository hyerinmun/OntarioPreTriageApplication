#define _CRT_SECURE_NO_WARNINGS
#include <cstring> 
#include <iostream> 
#include "IOAble.h"

using namespace seneca;

namespace seneca {
    std::ostream& operator<<(std::ostream& ostr, const IOAble& IO) {
        return IO.write(ostr);
    }
    std::istream& operator>>(std::istream& istr, IOAble& IO) {
        return IO.read(istr);
    }
}
