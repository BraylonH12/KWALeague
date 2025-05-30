#include "kwaTeam.hpp"
#include "kwaPlayer.hpp"
#include "kwaRound.hpp"

//Normal Include Statements
    #include <iostream>
    #include <string>
    #include <vector>
    //#include <math>
    #include <stdlib.h>
    #include <math.h>
    #include <random>
    #include <chrono>

    using namespace std;

void editTeam (vector<Team> &list, string name)
{
    string answer;
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i].teamName == name)
        {
            cout << "Team found" << endl;
            while (1)
            {
                cout << "Would you like to delete or edit? (type 'cancel' to exit)" << list[i].teamName << endl;
                cin >> answer;
                if (answer == "edit")
                {
                    while (true)
                    {
                        cout << "What would you like to change?" << endl;
                        cout << "(teamName/other)" << endl;
                        cin >> answer;
                        if (answer == "teamName")
                        {
                            cout << "What would you like the team name to be?" << endl;
                            cin >> answer;
                            list[i].teamName = answer;
                            cout << "Team name changed to " << list[i].teamName << endl;
                            return;
                        }
                        else if (answer == "other")
                        {
                            cout << "Still coding" << endl;
                            break;
                        }
                        else if (answer == "exit")
                        {
                            return;
                        }
                        
                        else
                        {
                            cout << "Invalid input, please try again" << endl;
                            continue;
                        }
                    }
                }
                else if (answer == "delete")
                {
                    cout << "Deleting " << list[i].teamName << endl;
                    list.erase(list.begin() + i);
                    break;
                }
                else
                {
                    cout << "Incorrect input" << endl;
                    continue;
                }
            }
        }
    }
}

void setMaxRank(vector<Team> &list, int size)
{
    for (int i = 0; i < list.size(); i++)
    {
        list[i].seed = size;
    }
}

void setMatchupsFalse(vector<Team> &list)
{
    int it = 0;
    while (it < list.size())
    {
        for (int i = 0; i < list.size(); i++)
        {
            if (i != it) //A team can't play itself
            {
                if (list[it].hasPlayed.size() == 0) //First instance of call
                {
                    list[it].hasPlayed.push_back(false);
                }
                else 
                {
                    list[it].hasPlayed[i] = false;
                }
            }
            else
            {
                if (list[it].hasPlayed.size() == 0)
                {
                    list[it].hasPlayed.push_back(true);
                }
                else 
                {
                    list[it].hasPlayed[i] = true;
                }
            }
        }
        it++;
    }
}

void calculateWinP(vector<Team> &list) //I could modify this to inlcude all teams instead of just one (Yessir you got it!)
{ 
    //win percentage = wins / total games
    
    int totalGames = list[0].wins + list[0].loses; //Any team could be used for reference

    //Steps
    for (int i = 0; i < list.size(); i++)
    {
       if (list[i].loses == 0)
        {
            list[i].winPercent = 100.00;
        }
        else if (list[i].wins == 0)
        {
            list[i].winPercent = 0.00;
        }
        else 
        {
            list[i].winPercent = list[i].wins / totalGames;
        }
    }
}

void printTeams(vector<Team> list)
{
    //alternate way (learned from dfs project)
    //while (i != list.end())
        //i++
    //i would be a team object rather than a int
    for (int i = 0; i < list.size(); i++)
    {
        cout << list[i].teamName << endl;
    }
}

void printScores(vector<Team> list)
{
    for (int i = 0; i < list.size(); i++)
    {
        cout << list[i].teamName << ": " << list[i].score << endl;
    }
}

void printRanks(vector<Team> list)// You don't need '&' for this method
{
    int rank = 1;
    while (rank != list.size() + 1)
    {
        for (int i = 0; i < list.size(); i++)
        {
            if(list[i].seed == rank)
            {
                cout << list[i].teamName << " is the #" << list[i].seed << " seed:   ";
                cout << "Record: " << list[i].wins << " - " << list[i].loses << "   ";
                cout << "Total Points: " << list[i].pTotal << endl;
            }
        }
        rank++;
    }
}

