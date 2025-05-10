//Author: Braylon Heavens
//Player object
#ifndef KWAPLAYER_HPP
#define KWAPLAYER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <math.h>

using namespace std;


struct Player
{
    int points;
    int totalPoints;

    //I can add the overalls to generate a team Rating
    //Choice to create players vs automatically generate them
    
    //Info
    string name;
    string position; //pg, sg, sf, pf, c
    int overall; // 0 - 99 
    int classStatus; //fr, soph, jr, senior
    //If you renew a season after a year,
        //Once a player's classStatus is over 4 they will graduate
        //Team will need a new player
};

Player createPlayer(string name, string position, int overall)
{
    Player newPlayer;
    newPlayer.name = name;
    newPlayer.position = position;
    newPlayer.overall = overall;
    newPlayer.points = 0;
    newPlayer.totalPoints = 0;
    
    return newPlayer;
}

int createOverall(int off, int def )
{

    int overall = 0;

    overall = (off + def) / 2;
    return overall;

}

#endif