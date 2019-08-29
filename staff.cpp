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

#include "staff.h"
#include <assert.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cctype>

// Integer Tokenizor. Put ints from string into vector
void Staff::intTok(std::vector<int>& v, const std::string& s)
{
    std::string sInteger = "";
    char cPrev = ' ';

    for (auto& c : s)
    {
        if (isdigit(c))
        {
            // Accept a minus sign from previous pass
            if (cPrev == '-')
                sInteger = "-";

            sInteger += c;
        }
        else if (sInteger.length())
        {
            // Convert to int and put in vector
            v.push_back(std::stoi(sInteger));
            sInteger = "";
        }

        cPrev = c;
    }
    
    // Handle residual terminating integer
    if (sInteger.length())
        v.push_back(std::stoi(sInteger));
}

Staff::Staff(const char *filename)
{
    std::ifstream in(filename);
    std::string line;
    std::vector<int> vInteger;
    iPos = iEmp = iSec = 0;

    // Read in sections
    do
    {
        std::getline(in, line);
        intTok(vInteger, line);
        if (vInteger.size())
        {
            iPos += vInteger.size();
            vSec.push_back(vInteger);
            iSec++;
        }
    }
    while (vInteger.size());

    // Read in employees
    do
    {
        std::getline(in, line);
        intTok(vInteger, line);
        if (vInteger.size())
        {
            assert(vInteger.size() == vSec.size());
            vEmp.push_back(vInteger);
            iEmp++;
        }
    }
    while (vInteger.size());

    // Sanity check
    assert(iEmp < iPos);

    for (auto& vPos : vSec)
    {
        for (auto& iPos : vPos)  // local iPos!
        {
            vPos.push_back(iPos);
            vLookupSection.push_back(iSec);
        }
        iSec++;
    }
}

void Staff::encode(Sol &s)
{
    s.resize(iPos);
    for (int i = 0; i != iEmp; i++)
        s[i] = i;

    for (int i = iEmp; i != iPos; i++)
        s[i] = -1; // Not assigned

    std::random_shuffle(s.begin(), s.end());
}

void Staff::mutate(Sol &s)
{
    // Do a random three position rotation
    int iSize = s.size();
    int tmp, i0 = irand(iSize), i1 = irand(iSize), i2 = irand(iSize);

    tmp = s[i0];
    s[i0] = s[i1];
    s[i1] = s[i2];
    s[i2] = tmp;
}

// For highly optimized PMX use:
#define PMX_lookup 1
#ifdef PMX_lookup

void Staff::crossover(const Sol &a, const Sol &b, Sol &c, Sol &d)
{
    assert(a.size() == b.size());

    const int n = a.size();

    // static to avoid realloc every call
    static std::vector<int> lookup_c;
    static std::vector<int> lookup_d;

    lookup_c.resize(n);
    lookup_d.resize(n);
    c.resize(n);
    d.resize(n);

    // Create lookup tables and initialize c and d
    for (int i = 0; i != n; i++)
    {
        c[i] = a[i];
        lookup_c[c[i]] = i;

        d[i] = b[i];
        lookup_d[d[i]] = i;
    }

    // Crossover random sequence of at least n / 4 and at most 3/4 * n cities
    const int start = irand(n);
    const int end = start + (n / 4) + irand(n / 2);

    // Do the PMX
    for (int i = start; i != end; i++)
    {
        const int j = i % n; // i mod n

        const int posb = lookup_c[b[j]];
        std::swap(c[posb], c[j]);
        lookup_c[c[posb]] = posb;

        const int posa = lookup_d[a[j]];
        std::swap(d[posa], d[j]);
        lookup_d[d[posa]] = posa;
    }
}

#else // No optimized PMX - provided for testing and comparision

void Staff::crossover(const Sol &a, const Sol &b, Sol &c, Sol &d)
{
    assert(a.size() == b.size());

    c = a;
    d = b;

    const int n = a.size();
    assert(n = 10);
    // Crossover random sequence of at least n / 4 and at most 3/4 * n cities
    const int start = irand(n);
    const int end = start + (n / 4) + irand(n / 2);

    // PMX
    for (int i = start; i != end; i++)
    {
        int j = i % n; // i mod n
        std::swap(c[j], *(find(c.begin(), c.end(), b[j])));
        std::swap(d[j], *(find(d.begin(), d.end(), a[j])));
    }
}

#endif

double Staff::evaluate(Sol &s)
{
    int len = s.size();
    int score;

    for (int iPos = 0; iPos != len; iPos++)
    {
        if (s[iPos] != -1)
            score += vPos[iPos] + vEmp[s[iPos]][vLookupSection[iPos]];
    }
    double sum = 0;

    return sum;
}
