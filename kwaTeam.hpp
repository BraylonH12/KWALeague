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

#include "kwaCoach.hpp"

using namespace std;

struct Team
{
    //General Info
    string teamName;
    int wins;
    int loses;
    double winPercent;
    int seed;
    int score; //for every game
    int pTotal; //points total
    int pAgainst;
    int championships;

    //Team specific Info
    string location;
    double education;
    double coachRating;
    double campusLife;
    double prestige;
    double funds; //Out of (100,000)

    //Coach pointer
    Coach* coach;

    //Ratins

    //int teamRating (total rank of players / # of players)
    //City

    vector<bool> hasPlayed;
};

Team buildTeam (string name)
{
    Team newTeam;
    newTeam.teamName = name;
    //newTeam.city = "default"
    newTeam.wins = 0;
    newTeam.loses = 0;
    newTeam.winPercent = 0;
    newTeam.seed = 0;
    newTeam.score = 0;
    newTeam.pTotal = 0;
    newTeam.pAgainst = 0;
    newTeam.championships = 0;

    newTeam.location = "default";
    newTeam.education = 3;
    newTeam.campusLife = 3;
    newTeam.prestige = 1;

    //I have to figure out how to set a coach, and a default rating system for coaches
    return newTeam;
}

Team buildTeam (string name, string cityName, double pRating, double eRating, Coach *currentCoach, double clRating) //I will most likely change the coach rating
{
    Team newTeam;
    newTeam.teamName = name;
    //newTeam.city = "default"
    newTeam.wins = 0;
    newTeam.loses = 0;
    newTeam.winPercent = 0;
    newTeam.seed = 0;
    newTeam.score = 0;
    newTeam.pTotal = 0;
    newTeam.pAgainst = 0;
    newTeam.championships = 0;

    newTeam.location = cityName;
    newTeam.prestige = pRating;
    newTeam.education = eRating;
    newTeam.campusLife = clRating;

    newTeam.coach = currentCoach;

    //I have to figure out how to set a coach, and a default rating system for coaches
    return newTeam;
}

#endif
