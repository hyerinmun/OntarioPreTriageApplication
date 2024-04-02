#ifndef SENECA_IOABLE_H
#define SENECA_IOABLE_H
#include <iostream>

using namespace std;

namespace seneca {
    class IOAble {
    public:
        virtual ostream& write(ostream& ostr) const = 0;
        virtual istream& read(istream& istr) = 0;
        virtual ~IOAble() {};
    };

    ostream& operator<<(ostream& ostr, const IOAble& IO);
    istream& operator>>(std::istream& istr, IOAble& IO);
}

#endif // SENECA_IOABLE_H
