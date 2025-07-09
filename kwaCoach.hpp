#ifndef KWACOACH_HPP
#define KWACOACH_HPP

#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct Coach
{
    string name;
    double rating;
    int championships;
    //I can make each team point to a coach instead for easier acess
};

Coach buildCoach(string name, double rating)
{
    Coach newCoach;
    newCoach.name = name;
    newCoach.rating = rating;

    return newCoach;
}

#endif
