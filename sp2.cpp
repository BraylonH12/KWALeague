#include <iostream>
#include <string>
#include <vector>
//#include <math>
#include <stdlib.h>
#include <math.h>
#include <random>
#include <chrono>


using namespace std;

//Description
/*
    This is an alternate version of sp2.cpp that has a vector of structs instead of creating
        the teams as linked list
*/

//Node for each team
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

//You could honeslty create a struct of the class "Team" and put all the info for the class. 
    // I think this could make it easier to call functions without having to traverse through the list of
    //  nodes each call.
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

void editTeam (vector<team> &list, string name)
{
    string answer;
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i].teamName == name)
        {
            cout << "Team found" << endl;
            cout << "Would you like to delete or edit?" << list[i].teamName << endl;
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
                        break;
                    }
                }
            }
            else if (answer == "delete")
            {
                cout << "Deleting " << list[i].teamName << endl;
                list.erase(list.begin() + i);
            }
        }
    }
}

void setMaxRank(vector<team> &list, int size)
{
    for (int i = 0; i < list.size(); i++)
    {
        list[i].seed = size;
    }
}

void setMatchupsFalse(vector<team> &list)
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

void calculateWinP(vector<team> &list) //I could modify this to inlcude all teams instead of just one (Yessir you got it!)
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

void printTeams(vector<team> list)
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

void printScores(vector<team> list)
{
    for (int i = 0; i < list.size(); i++)
    {
        cout << list[i].teamName << ": " << list[i].score << endl;
    }
}

void printRanks(vector<team> list)// You don't need '&' for this method
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

void genOneScore(vector<team> &list, int index) //for one team
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

void genOTScore(vector<team> &list, int index)
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

void generateAllScores(vector<team> &list) //all teams
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

void createMatchups(vector<team> &list)
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


//In Theory
    //Create method to set all teams rank value equal to the total # of teams
        //Then loop through each index and compare the teams to eachother
            //If the teams winP is greater subtract rank by 1, if less subtract by 1, if equal stay the same; (how to check if already compared to tho)
void rankTeams(vector<team> &list)
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

int main(int argc, char* argv[])
{
    // I want to create a program that has 4 teams and ranks these teams in 4 seeds based on a 4 game season.
    // Accounts tie records for point difference
        //You can calculate the standings through win percentage

    //For the end I want to let the program randomly have scores for each team
    //Have it read from a note file eahc team

    //vector <string> players;
        //We can add players later on.

    
    //Intro
    cout << "This program covers an official KWA basketball season" << endl;
    cout << "Enter your team names with '-' substituting for spaces" << endl;
    cout << "When you are finished creating teams, type 'done' to proceed" << endl;

    int totalTeams = 0;

    vector<team> list; 

    string input;
    cin >> input;
    while (input != "done")
    {
        //Both lines below would work, depends on preference
        list.push_back({input, 0, 0, 0, 0, 0, 0}); 
        //buildTeam(input);

        totalTeams++;
        cin >> input;
    }
    setMaxRank(list, totalTeams);
    setMatchupsFalse(list);

    cout << "Here are all the entered teams:" << endl;
    printTeams(list);

    while (true)
    {
        cout << "Would you like to make any changes to the teams? (yes/no)" << endl;
        //editTeams:
        cin >> input;
        if (input == "yes" || input == "Yes")
        {
            cout << "What team would you like to change?" << endl;
            cin >> input;
            editTeam(list, input);
        }
        else if (input == "no" || input == "No")
        {
            break;
        }
        else
        {
            cout << "Please enter again (yes/no)" << endl;
            //goto editTeams;

        }
    }

    //Starting Season
        //How many rounds of matchups
            //for loop of setMatchups False with generate matchups

    cout << "The regular season will now begin" << endl;

    cout << "How many rounds would you like the season to have?" << endl;
    cout << "In a round, a team will play every other team once." << endl;

    int rounds;
    cin >> rounds;


    for (int i = 0; i < rounds; i++)
    {
        setMatchupsFalse(list);
        createMatchups(list); //Create games 
    }


    calculateWinP(list); //must call this before generating ranks
    rankTeams(list); //Gives teams a rank
    printRanks(list); //Print Standings


    
    cout << "Get ready for the Tournament!" << endl;

    return 0;
}