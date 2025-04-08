#include <string>
#include <vector>
//#include <math>
#include <stdlib.h>
#include <math.h>
#include <random>


using namespace std;

class League
{
    public:

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

        string teamName; //reference to team they play for
    };

    struct Team
    {
        string teamName;
        int wins;
        int loses;
        double winPercent;
        int seed;
        int score; //for every game
        int pTotal; //points total
        //int teamRating (total rank of players / # of players)

        vector<bool> hasPlayed;

        vector<Player> roster; //List of players
    };

    Team buildTeam (string name)
    {
        Team newTeam;
        newTeam.teamName = name;
        newTeam.wins = 0;
        newTeam.loses = 0;
        newTeam.winPercent = 0;
        newTeam.seed = 0;
        newTeam.score = 0;
        newTeam.pTotal = 0;

        return newTeam;
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

    void generateAllScores(vector<Team> &list) //all teams
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


    //In Theory
        //Create method to set all teams rank value equal to the total # of teams
            //Then loop through each index and compare the teams to eachother
                //If the teams winP is greater subtract rank by 1, if less subtract by 1, if equal stay the same; (how to check if already compared to tho)
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


};

int main()
{
    return 0;
}