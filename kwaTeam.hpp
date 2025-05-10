//Author: Braylon Heavens
//Team object
#ifndef KWATEAM_HPP
#define KWATEAM_HPP

#include <iostream>
#include <string>
#include <vector>
//#include <math>
#include <stdlib.h>
#include <math.h>
#include <random>
#include <chrono>

using namespace std;

struct team
{
    string teamName;
    int wins;
    int loses;
    double winPercent;
    int seed;
    int score; //for every game
    int pTotal; //points total
    //int teamRating (total rank of players / # of players)
    //City

    vector<bool> hasPlayed;
};

team buildTeam (string name)
{
    team newTeam;
    newTeam.teamName = name;
    //newTeam.city = "default"
    newTeam.wins = 0;
    newTeam.loses = 0;
    newTeam.winPercent = 0;
    newTeam.seed = 0;
    newTeam.score = 0;
    newTeam.pTotal = 0;

    return newTeam;
}

#endif