#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <math.h>

using namespace std;

//Do I need to make this a class?
struct Player
{
    int points;
    int totalPoints;

    //I can add the overalls to generate a team Rating
    //Choice to create players vs automatically generate them
    
    //Info
    string name;
    string position; //pg, sg, sf, pf, c
    int overAll; // 0 - 99 
    int classStatus; //fr, soph, jr, senior
    //If you renew a season after a year,
        //Once a player's classStatus is over 4 they will graduate
        //Team will need a new player
};

Player createPlayer(string name, string position, string)
{
    Player newPlayer;
    newPlayer.name = name;
    newPlayer.position = position;
    newPlayer.points = 0;
    newPlayer.totalPoints = 0;


    return newPlayer;


}

//Each team has 5 players
Player MVP(vector<int> teams)
{
    int test = 0;
    for (int i = 0; i < teams.size(); i++)
    {
        test++;
        //Loop through every player of each team to find player with most points
            //If tie check overall
                //If tie check teams record
    }
}

int createOverall(int off, int def )
{

    int overall = 0;

    overall = (off + def) / 2;
    return overall;

}

//Notes 
// I could make the overall its own unique variable
    // It takes a defensive rating, offensive rating, and other ratings to measure an overall (0 - 99)
// I want to get to the point where I can create a method than generates an individual players stats each game
// Also creating a team overall
int main()
{

}