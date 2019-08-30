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

#ifndef GA_H
#define GA_H

#include "staff.h"
#include <utility>
#include <vector>
#include <map>

typedef std::map<double, Sol> Pop;
typedef std::map<double, Sol>::iterator PopIter;

/* For multimap use:
typedef std::multimap<double, Sol> Pop;
typedef std::multimap<double, Sol>::iterator PopIter;
 */

class Ga
{
    Pop oldPop;
    Pop newPop;
    Problem *problem;
    double selPres, mutFreq;
    int popSize;
    int newPopSize;
    int elitism;
    unsigned long crossovers;

public:

    // Create a population, based on some problem type
    Ga(Problem *pr, int ps = 500, int e = 5, double sp = 1.3, double mf = 0.01);

    // Evolve the next generation
    void generation(void);

    // Change the selection pressure
    void setSelPres(double p)
    {
        selPres = p;
    };

    // Change the mutation frequency

    void setMutFreq(double f)
    {
        mutFreq = f;
    };

    // Change level ov elitism (number of the best solutions to move to next)

    void setElitism(int e)
    {
        elitism = e;
    };

    // Change the population size

    void setPopSize(int p)
    {
        newPopSize = p;
    };

    // Iterator to the first solution in the population

    PopIter begin(void)
    {
        return newPop.begin();
    };

    // Iterator to the last + 1 solution in the population

    PopIter end(void)
    {
        return newPop.end();
    };

    // Get the current populationsize

    int size(void)
    {
        return newPop.size();
    };

    // Get a count of crossovers done so far

    unsigned long getCrossovers(void)
    {
        return crossovers;
    };
};

#endif
