#ifndef SENECA_MENU_H
#define SENECA_MENU_H
#include <iostream>
#include "Utils.h"

namespace seneca {
    class Menu {
        char* m_text; 
        int m_numOptions;
        int m_tabs;
    public:
        Menu(const char* menuContent, int numberOfTabs = 0);
        ~Menu();
        Menu(const Menu&) = delete; 
        Menu& operator=(const Menu&) = delete; 
        std::ostream& display(std::ostream& ostr = std::cout) const;
        int& operator>>(int& selection); 
    };
}
#endif //SENECA_MENU_H
