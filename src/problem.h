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

// This file contains a base class for some problem to solve using the GA.
// A problem must define how to encode, mutate, crossover and evaluate
// solutions. Solutions are stored as vectors of ints.

#ifndef PROBLEM_H
#define PROBLEM_H

#include <vector>

// A Solution is a vector of ints
typedef std::vector<int> Sol;
typedef std::vector<int>::iterator SolIter;

// Genetic operations depend on the problem type

class Problem
{
private:
public:
    // Generate a random valid solution &s
    virtual void encode(Sol &s) = 0;

    // Mutate the soultion &s
    virtual void mutate(Sol &s) = 0;

    // Use old genes in a and b to create new in c and d
    virtual void crossover(const Sol &a, const Sol &b, Sol &c, Sol &d) = 0;

    // Calculate cost for solution &s
    virtual double evaluate(Sol &s) = 0;
};
//---------------------------------------------------------------------------

#endif