void genOneScore(vector<Team> &list, int index) //for one team
{ 
    int min = 75;
    int max = 120;

    random_device randomSeed; //Obtain a random number from hardware?
    mt19937 gen(randomSeed()); //random generator seed
    uniform_int_distribution<> distr(min, max); //range  

    int genScore = distr(gen);
    list[index].score = genScore;

    list[index].pTotal = list[index].pTotal + genScore;

}

void genOTScore(vector<Team> &list, int index)
{
    int min = 0;
    int max = 15;

    random_device randomSeed; //Obtain a random number from hardware?
    mt19937 gen(randomSeed()); //random generator seed
    uniform_int_distribution<> distr(min, max); //range  

    int OTScore = distr(gen);
    list[index].score = list[index].score + OTScore;

    list[index].pTotal = list[index].pTotal + OTScore;
}

void generateAllScores(vector<Team> &list) //all teams (I don't really use this method - I use genOne Score instead)
{
    //I want to have these scores depend on the rank and the seeding matchup
        //Should I have offensive and defensive ratings?
    int min = 75;
    int max = 120;

    random_device randomSeed; //Obtain a random number from hardware?
    mt19937 gen(randomSeed()); //random generator seed
    uniform_int_distribution<> distr(min, max); //range 

    for (int i = 0; i < list.size(); i++)
    {
        int genScore = distr(gen);
        list[i].score = genScore;

        list[i].pTotal = list[i].score + genScore; //add to total score
    }
}

void createMatchups(vector<Team> &list)
{
    //Note
        //For the vector of bools
            //whatever the team's index is has to be true for it's vertex because it can't play itself
                // so it may jus have to skip over it's iterators position
                    //ex. if (i == it)
                        //continue;
    int it = 0; //iterator for team
    while (it < list.size())
    {
        for (int i = 0; i < list.size(); i++) //it shouldn't compare to 
        {
            if (list[it].hasPlayed[i] == false)
            {
                genOneScore(list, it);
                genOneScore(list, i);
                list[it].hasPlayed[i] = true;
                list[i].hasPlayed[it] = true;
                if (list[it].score > list[i].score)
                {
                    list[it].wins++;
                    
                    list[i].loses++;
                }
                else if (list[it].score < list[i].score)
                {
                    list[i].wins++;

                    list[it].loses++;
                }
                else if (list[it].score == list[i].score)
                {
                    bool tied = true;
                    while (tied == true)
                    {
                        genOTScore(list, it);
                        genOTScore(list, i);

                        if (list[it].score > list[i].score)
                        {
                            list[it].wins++;
                            
                            list[i].loses++;
                            
                            tied = false;
                        }
                        else if (list[it].score < list[i].score)
                        {
                            list[i].wins++;

                            list[it].loses++;

                            tied = false;
                        }
                    }
                }
                
            }
        }
        it++;
    }
}

void rankTeams(vector<Team> &list)
{
    //Could I set each teams seed to the max number of teams
    //  and then add or subtract 1 due to their placement 

    //For for loop I loop from 0 to size, then 1, to size, then 2 to size, etc

    for (int i = 0; i < list.size(); i++)
    {
        for (int j = 0; j < list.size(); j++)
        {
            if(list[i].teamName == list[j].teamName) //If comparing the same team
            {
                continue;
            }
            else //If not the same team
            {
                if (list[i].wins > list[j].wins) //won more games
                {
                    list[i].seed--;
                }
                else if (list[i].wins == list[j].wins) //won same amount of games
                {
                    //Handle by point differenital
                    if (list[i].pTotal > list[j].pTotal)
                    {
                        list[i].seed--;
                    }
                    else if (list[i].pTotal < list[j].pTotal)
                    {
                        list[i].seed = list[i].seed; //Don't change (wait for a later iteration for the first if statement to take effect)
                                                    // It will make sense once the loop gets to the other team
                    }
                    else if (list[i].pTotal == list[j].pTotal) //I don't have a decision for this instance yet
                    {
                        list[i].seed = list[i].seed;
                    }
                }
                else
                {
                    continue;
                }
            }
        }
    }
}

