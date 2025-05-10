//Author: Braylon Heavens
//Main File used for execution
    //Will call other files for methods, structs, etc.

#include "kwaTeam.hpp"
#include "kwaPlayer.hpp"
#include "kwaMethods.hpp"

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
        cout << "Type 'print' if you would like to see all teams" << endl;
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
        else if (input == "print" || "Print")
        {
            printTeams(list);
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