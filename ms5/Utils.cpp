/***********************************************************************
// OOP244 Project
//
// File  Utils.cpp
// Author  Fardad Soleimanloo
// Description
//
// Revision History
// -----------------------------------------------------------
// Name                 Date            Reason
***********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Utils.h"
#include "Time.h"
using namespace std;
namespace seneca {
    
   bool debug = false;
   Utils U;
   int Utils::getTime() {
      int mins = -1;
      if (debug) {
         int duration[]{ 3,5,9,20,30 };
         mins = (m_testMins %= 1440);
         m_testMins += duration[m_testIndex++ % 5];
      }
      else {
         time_t t = time(NULL);
         tm lt = *localtime(&t);
         mins = lt.tm_hour * 60 + lt.tm_min;
      }
      return mins;
   }
   void Utils::setDebugTime(int hour, int min) {
      seneca::debug = true;
      m_testMins = hour * 60 + min;
   }

   int Utils::strcmp(const char* s1, const char* s2)const {
      int i;
      for (i = 0; s1[i] && s2[i] && s1[i] == s2[i]; i++);
      return s1[i] - s2[i];
   }
   int Utils::getInt() const
   {
        int val{};
        cin >> val;
        while (cin.fail()) {
            cout << "Bad integer value, try again: ";
            cin.clear();
            cin.ignore(50, '\n');
            cin >> val;
        }
        cin.ignore(50, '\n');
        return val;
   }
   int Utils::getInt(int min, int max) const
   {
       int val = getInt();
       while ((val < min || val > max)) {
           cout << "Invalid value entered, retry[" << min << " <= value <= " << max << "]: ";
           cin >> val;
           cin.ignore(50, '\n'); 
       }
       return val;
   }

   size_t Utils::strlen(const char* str) {
       size_t len{};
       while (str[len]) {
           len++;
       }
       return len;
   }
   char* Utils::strcpy(char* des, const char* src) {
       int i;
       for (i = 0; src[i]; i++) {
           des[i] = src[i];
       }
       des[i] = 0;
       return des;
   }

    char* Utils::strcpy(char* des, const char* src, size_t len) {
        size_t i;
        for (i = 0; src[i] && i < len; i++) {
            des[i] = src[i];
        }
        des[i] = 0;
        return des;
    }

   void Utils::aloCopy(char*& des, const char* src) {
       delete[] des;
       des = nullptr;
       if (src) {
           des = new char[U.strlen(src) + 1];
           U.strcpy(des, src);
       }
   }

   void Utils::aloCopy(char*& des, const char* src, size_t maxLen) {
       delete[] des;
       des = nullptr;
       if (src) {
           size_t len = U.strlen(src);
           des = new char[(len < maxLen ? len : maxLen) + 1];
           U.strcpy(des, src, maxLen);
       }
   }

   void Utils::getCstr(char* str, size_t len) {
       cin.getline(str, len + 1);
       while (cin.fail()) {
           cout << "Maximum " << len << " chars!, retry\n> ";
           cin.clear();
           cin.ignore(12000, '\n');
           cin.getline(str, len + 1);
       }
   }

   bool Utils::getDynCstr(char*& str, istream& istr, char delimiter) {
       delete[] str;
       str = nullptr;
       char buf[1000];
       istr.getline(buf, 1000, delimiter);
       if (istr) {
           str = new char[this->strlen(buf) + 1];
           this->strcpy(str, buf);
       }
       else {
           istr.clear();
           istr.ignore(1000, '\n');
       }
       return bool(str);
   }
   // end provided code
}