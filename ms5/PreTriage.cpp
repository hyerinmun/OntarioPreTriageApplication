#include <fstream> 
#include <iomanip>
#include "PreTriage.h"
#include "TestPatient.h"
#include "Patient.h"
#include "TriagePatient.h"
#include "Menu.h"
#include "IOAble.h"

using namespace std;
using namespace seneca;

namespace seneca {

    void PreTriage::load() {
        cout << "Loading data..." << endl;

        ifstream file(m_dataFilename);

        if (file) {
            file >> m_averCovidWait;
            file.ignore(1000, ',');
            file >> m_averTriageWait;
            file.ignore(1000, '\n');

            Patient* patient = nullptr;
            char type = '\0';
            int recordsRead = 0;

            while (file >> type && recordsRead < MAX_NO_OF_PATIENTS) {
                file.ignore(); 

                if (type == 'C') {
                    patient = new TestPatient();
                }
                else if (type == 'T') {
                    patient = new TriagePatient();
                }
                if (patient != nullptr) {
                    if (patient->read(file)) {
                        m_lineup[m_lineupSize++] = patient;
                        recordsRead++;
                    }
                    else {
                        delete patient; 
                    }
                }
            }
            if (!file.eof() && recordsRead == MAX_NO_OF_PATIENTS) {
                cout << "Warning: number of records exceeded " << MAX_NO_OF_PATIENTS << endl;
                cout << recordsRead << " Records imported..." << endl;
            }
            else if (recordsRead == 0) {
                cout << "No data or bad data file!\n";
            }
            else {
                cout << recordsRead << " Records imported..." << endl;
            }
        }
        else {
            cout << "No data or bad data file!\n";
        }
        cout << endl;
    }

    void PreTriage::save() const {
        cout << "Saving lineup..." << endl;
        ofstream file(m_dataFilename);

        file << m_averCovidWait << ',' << m_averTriageWait << endl;

        int cntContagion = 0, cntTriage = 0;
        for (int i = 0; i < m_lineupSize; i++) {
            if (m_lineup[i]->type() == 'C') ++cntContagion;
            else if (m_lineup[i]->type() == 'T') ++cntTriage;

            m_lineup[i]->write(file) << endl;
        }

        cout << cntContagion << " Contagion Tests and "
            << cntTriage << " Triage records were saved!" << endl;
    }

    int PreTriage::getWaitTime(const Patient& p) const {
        int count = 0;
        char type = p.type();

        for (int i = 0; i < m_lineupSize; ++i) {
            if (m_lineup[i]->type() == type) {
                count++;
            }
        }
        int averageWaitTime = (type == 'C' ? m_averCovidWait : m_averTriageWait);
        return count * averageWaitTime;
    }

    void PreTriage::setAverageWaitTime(const Patient& p) {
        Time CT;
        CT.reset();
        Time PTT = p.time();
        int PTN = p.number();
        Time& AWT = (p.type() == 'C' ? m_averCovidWait : m_averTriageWait);

        AWT = ((CT - PTT) + (AWT * (PTN - 1))) / PTN;

        if (p.type() == 'C') {
            m_averCovidWait = AWT;
        }
        else {
            m_averTriageWait = AWT;
        }
    }

    int PreTriage::indexOfFirstInLine(char type) const {
        for (int i = 0; i < m_lineupSize; i++) {
            if (*m_lineup[i] == type) {
                return i;
            }
        }
        return -1;
    }

    PreTriage::PreTriage(const char* dataFilename) : m_averCovidWait(15), m_averTriageWait(5), m_lineupSize(0) {
        m_dataFilename = new char[U.strlen(dataFilename) + 1];
        U.strcpy(m_dataFilename, dataFilename);
        for (int i = 0; i < MAX_NO_OF_PATIENTS; i++) {
            m_lineup[i] = nullptr;
        }
        load();
    }

    PreTriage::~PreTriage() {
        save();
        for (int i = 0; i < m_lineupSize; i++) {
            delete m_lineup[i];
        }
        delete[] m_dataFilename;
    }

    void PreTriage::run() {
        int selection;
        do {
            Menu mainMenu("General Healthcare Facility Pre-Triage Application\n1- Register\n2- Admit\n3- View Lineup");
            mainMenu >> selection;
            switch (selection) {
            case 1:
                registerPatient();
                break;
            case 2:
                admitPatient();
                break;
            case 3:
                lineUp();
                break;
            }
        } while (selection != 0);
    }

    void PreTriage::registerPatient() {
        if (m_lineupSize >= MAX_NO_OF_PATIENTS) {
            cout << "Line up full!" << endl;
            return;
        }

        int selection = 0;
        Menu patientTypeMenu("Select Type of Registration:\n1- Contagion Test\n2- Triage", 3);
        patientTypeMenu >> selection;

        Patient* patient = nullptr;
        switch (selection) {
        case 1:
            patient = new TestPatient();
            break;
        case 2:
            patient = new TriagePatient();
            break;
        default:
            cout << "Invalid selection. Returning to main menu." << endl;
            return;
        }

        patient->setArrivalTime();

        cout << "Please enter patient information: " << endl;
        cin >> *patient;
        cin.clear();

        int waitTimeMinutes = getWaitTime(*patient);
        Time waitTimeFormatted(waitTimeMinutes);

        cout << "\n******************************************" << endl
            << *patient
            << "Estimated Wait Time: " << waitTimeFormatted << endl
            << "******************************************\n\n";

        m_lineup[m_lineupSize++] = patient;
    }

    void PreTriage::admitPatient() {
        int selection = 0;
        char type = '\0';
        Menu admitMenu("Select Type of Admittance:\n1- Contagion Test\n2- Triage", 3);
        admitMenu >> selection;

        switch (selection) {
        case 1: type = 'C'; break;
        case 2: type = 'T'; break;
        default: return;
        }

        int index = indexOfFirstInLine(type);
        if (index == -1) {
            cout << "No patient to admit\n";
            return;
        }

        Time currentTime;
        currentTime.reset();

        cout << "\n******************************************\n";
        cout << "Call time: " << "[" << currentTime << "]";
        cout << "\nCalling at for " << *m_lineup[index];
        cout << "******************************************\n\n";

        setAverageWaitTime(*m_lineup[index]);

        delete m_lineup[index];
        for (int i = index; i < m_lineupSize - 1; ++i) {
            m_lineup[i] = m_lineup[i + 1];
        }
        m_lineup[--m_lineupSize] = nullptr;
    }

    void PreTriage::lineUp() const {
        int selection = 0;
        Menu lineupMenu("Select The Lineup:\n1- Contagion Test\n2- Triage", 3);
        lineupMenu >> selection;

        if (selection == 0) return;

        char type = selection == 1 ? 'C' : 'T';

        cout << "Row - Patient name                                          OHIP     Tk #  Time" << endl;
        cout << "-------------------------------------------------------------------------------" << endl;

        bool isEmpty = true;
        int rowNumber = 0;
        for (int i = 0; i < m_lineupSize; i++) {
            if (*m_lineup[i] == type || selection == 3) {
                clog << left << setw(4) << ++rowNumber << "- " << *m_lineup[i] << endl;
                isEmpty = false;
            }
        }

        if (isEmpty) {
            cout << "The lineup is empty!" << endl;
        }
        cout << "-------------------------------------------------------------------------------" << endl;
    }
}