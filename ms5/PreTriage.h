#ifndef SENECA_PRETRIAGE_H
#define SENECA_PRETRIAGE_H

#include "Patient.h"
#include "Time.h"

namespace seneca {
    const int MAX_NO_OF_PATIENTS = 100;

    class PreTriage {
        Time m_averCovidWait;
        Time m_averTriageWait;
        Patient* m_lineup[MAX_NO_OF_PATIENTS];
        char* m_dataFilename;
        int m_lineupSize;

        void load();
        void save() const;

        //int getWaitTime(const Patient& p) const;
       void setAverageWaitTime(const Patient& p);
       int indexOfFirstInLine(char type) const;


    public:
        PreTriage(const char* dataFilename);
        ~PreTriage();
        void run();
        //void registerPatient();
        void admitPatient();
        void lineUp() const;
    };
}

#endif // SENECA_PRETRIAGE_H
