#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
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
            file.ignore();
            file >> m_averTriageWait;
            file.ignore(1000, '\n');

            Patient* patient = nullptr;
            char type = '\0';
            int recordsRead = 0;

            while (file >> type && recordsRead < MAX_NO_OF_PATIENTS) {
                file.ignore();  // Ignore the comma

                if (type == 'C') {
                    patient = new TestPatient();
                }
                else if (type == 'T') {
                    patient = new TriagePatient();
                }

                if (patient != nullptr) {
                    if (patient->csvRead(file)) {
                        m_lineup[m_lineupSize++] = patient;
                        recordsRead++;
                    }
                    else {
                        delete patient;  // If reading failed, clean up
                    }
                    file.ignore(1000, '\n');  // Skip to the end of the line
                }
            }

            if (!file.eof() && recordsRead == MAX_NO_OF_PATIENTS) {
                cout << "Warning: number of records exceeded " << MAX_NO_OF_PATIENTS << endl;
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

        file << m_averCovidWait << ',' << m_averTriageWait << '\n';

        int cntContagion = 0, cntTriage = 0;
        for (int i = 0; i < m_lineupSize; i++) {
            if (m_lineup[i]->type() == 'C') ++cntContagion;
            else if (m_lineup[i]->type() == 'T') ++cntTriage;

            m_lineup[i]->csvWrite(file) << '\n';
        }

        cout << cntContagion << " Contagion Tests and "
            << cntTriage << " Triage records were saved!" << endl;
    }

    PreTriage::PreTriage(const char* dataFilename) : m_averCovidWait(15), m_averTriageWait(5), m_lineupSize(0) {
        m_dataFilename = new char[strlen(dataFilename) + 1];
        strcpy(m_dataFilename, dataFilename);
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
                //registerPatient();
                break;
            case 2:
                //admitPatient();
                break;
            case 3:
                lineUp();
                break;
            }
        } while (selection != 0);
        //cout << "Exiting the program.\n";
    }

    void PreTriage::lineUp() const {
        int selection = 0;
        Menu lineupMenu("Select The Lineup:\n1- Contagion Test\n2- Triage", 3);
        lineupMenu >> selection;

        if (selection == 0) return; 

        char type = selection == 1 ? 'C' : 'T'; 

        cout << "Row - Patient name                                          OHIP     Tk #  Time\n";
        cout << "-------------------------------------------------------------------------------\n";

        bool isEmpty = true; // Track if any patient is printed
        int rowNumber = 0;
        for (int i = 0; i < m_lineupSize; i++) {
            if (*m_lineup[i] == type || selection == 3) { // Check if patient type matches or show all
                cout << left << setw(4) << ++rowNumber << "- ";
                m_lineup[i]->write(clog) << endl; // Delegate to patient's write method
                isEmpty = false;
            }
        }

        if (isEmpty) {
            cout << "The lineup is empty!\n";
        }

        cout << "-------------------------------------------------------------------------------\n";
    }

}