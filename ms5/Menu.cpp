#define _CRT_SECURE_NO_WARNINGS
#include <cstring> 
#include <iostream> 
#include "Menu.h"

using namespace seneca;

namespace seneca {
    Menu::Menu(const char* menuContent, int numberOfTabs):m_tabs(numberOfTabs){
        if (menuContent != nullptr) {
            m_text = new char[strlen(menuContent) + 1];
            strcpy(m_text, menuContent);

        }
        else {
            m_text = nullptr;
        }
        m_numOptions = 0;
            for (const char* p = menuContent; *p; p++) {
               m_numOptions += (*p == '\n');
            }
        }
    

    Menu::~Menu() {
        delete[] m_text;
    }

    std::ostream& Menu::display(std::ostream& ostr) const {
        if (m_text != nullptr) {
            const char* p = m_text;
            bool isNewLine = true;

            while (*p) {
                if (isNewLine && m_tabs > 0) {
                    for (int i = 0; i < m_tabs; i++) {
                        ostr << ' '; 
                    }
                    isNewLine = false;
                }

                if (*p == '\n') {
                    isNewLine = true;
                }

                ostr << *p;
                p++;
            }

            ostr << std::endl;
            if (m_tabs > 0) {
                for (int i = 0; i < m_tabs; i++) {
                    ostr << ' '; 
                }
            }
            ostr << "0- Exit" << std::endl;
            for (int i = 0; i < m_tabs; i++) {
                ostr << ' '; 
            }
            ostr << "> ";
        }
        return ostr;
    }


    int& Menu::operator>>(int& selection) {
        display();
        while (true) { 
            std::cin >> selection;
            if (std::cin.fail()) {
                std::cin.clear(); 
                std::cin.ignore(1000, '\n'); 
                std::cout << "Bad integer value, try again: ";
            }
            else if (selection < 0 || selection > m_numOptions) {
                std::cout << "Invalid value enterd, retry[0 <= value <= " << m_numOptions << "]: ";
                std::cin.ignore(1000, '\n');
            }
            else {

                char nextChar = std::cin.get();
                if (nextChar != '\n') {
                    std::cout << "Only enter an integer, try again: ";
                    std::cin.ignore(1000, '\n');
                }
                else {
                    break; 
                }
            }
        }
        return selection;
    }
}
