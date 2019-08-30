/*
 * Copyright (C) 2019 Anders Larsen gislagard@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ga.h"
#include "staff.h"

#include <iostream>
#include <cstdlib>
#include <chrono>

int main(int argc, char *argv[])
{
    Staff staff("filename");
    Ga ga(&staff);

    double first = ga.begin()->first;
    double best = first + 1;
    int generation = 0;

    // Default mutation frequency
    const double dDefaultMutFreq = 0.001;
    double dMutFreq = dDefaultMutFreq;

    auto start = std::chrono::steady_clock::now(); // Start timeout timer

    for (;;)
    {
        if (ga.begin()->first > best)
        {
            start = std::chrono::steady_clock::now(); // Reset timeout timer
            dMutFreq = 0.001; // Reset mutation frequency

            best = ga.begin()->first;
            std::cout << "\n\n        ******** GA STAFF stats *********"
                    << "\n Highest score: " << best
                    << "\n Initial score: " << first
                    << "\n    Generation: " << generation
                    << "\n    Crossovers: " << ga.getCrossovers()
                    << "\n   Improvement: " << 100.0 * (best - first) / first << "%";
        }

        int iSecondsLapsed = std::chrono::duration_cast<std::chrono::seconds>
                (std::chrono::steady_clock::now() - start).count();

        if (iSecondsLapsed > 30)
        {
            if (dMutFreq < 0.2) // Max mutation frequency is 20% 
                dMutFreq = dMutFreq + 0.001; // Increase mutation frequency
        }
        else if (iSecondsLapsed > 120)
            break; // Quit program 120 seconds after last improvement

        ga.setMutFreq(dMutFreq);

        ga.generation();

        generation++;
    }

    return EXIT_SUCCESS;
}
