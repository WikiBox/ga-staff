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

#ifndef STAFF_H
#define STAFF_H

#include "problem.h"
#include "gautility.h"
#include <string>
#include <vector>

class Staff : public Problem
{
public:
    Staff(const char *filename);
    void encode(Sol &s);
    void mutate(Sol &s);
    void crossover(const Sol &a, const Sol &b, Sol &c, Sol &d);
    double evaluate(Sol &s);
private:

    int iSec, iPos, iEmp;
    std::vector<std::vector<int> > vSec;
    std::vector<std::vector<int> > vEmp;
    std::vector<int> vPos; // The sections laid out flat
    
    std::vector<int> vLookupSection; // Lookup table for position/section

    void intTok(std::vector<int>& v, const std::string& s);
};

#endif
