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
                        cout << "(teamName/city/other/exit)" << endl;
                        cin >> answer;
                        if (answer == "teamName")
                        {
                            cout << "What would you like the team name to be?" << endl;
                            cin >> answer;
                            list[i].teamName = answer;
                            cout << "Team name changed to " << list[i].teamName << endl;
                            return;
                        }
                        else if (answer == "city")
                        {
                            cout << "What would you like the team location to be?" << endl;
                            cout << "Original Location: " << list[i].location << endl;
                            cin >> answer;
                            list[i].location = answer;
                            cout << "Team location changed to " << list[i].location << endl;
                            return;
                        }
                        else if (answer == "other")
                        {
                            cout << "Still coding" << endl;
                            return;
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

void printTeamInfo(string name, vector<Team> list)
{
    bool found = false;
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i].teamName == name)
        {
            cout << "Printing Rating " << list[i].teamName << " information . . ." << endl;
            cout << "Education Rating: " << list[i].education << endl;
            //cout << "Coach Rating: " << list[i].coach->rating << endl; //Still working on this so it may not work (I need to build coaches for each team)
            cout << "Campus Life Rating: " << list[i].campusLife << endl;
            //cout << "Rivals: " << endl; //I still need to add this as an array for the teams
            cout << "ChampionShips: " << list[i].championships << endl;
            found = true;
        }
    }
    if (found == false)
    {
        cout << "Incorrect team name or team not found" << endl << endl;
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
    int currentSeed = 0;
    for (int i = 0; i < list.size(); i++)
    {
        currentSeed++; //There's probably a way not to use this and use i instead
        for (int j = 0; j < list.size(); j++)
        {
            if (list[j].seed == currentSeed)
            {
                newList.push_back(list[j]);
                break;
            }
        }
    }

    return newList;
}