vector<Team> orderTeams(vector<Team> &list) //This method re-orders the vector in order of team ranks (makes it easier to write playoff method)
{
    vector<Team> newList;
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i].seed == i++)
        {
            newList.push_back(list[i]);
        }
    }

    return newList;
}

/*
Team findSeed(int num, vector<Team> list)
{
    for (int j = 0; j < list.size(); j++)
    {
        if (list[j].seed == num)
        {
            return list[j];
        }
    }
}
*/

//You probably have to call setMatchupsFalse() before starting playoffs (you could really call it in this method)
void startPlayoffs(vector<Team> &list) //The round vector should be the size 16
{
    //Assuming vector Round size is 16.
    setMatchupsFalse(list);

    Round eliteEight1;
    Round eliteEight2;
    Round eliteEight3;
    Round eliteEight4;
    Round finalFour1;
    Round finalFour2;
    Round natChampionship;

    for (int i = 0; i < list.size(); i++)
    {
        if (i == 0) //Game 1 (winner goes to Game 9)
        {
            genOneScore(list, 0); //seed 1
            genOneScore(list, 15); //seed 16
            if (list[0].score == list[15].score)
            {
                while (list[0].score == list[15].score)
                {
                    genOTScore(list, 0); //seed 1
                    genOTScore(list, 15); //seed 16
                }
            }
            if (list[0].score > list[15].score)
            {
                list[0].wins++;
                list[15].loses++;
                cout << "The " << list[0].location << " " << list[0].teamName << "move on to the Elite Eight!" << endl;
                cout << "The " << list[15].location << " " << list[15].teamName << "have been eliminated!" << endl;
                eliteEight1.team1 = &list[0];
            }
            else
            {
                list[15].wins++;
                list[0].loses++;
                cout << "The " << list[15].location << " " << list[15].teamName << "move on to the Elite Eight!" << endl;
                cout << "The " << list[0].location << " " << list[0].teamName << "have been eliminated!" << endl;
                eliteEight1.team1 = &list[15];
            }
        }

        if (i == 1) //Game 5 (winner goes to Game 9)
        {
            genOneScore(list, 7); //seed 8
            genOneScore(list, 8); //seed 9
            if (list[7].score == list[8].score)
            {
                while (list[7].score == list[8].score)
                {
                    genOTScore(list, 7); 
                    genOTScore(list, 8);
                }
            }
            if (list[7].score > list[8].score)
            {
                list[7].wins++;
                list[8].loses++;
                cout << "The " << list[7].location << " " << list[7].teamName << "move on to the Elite Eight!" << endl;
                cout << "The " << list[8].location << " " << list[8].teamName << "have been eliminated!" << endl;
                eliteEight1.team2 = &list[7];
            }
            else //upset
            {
                list[8].wins++;
                list[7].loses++;
                cout << "IT'S AN UPSET!!" << endl;
                cout << "The " << list[8].location << " " << list[8].teamName << "move on to the Elite Eight!" << endl;
                cout << "The " << list[7].location << " " << list[7].teamName << "have been eliminated!" << endl;
                eliteEight1.team2 = &list[8];
            }
        }

        if (i == 2) //Game 3 (winner goes to Game 11)
        {
            genOneScore(list, 2); //seed 3
            genOneScore(list, 13); //seed 14
            if (list[7].score == list[8].score)
            {
                while (list[7].score == list[8].score)
                {
                    genOTScore(list, 2); 
                    genOTScore(list, 13); 
                }
            }
            if (list[7].score > list[8].score)
            {
                list[7].wins++;
                list[8].loses++;
                cout << "The " << list[7].location << " " << list[7].teamName << "move on to the Elite Eight!" << endl;
                cout << "The " << list[8].location << " " << list[8].teamName << "have been eliminated!" << endl;
                eliteEight1.team2 = &list[7];
            }
            else //upset
            {
                list[8].wins++;
                list[7].loses++;
                cout << "IT'S AN UPSET!!" << endl;
                cout << "The " << list[8].location << " " << list[8].teamName << "move on to the Elite Eight!" << endl;
                cout << "The " << list[7].location << " " << list[7].teamName << "have been eliminated!" << endl;
                eliteEight1.team2 = &list[8];
            }
        }
}
