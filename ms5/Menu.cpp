#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include "Menu.h"

using namespace std;
using namespace seneca;

namespace seneca {
    Menu::Menu(const char* menuContent, int numberOfTabs) :m_tabs(numberOfTabs) {
        if (menuContent != nullptr) {
            m_text = new char[U.strlen(menuContent) + 1];
            U.strcpy(m_text, menuContent);
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

    ostream& Menu::display(ostream& ostr) const {
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

            ostr << endl;
            if (m_tabs > 0) {
                for (int i = 0; i < m_tabs; i++) {
                    ostr << ' ';
                }
            }
            ostr << "0- Exit" << endl;
            for (int i = 0; i < m_tabs; i++) {
                ostr << ' ';
            }
            ostr << "> ";
        }
        return ostr;
    }


    int& Menu::operator>>(int& selection) {
        display();
        selection = U.getInt(0, m_numOptions);

        return selection;
    }
}