void resetLeague(vector<Team> &list) //call before next season
{
    int size = list.size();
    for (int i = 0; i < list.size(); i++)
    {
        list[i].wins = 0;
        list[i].loses = 0;
        list[i].seed = size;
    }
}
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

    string input;
    bool finished = false;
    int i = 0;

    cout << "Press Enter to Continue" << endl; // int array = {1, 2, 4, 5}
    getline(cin, input);
    
    while (finished == false)
    {
        cout << "Press Enter to Continue" << endl;
        getline(cin, input);

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
                cout << "The " << list[0].location << " " << list[0].teamName << " move on to the Elite Eight!" << endl;
                cout << "The " << list[15].location << " " << list[15].teamName << " have been eliminated!" << endl;
                eliteEight1.team1 = &list[0];
            }
            else
            {
                list[15].wins++;
                list[0].loses++;
                cout << "The " << list[15].location << " " << list[15].teamName << " move on to the Elite Eight!" << endl;
                cout << "The " << list[0].location << " " << list[0].teamName << " have been eliminated!" << endl;
                eliteEight1.team1 = &list[15];
            }
            cout << "Final Score: " << list[0].teamName << " (" << list[0].score << ") - " << list[15].teamName;
            cout << "(" << list[15].score << ")"<< endl;
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
                cout << "The " << list[7].location << " " << list[7].teamName << " move on to the Elite Eight!" << endl;
                cout << "The " << list[8].location << " " << list[8].teamName << " have been eliminated!" << endl;
                eliteEight1.team2 = &list[7];
            }
            else //upset
            {
                list[8].wins++;
                list[7].loses++;
                cout << "IT'S AN UPSET!!" << endl;
                cout << "The " << list[8].location << " " << list[8].teamName << " move on to the Elite Eight!" << endl;
                cout << "The " << list[7].location << " " << list[7].teamName << " have been eliminated!" << endl;
                eliteEight1.team2 = &list[8];
            }
            cout << "Final Score: " << list[7].teamName << " (" << list[7].score << ") - " << list[8].teamName;
            cout << "(" << list[8].score << ")"<< endl;
        }

        if (i == 2) //Game 3 (winner goes to Game 11)
        {
            genOneScore(list, 2); //seed 3
            genOneScore(list, 13); //seed 14
            if (list[2].score == list[13].score)
            {
                while (list[2].score == list[13].score)
                {
                    genOTScore(list, 2); 
                    genOTScore(list, 13); 
                }
            }
            if (list[2].score > list[13].score)
            {
                list[2].wins++;
                list[13].loses++;
                cout << "The " << list[2].location << " " << list[2].teamName << " move on to the Elite Eight!" << endl;
                cout << "The " << list[13].location << " " << list[13].teamName << " have been eliminated!" << endl;
                eliteEight2.team1 = &list[2];
            }
            else //upset
            {
                list[13].wins++;
                list[2].loses++;
                cout << "IT'S AN UPSET!!" << endl;
                cout << "The " << list[13].location << " " << list[13].teamName << " move on to the Elite Eight!" << endl;
                cout << "The " << list[2].location << " " << list[2].teamName << " have been eliminated!" << endl;
                eliteEight2.team1 = &list[13];
            }
            cout << "Final Score: " << list[2].teamName << " (" << list[2].score << ") - " << list[13].teamName;
            cout << "(" << list[13].score << ")"<< endl;
        }

        if (i == 3) //Game 7 (winner goes to Game 11)
        {
            genOneScore(list, 4); //seed 5
            genOneScore(list, 11); //seed 12
            if (list[4].score == list[11].score)
            {
                while (list[4].score == list[11].score)
                {
                    genOTScore(list, 4); 
                    genOTScore(list, 11); 
                }
            }
            if (list[4].score > list[11].score)
            {
                list[4].wins++;
                list[11].loses++;
                cout << "The " << list[4].location << " " << list[4].teamName << " move on to the Elite Eight!" << endl;
                cout << "The " << list[11].location << " " << list[11].teamName << " have been eliminated!" << endl;
                eliteEight2.team2 = &list[4];
            }
            else //upset
            {
                list[11].wins++;
                list[4].loses++;
                cout << "IT'S AN UPSET!!" << endl;
                cout << "The " << list[11].location << " " << list[11].teamName << " move on to the Elite Eight!" << endl;
                cout << "The " << list[4].location << " " << list[4].teamName << " have been eliminated!" << endl;
                eliteEight2.team2 = &list[11];
            }
            cout << "Final Score: " << list[4].teamName << " (" << list[4].score << ") - " << list[11].teamName;
            cout << "(" << list[11].score << ")"<< endl;
        }

        if (i == 4) //Game 2 (winner goes to Game 10)
        {
            genOneScore(list, 1); //seed 2
            genOneScore(list, 14); //seed 15
            if (list[1].score == list[14].score)
            {
                while (list[1].score == list[14].score)
                {
                    genOTScore(list, 1); 
                    genOTScore(list, 14); 
                }
            }
            if (list[1].score > list[14].score)
            {
                list[1].wins++;
                list[14].loses++;
                cout << "The " << list[1].location << " " << list[1].teamName << " move on to the Elite Eight!" << endl;
                cout << "The " << list[14].location << " " << list[14].teamName << " have been eliminated!" << endl;
                eliteEight3.team1 = &list[1];
            }
            else //upset
            {
                list[14].wins++;
                list[1].loses++;
                cout << "IT'S AN UPSET!!" << endl;
                cout << "The " << list[14].location << " " << list[14].teamName << " move on to the Elite Eight!" << endl;
                cout << "The " << list[1].location << " " << list[1].teamName << " have been eliminated!" << endl;
                eliteEight3.team1 = &list[14];
            }
            cout << "Final Score: " << list[1].teamName << " (" << list[1].score << ") - " << list[14].teamName;
            cout << "(" << list[14].score << ")"<< endl;
        }

        if (i == 5) //Game 6 (winner goes to Game 10)
        {
            genOneScore(list, 6); //seed 7
            genOneScore(list, 9); //seed 10
            if (list[6].score == list[9].score)
            {
                while (list[6].score == list[9].score)
                {
                    genOTScore(list, 6); 
                    genOTScore(list, 9); 
                }
            }
            if (list[6].score > list[9].score)
            {
                list[6].wins++;
                list[9].loses++;
                cout << "The " << list[6].location << " " << list[6].teamName << " move on to the Elite Eight!" << endl;
                cout << "The " << list[9].location << " " << list[9].teamName << " have been eliminated!" << endl;
                eliteEight3.team2 = &list[6];
            }
            else //upset
            {
                list[9].wins++;
                list[6].loses++;
                cout << "IT'S AN UPSET!!" << endl;
                cout << "The " << list[9].location << " " << list[9].teamName << " move on to the Elite Eight!" << endl;
                cout << "The " << list[6].location << " " << list[6].teamName << " have been eliminated!" << endl;
                eliteEight3.team2 = &list[14];
            }
            cout << "Final Score: " << list[6].teamName << " (" << list[6].score << ") - " << list[9].teamName;
            cout << "(" << list[9].score << ")"<< endl;
        }

        if (i == 6) //Game 4 (winner goes to Game 12)
        {
            genOneScore(list, 3); //seed 4
            genOneScore(list, 12); //seed 13
            if (list[3].score == list[12].score)
            {
                while (list[3].score == list[12].score)
                {
                    genOTScore(list, 3); 
                    genOTScore(list, 12); 
                }
            }
            if (list[3].score > list[12].score)
            {
                list[3].wins++;
                list[12].loses++;
                cout << "The " << list[3].location << " " << list[3].teamName << " move on to the Elite Eight!" << endl;
                cout << "The " << list[12].location << " " << list[12].teamName << " have been eliminated!" << endl;
                eliteEight4.team1 = &list[3];
            }
            else //upset
            {
                list[12].wins++;
                list[3].loses++;
                cout << "IT'S AN UPSET!!" << endl;
                cout << "The " << list[12].location << " " << list[12].teamName << " move on to the Elite Eight!" << endl;
                cout << "The " << list[3].location << " " << list[3].teamName << " have been eliminated!" << endl;
                eliteEight4.team1 = &list[12];
            }
            cout << "Final Score: " << list[3].teamName << " (" << list[3].score << ") - " << list[12].teamName;
            cout << "(" << list[12].score << ")"<< endl;
        }

        if (i == 7) //Game 8 (winner goes to Game 12)
        {
            genOneScore(list, 5); //seed 6
            genOneScore(list, 10); //seed 11
            if (list[5].score == list[10].score)
            {
                while (list[5].score == list[10].score)
                {
                    genOTScore(list, 5); 
                    genOTScore(list, 10); 
                }
            }
            if (list[5].score > list[10].score)
            {
                list[5].wins++;
                list[10].loses++;
                cout << "The " << list[5].location << " " << list[5].teamName << " move on to the Elite Eight!" << endl;
                cout << "The " << list[10].location << " " << list[10].teamName << " have been eliminated!" << endl;
                eliteEight4.team2 = &list[5];
            }
            else //upset
            {
                list[10].wins++;
                list[5].loses++;
                cout << "IT'S AN UPSET!!" << endl;
                cout << "The " << list[10].location << " " << list[10].teamName << " move on to the Elite Eight!" << endl;
                cout << "The " << list[5].location << " " << list[5].teamName << " have been eliminated!" << endl;
                eliteEight4.team2 = &list[10];
            }
            cout << "Final Score: " << list[5].teamName << " (" << list[5].score << ") - " << list[10].teamName;
            cout << "(" << list[10].score << ")"<< endl;
        }

        if (i == 8) //Game 9 (winner goes to Game 13)
        {
            cout << "Time for the Elite 8!!" << endl;
            int index1; //team1
            int index2; //team2
            for (int j = 0; j < list.size(); j++) //Finding first team
            {
                if (eliteEight1.team1->teamName == list[j].teamName)
                {
                    index1 = j;
                }
            }
            for (int j = 0; j < list.size(); j++)
            {
                if (eliteEight1.team2->teamName == list[j].teamName)
                {
                    index2 = j;
                }
            }
            genOneScore(list, index1); //winner of Game 1
            genOneScore(list, index2); //winner of Game 5
            if (list[index1].score == list[index2].score)
            {
                while (list[index1].score == list[index2].score)
                {
                    genOTScore(list, index1); 
                    genOTScore(list, index2); 
                }
            }
            if (list[index1].score > list[index2].score)
            {
                list[index1].wins++;
                list[index2].loses++;
                cout << "The " << list[index1].location << " " << list[index1].teamName << " move on to the Final Four!" << endl;
                cout << "The " << list[index2].location << " " << list[index2].teamName << " have been eliminated!" << endl;
                finalFour1.team1 = &list[index1];
            }
            else //upset
            {
                list[index2].wins++;
                list[index1].loses++;
                if (eliteEight1.team1->seed < eliteEight1.team2->seed)
                {
                    cout << "IT'S AN UPSET!!" << endl;
                }
                cout << "The " << list[index2].location << " " << list[index2].teamName << " move on to the Final Four!" << endl;
                cout << "The " << list[index1].location << " " << list[index1].teamName << " have been eliminated!" << endl;
                finalFour1.team1 = &list[index2];
            }
            cout << "Final Score: " << list[index1].teamName << " (" << list[index1].score << ") - " << list[index2].teamName;
            cout << "(" << list[index2].score << ")"<< endl;
        }

        if (i == 9) //Game 11 (winner goes to Game 13)
        {
            int index1; //team1
            int index2; //team2
            for (int j = 0; j < list.size(); j++) //Finding first team
            {
                if (eliteEight2.team1->teamName == list[j].teamName)
                {
                    index1 = j;
                }
            }
            for (int j = 0; j < list.size(); j++)
            {
                if (eliteEight2.team2->teamName == list[j].teamName)
                {
                    index2 = j;
                }
            }
            genOneScore(list, index1); //winner of Game 1
            genOneScore(list, index2); //winner of Game 5
            if (list[index1].score == list[index2].score)
            {
                while (list[index1].score == list[index2].score)
                {
                    genOTScore(list, index1); 
                    genOTScore(list, index2); 
                }
            }
            if (list[index1].score > list[index2].score)
            {
                list[index1].wins++;
                list[index2].loses++;
                cout << "The " << list[index1].location << " " << list[index1].teamName << " move on to the Final Four!" << endl;
                cout << "The " << list[index2].location << " " << list[index2].teamName << " have been eliminated!" << endl;
                finalFour1.team2 = &list[index1];
            }
            else //upset
            {
                list[index2].wins++;
                list[index1].loses++;
                if (eliteEight2.team1->seed < eliteEight2.team2->seed)
                {
                    cout << "IT'S AN UPSET!!" << endl;
                }
                cout << "The " << list[index2].location << " " << list[index2].teamName << " move on to the Final Four!" << endl;
                cout << "The " << list[index1].location << " " << list[index1].teamName << " have been eliminated!" << endl;
                finalFour1.team2 = &list[index2];
            }
            cout << "Final Score: " << list[index1].teamName << " (" << list[index1].score << ") - " << list[index2].teamName;
            cout << "(" << list[index2].score << ")"<< endl;
        }

        if (i == 10) //Game 10 (winner goes to Game 14)
        {
            int index1; //team1
            int index2; //team2
            for (int j = 0; j < list.size(); j++) //Finding first team
            {
                if (eliteEight3.team1->teamName == list[j].teamName)
                {
                    index1 = j;
                }
            }
            for (int j = 0; j < list.size(); j++)
            {
                if (eliteEight3.team2->teamName == list[j].teamName)
                {
                    index2 = j;
                }
            }
            genOneScore(list, index1); //winner of Game 1
            genOneScore(list, index2); //winner of Game 5
            if (list[index1].score == list[index2].score)
            {
                while (list[index1].score == list[index2].score)
                {
                    genOTScore(list, index1); 
                    genOTScore(list, index2); 
                }
            }
            if (list[index1].score > list[index2].score)
            {
                list[index1].wins++;
                list[index2].loses++;
                cout << "The " << list[index1].location << " " << list[index1].teamName << " move on to the Final Four!" << endl;
                cout << "The " << list[index2].location << " " << list[index2].teamName << " have been eliminated!" << endl;
                finalFour2.team1 = &list[index1];
            }
            else //upset
            {
                list[index2].wins++;
                list[index1].loses++;
                if (eliteEight3.team1->seed < eliteEight3.team2->seed)
                {
                    cout << "IT'S AN UPSET!!" << endl;
                }
                cout << "The " << list[index2].location << " " << list[index2].teamName << " move on to the Final Four!" << endl;
                cout << "The " << list[index1].location << " " << list[index1].teamName << " have been eliminated!" << endl;
                finalFour2.team1 = &list[index2];
            }
            cout << "Final Score: " << list[1].teamName << " (" << list[1].score << ") - " << list[14].teamName;
            cout << "(" << list[14].score << ")"<< endl;
        }

        if (i == 11) //Game 12 (winner goes to Game 14)
        {
            int index1; //team1
            int index2; //team2
            for (int j = 0; j < list.size(); j++) //Finding first team
            {
                if (eliteEight4.team1->teamName == list[j].teamName)
                {
                    index1 = j;
                }
            }
            for (int j = 0; j < list.size(); j++)
            {
                if (eliteEight4.team2->teamName == list[j].teamName)
                {
                    index2 = j;
                }
            }
            genOneScore(list, index1); //winner of Game 1
            genOneScore(list, index2); //winner of Game 5
            if (list[index1].score == list[index2].score)
            {
                while (list[index1].score == list[index2].score)
                {
                    genOTScore(list, index1); 
                    genOTScore(list, index2); 
                }
            }
            if (list[index1].score > list[index2].score)
            {
                list[index1].wins++;
                list[index2].loses++;
                cout << "The " << list[index1].location << " " << list[index1].teamName << " move on to the Final Four!" << endl;
                cout << "The " << list[index2].location << " " << list[index2].teamName << " have been eliminated!" << endl;
                finalFour2.team2 = &list[index1];
            }
            else //upset
            {
                list[index2].wins++;
                list[index1].loses++;
                if (eliteEight4.team1->seed < eliteEight4.team2->seed)
                {
                    cout << "IT'S AN UPSET!!" << endl;
                }
                cout << "The " << list[index2].location << " " << list[index2].teamName << " move on to the Final Four!" << endl;
                cout << "The " << list[index1].location << " " << list[index1].teamName << " have been eliminated!" << endl;
                finalFour2.team2 = &list[index2];
            }
            cout << "Final Score: " << list[index1].teamName << " (" << list[index1].score << ") - " << list[index2].teamName;
            cout << "(" << list[index2].score << ")"<< endl;
        }

        if (i == 12) //Game 13 (winner goes to National Championship)
        {
            int index1; //team1
            int index2; //team2
            for (int j = 0; j < list.size(); j++) //Finding first team
            {
                if (finalFour1.team1->teamName == list[j].teamName)
                {
                    index1 = j;
                }
            }
            for (int j = 0; j < list.size(); j++)
            {
                if (finalFour1.team2->teamName == list[j].teamName)
                {
                    index2 = j;
                }
            }
            genOneScore(list, index1); //winner of Game 1
            genOneScore(list, index2); //winner of Game 5
            if (list[index1].score == list[index2].score)
            {
                while (list[index1].score == list[index2].score)
                {
                    genOTScore(list, index1); 
                    genOTScore(list, index2); 
                }
            }
            if (list[index1].score > list[index2].score)
            {
                list[index1].wins++;
                list[index2].loses++;
                cout << "The " << list[index1].location << " " << list[index1].teamName << " move on to the National Championship!" << endl;
                cout << "The " << list[index2].location << " " << list[index2].teamName << " have been eliminated!" << endl;
                natChampionship.team1 = &list[index1];
            }
            else //upset
            {
                list[index2].wins++;
                list[index1].loses++;
                if (finalFour1.team1->seed < finalFour1.team2->seed)
                {
                    cout << "IT'S AN UPSET!!" << endl;
                }
                cout << "The " << list[index2].location << " " << list[index2].teamName << " move on to the Final Four!" << endl;
                cout << "The " << list[index1].location << " " << list[index1].teamName << " have been eliminated!" << endl;
                natChampionship.team1 = &list[index2];
            }
            cout << "Final Score: " << list[index1].teamName << " (" << list[index1].score << ") - " << list[index2].teamName;
            cout << "(" << list[index2].score << ")"<< endl;
        }

        if (i == 13) //Game 14 (winner goes to National Championship)
        {
            int index1; //team1
            int index2; //team2
            for (int j = 0; j < list.size(); j++) //Finding first team
            {
                if (finalFour2.team1->teamName == list[j].teamName)
                {
                    index1 = j;
                }
            }
            for (int j = 0; j < list.size(); j++)
            {
                if (finalFour2.team2->teamName == list[j].teamName)
                {
                    index2 = j;
                }
            }
            genOneScore(list, index1); //winner of Game 1
            genOneScore(list, index2); //winner of Game 5
            if (list[index1].score == list[index2].score)
            {
                while (list[index1].score == list[index2].score)
                {
                    genOTScore(list, index1); 
                    genOTScore(list, index2); 
                }
            }
            if (list[index1].score > list[index2].score)
            {
                list[index1].wins++;
                list[index2].loses++;
                cout << "The " << list[index1].location << " " << list[index1].teamName << " move on to the National Championship!" << endl;
                cout << "The " << list[index2].location << " " << list[index2].teamName << " have been eliminated!" << endl;
                natChampionship.team2 = &list[index1];
            }
            else //upset
            {
                list[index2].wins++;
                list[index1].loses++;
                if (finalFour2.team1->seed < finalFour2.team2->seed)
                {
                    cout << "IT'S AN UPSET!!" << endl;
                }
                cout << "The " << list[index2].location << " " << list[index2].teamName << " move on to the National Championship!" << endl;
                cout << "The " << list[index1].location << " " << list[index1].teamName << " have been eliminated!" << endl;
                natChampionship.team2 = &list[index2];
            }
            cout << "Final Score: " << list[index1].teamName << " (" << list[index1].score << ") - " << list[index2].teamName;
            cout << "(" << list[index2].score << ")"<< endl;
        }

        if (i == 14) //National Championship
        {
            cout << "IT'S TIME FOR THE NATIONAL CHAMPIONSHIP!!" << endl;
            cout << "Press Enter to Continue" << endl;
            getline(cin, input);
            int index1; //team1
            int index2; //team2
            for (int j = 0; j < list.size(); j++) //Finding first team
            {
                if (natChampionship.team1->teamName == list[j].teamName)
                {
                    index1 = j;
                }
            }
            for (int j = 0; j < list.size(); j++)
            {
                if (natChampionship.team2->teamName == list[j].teamName)
                {
                    index2 = j;
                }
            }
            genOneScore(list, index1); //winner of Game 1
            genOneScore(list, index2); //winner of Game 5
            if (list[index1].score == list[index2].score)
            {
                while (list[index1].score == list[index2].score)
                {
                    genOTScore(list, index1); 
                    genOTScore(list, index2); 
                }
            }
            if (list[index1].score > list[index2].score)
            {
                list[index1].wins++;
                list[index1].championships = list[index1].championships++;
                list[index2].loses++;
                cout << "The " << list[index1].location << " " << list[index1].teamName << " are the KWA National Champions!" << endl;
            }
            else //upset
            {
                list[index2].wins++;
                list[index2].championships = list[index2].championships++;
                list[index1].loses++;
                if (natChampionship.team1->seed < natChampionship.team2->seed)
                {
                    cout << "IT'S AN UPSET!!" << endl;
                }
                cout << "The " << list[index2].location << " " << list[index2].teamName << " are the KWA National Champions!" << endl;
            }
            cout << "Final Score: " << list[index1].teamName << " (" << list[index1].score << ") - " << list[index2].teamName;
            cout << "(" << list[index2].score << ")"<< endl;
            finished = true;
        }
        i++;
    }
}
