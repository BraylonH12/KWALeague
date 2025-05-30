#ifndef KWAROUND_HPP
#define KWAROUND_HPP

#include <iostream>
#include "kwaTeam.hpp"

using namespace std;

/*
    Each round should point to 2 teams
    Details for each round shown in text files
    the numbers of round are equal to the vector placement - 1 (ex. Round 1 = roundList[0])
*/
struct Round
{ // I may encounter some struggles when using these pointers in methods
    Team *team1;
    Team *team2;

    Round(): team1(nullptr) , team2(nullptr) {} //default constructor 
};


Round createRound(Team *t1, Team *t2)
{
    Round newRound;

    newRound.team1 = t1;
    newRound.team2 = t2;


    return newRound;
}


//I need a find seed method

#endif

