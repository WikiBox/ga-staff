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
#include <math.h>
#include <assert.h>
#include <iostream>
#include <cstdlib>

// To disable the asserts use:
// #define NDEBUG

Ga::Ga(Problem *pr, int ps, int e, double sp, double mf)
{
    popSize = ps;
    newPopSize = ps;
    assert(ps >= 10);
    
    elitism = e;
    assert(e < ps);
    
    problem = pr;
    assert(pr);
    
    selPres = sp;
    assert((sp >= 1.0) && (sp < 10.0));
    
    mutFreq = mf;
    assert((mf >= 0.0) && (mf <= 1.0));
    
    crossovers = 0;

    newPop.clear();
    oldPop.clear();

    while (newPop.size() < popSize)
    {
        Sol temp;
        problem->encode(temp);
        newPop.insert(std::make_pair(problem->evaluate(temp), temp));
    }
}

void Ga::generation(void)
{
    std::swap(oldPop, newPop);
    newPop.clear();

    // Handle elitism - copy over some of the best solutions
    PopIter p = oldPop.begin();
    for (int i = 0; i != elitism; i++)
    {
        newPop.insert(std::make_pair(p->first, p->second));
        p++;
    }

    // Note that actual populationsize sometimes may be one more than requested   
    while (newPop.size() < newPopSize)
    {
        PopIter p = oldPop.begin(),
                q = oldPop.begin();

        int i = popSize * pow(drand(), selPres),
            j = popSize * pow(drand(), selPres);

        assert(i < oldPop.size() && j < oldPop.size());
        
        std::advance(p, i); // Should use some random access container instead?
        std::advance(q, j); // But then I'd have to sort it instead...

        Sol &a = p->second, &b = q->second, c, d;

        problem->crossover(a, b, c, d);
        crossovers += 2;

        if (mutFreq > drand())
        {
            problem->mutate(c);
            problem->mutate(d);
        }
        newPop.insert(std::make_pair(problem->evaluate(c), c));
        newPop.insert(std::make_pair(problem->evaluate(d), d));
    }

    popSize = newPop.size();
}
