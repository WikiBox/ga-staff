# ga-staff
Genetic algorithm to optimize staff planning

## Problem description
The objective is to create a good or even close to optimal suggestion for a staff plan.

There are a number of positions that need to be filled. 
There are more positions than staff.

Each position is in a section. There is a score set if the position is filled. Positions that MUST be staffed are given a very high score. Positions that may be staffed,but only if there is a surplus staff, are given a negative score. And intermediate positions are given intermediate scores.

Each staff has a preference score for work in each section. It may be based on ability, need or just preference. Sections that are preferred are given a high score. Sections that must be avoided be avoided are ginven a very high negative score.

A solution is optimal if there is no other solution that gives a higher total score.

### Input
One row per section with integer scores for each position in that section. First row, first score is section 1, position 1 and so on.
A blank row.
One row per staff with integer scores for each section. First row, first score is the score for employee 1 working in section 1, and so on.

### Output
One row per section with employees assigned to that section-

## The algorithm

A genetic algorithm will be used to search for good solutions, likely to be (almost) optimal.

## The code

The code is based on an earlier GA with many similarities. This means that a lot of code need not be written. 

See the repository ga-tsp.
