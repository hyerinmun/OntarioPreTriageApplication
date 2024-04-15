/***********************************************************************
// OOP244 Project 
//
// File  Utils.h
// Author  Fardad Soleimanloo
// Description
//
// Revision History
// -----------------------------------------------------------
// Name                 Date            Reason
***********************************************************************/
#ifndef SENECA_UTILS_H_
#define SENECA_UTILS_H_
#include <iostream>
namespace seneca {
   class Utils {
      /// <summary>
      /// Start point for the simulated time
      /// Set to 8 AM
      /// </summary>
      unsigned int m_testMins = 480;
      /// <summary>
      /// index for the time addition intervals ({ 3,5,9,20,30 });
      /// </summary>
      unsigned int m_testIndex = 0;
   public:
      /// <summary>
      /// Set the debug global variable to true and sets the m_testMins attribute to 
      ///  hour x 60 + min. This value will be the intial starting time for debugging
      ///  and testing. 
      /// </summary>
      /// <param name="hour">hours</param>
      /// <param name="min">minutes</param>
      void setDebugTime(int hour, int min);
      /// <summary>
      /// If not in debugging mode, returns the current minute value of the system hour
      ///  and minute. If debugging is active it will first return the value of m_testMins 
      ///  then adds the following values in these intervals (3,5,9,20,30) to simulate passage
      ///  of time. 
      /// </summary>
      /// <returns>the current time in minutes</returns>
      int getTime(); // returns the time of day in minutes

      /// <summary>
      /// compares s1 to s2
      /// </summary>
      /// <param name="s1">Cstring</param>
      /// <param name="s2">Cstring</param>
      /// <returns> &gt;0 if s1 &gt; s2  OR  &lt;0 if s1 &lt; s2 OR 0 if s1 = s2</returns>
      int strcmp(const char* s1, const char* s2)const;

      /// <summary>
      /// get and foolproof int printing "Bad integer value, try again: " for error message. 
      /// </summary>
      /// <returns>integer entered from console</returns>
      int getInt()const;

      /// <summary>
      /// uses int getint()const to get an int and if it is not between the min and max values it will print <br />"Invalid value enterd, retry[100000000 <= value <= 999999999]: "
      /// </summary>
      /// <param name="min">minimum acceptable value</param>
      /// <param name="max">maximum acceptable value</param>
      /// <returns></returns>
      int getInt(int min, int max)const;

      size_t strlen(const char* str);

      /// <summary>
      /// Copies the string pointed to by src, including the terminating null byte ('\0'), 
      /// to the buffer pointed to by des. The strings may not overlap, and the destination string des 
      /// must be large enough to receive the copy. 
      /// </summary>
      /// <param name="des">Pointer to the destination array where the content is to be copied.</param>
      /// <param name="src">The string to be copied.</param>
      /// <returns>Returns a pointer to the destination string des.</returns>
      char* strcpy(char* des, const char* src);

       /// <summary>
       /// Copies up to len characters from the string pointed to by src to des. If the length of src is less than len, 
       /// the remainder of des will be padded with null bytes. If len is greater than the length of src, the copy stops 
       /// once the end of the string is reached (the null terminator is also copied). The destination string must have 
       /// enough space to receive the copy. This function is designed to be safer than strcpy by limiting the number of 
       /// bytes copied to prevent buffer overflow.
       /// </summary>
       /// <param name="des">Pointer to the destination array where the content is to be copied.</param>
       /// <param name="src">The string to be copied.</param>
       /// <param name="len">The maximum number of characters to copy from src.</param>
       /// <returns>Returns a pointer to the destination string des.</returns>
      char* strcpy(char* des, const char* src, size_t len);

       /// <summary>
       /// Allocates memory for and copies a string to a new location in memory, pointed to by des. This function first 
       /// deallocates any memory previously referenced by des using delete[], setting des to nullptr to ensure it does 
       /// not become a dangling pointer. It then checks if src is not null; if so, it allocates enough memory to hold 
       /// the src string, including the terminating null byte, and copies the string into this new memory location.
       /// </summary>
       /// <param name="des">Reference to a pointer to the destination array where the content is to be copied. Previous memory 
       /// is safely deleted and new memory allocated for the copy.</param>
       /// <param name="src">Pointer to the source string to be copied. If null, des is set to nullptr.</param>
      void aloCopy(char*& des, const char* src);

       /// <summary>
       /// Allocates memory for and copies up to maxLen characters of a string to a new memory location, pointed to by des. 
       /// The function first frees any memory previously pointed to by des using delete[], then sets des to nullptr to prevent 
       /// it from becoming a dangling pointer. If src is not null, it calculates the length of src and allocates enough memory 
       /// for the lesser of len and maxLen characters plus a null terminator. It then copies the string, up to maxLen characters, 
       /// into this new memory location.
       /// </summary>
       /// <param name="des">Reference to a pointer to the destination array where the content is to be copied. Old memory is 
       /// safely deleted, and new memory is allocated for the copy.</param>
       /// <param name="src">Pointer to the source string to be copied. If null, des is set to nullptr.</param>
       /// <param name="maxLen">The maximum number of characters to copy from the source string, not including the null terminator.</param>
      void aloCopy(char*& des, const char* src, size_t maxLen);

       /// <summary>
       /// Reads a line of text from standard input (stdin) into a provided buffer up to a specified length, handling input overflow. 
       /// This function uses cin.getline to read up to len characters into the buffer pointed to by str, including the terminating 
       /// null byte ('\0'). If the input exceeds len characters, causing cin to enter a fail state, the function informs the user 
       /// of the maximum character limit, clears the fail state with cin.clear(), ignores the excess characters up to a newline 
       /// character or a large arbitrary limit (12000 characters), and prompts the user to enter the input again. This process 
       /// repeats until the input is within the allowed length, ensuring robust handling of user input exceeding the buffer size.
       /// </summary>
       /// <param name="str">Pointer to the character array (buffer) where the input is to be stored.</param>
       /// <param name="len">Maximum number of characters to read into the buffer, excluding the null terminator.</param>
      void getCstr(char* str, size_t len);

      bool getDynCstr(char*& str, std::istream& istr, char delimiter);

      template <typename type>
      void removeDynamicElement(type* array[], int index, int& size) {
          delete array[index];
          for (int j = index; j < size; j++) {
              array[j] = array[j + 1];
          }
          size--;
      }
   };
   /// <summary>
      /// making seneca::debug variable global to all the files
      /// which include "Utils.h"
      /// </summary>
   extern bool debug;
   /// <summary>
   /// making seneca::U "Utils" object global to all the files which include "Utils.h"
   /// </summary>
   extern Utils U;

}
#endif // !SENECA_UTILS_H_

