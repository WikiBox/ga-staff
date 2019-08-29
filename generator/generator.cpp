
/* 
 * File:   generator.cpp
 * Testfile generator for ga-staff
 * Created on 28 augusti 2019, 12:47
 */

#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    srand(time(NULL));

    int iStaff = 0;

    int iNumSections = 8 + (rand() % 5);

    for (int iSection = 0; iSection < iNumSections; iSection++)
    {
        int iNeeded = 12 + (rand() % 4);
        for (int i = 0; i != iNeeded; i++)
            cout << 5 << " ";

        int iWanted = 4 + (rand() % 2);
        for (int i = 0; i != iWanted; i++)
            cout << 1 << " ";

        int iSurplus = 4 + (rand() % 3);
        for (int i = 0; i != iSurplus; i++)
            cout << -5 << " ";

        cout << endl;

        iStaff += iNeeded + (rand() % 2);
    }

    cout << endl;

    for (int iEmployee = 0; iEmployee < iStaff; iEmployee++)
    {
        for (int iSection = 0; iSection != iNumSections; iSection++)
        {
            if ((rand() % 10) <= 1)
                cout << 4 - (rand() % 8) << " ";
            else
                cout << 0 << " ";
        }
        cout << endl;
    }

    cout << endl;

    return 0;
}