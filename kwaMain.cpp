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

    int season = 0;
    int totalTeams = 0;

    vector<Team> list;

    //Pre Built teams (16)
    // /*
    list.push_back(buildTeam("Pumas", "Panama City", 3.5, 3.5, 4, 5)); //1
    list.push_back(buildTeam("Penguins", "Chicago", 3, 4.5, 4, 3.75));
    list.push_back(buildTeam("Titans", "Texas", 5, 4, 5, 5));
    list.push_back(buildTeam("Samurai", "Sacremento", 3.5, 3, 3, 4));
    list.push_back(buildTeam("Deer", "Des Moines", 3, 3, 3, 3)); //5
    list.push_back(buildTeam("Sharks", "Saco", 4.5, 5, 4, 4));
    list.push_back(buildTeam("Geckos", "San Diego", 2.5, 3.5, 3, 3.5));
    list.push_back(buildTeam("Knights", "New York", 3, 4, 5, 4));
    list.push_back(buildTeam("Manta Rays", "Kailua-Kona", 2, 4, 3.5, 4));
    list.push_back(buildTeam("Red", "Providence", 1, 4.5, 4, 2)); //10
    list.push_back(buildTeam("Koalas", "Cancun", 3, 4, 3.75, 5)); 
    list.push_back(buildTeam("Tarantulas", "Tulsa", 1, 3, 5, 3.5)); 
    list.push_back(buildTeam("Leopards", "Lincoln", 4, 4.5, 4, 4)); 
    list.push_back(buildTeam("Axolotls", "New Mexico", 2, 3.5, 3, 5));
    list.push_back(buildTeam("Lynx", "Las Vegas", 3.25, 4.5, 4, 5)); //15
    list.push_back(buildTeam("Krane", "Knoxville", 3.75, 4, 3.5, 4));
    // */

    string input;
    cin >> input;
    while (input != "done" && !input.empty()) //The ".empty()" prevents a null team from being created
    {
        //Both lines below would work, depends on preference
        //list.push_back({input, 0, 0, 0, 0, 0, 0}); 
        list.push_back(buildTeam(input));

        cin >> input;
    }

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

    setMaxRank(list, list.size()); //Sets the rank to the vector size (will be changed later)
    //setMatchupsFalse(list); //Need to reset before each season

    cout << "The regular season will now begin" << endl;

    cout << "How many rounds would you like the season to have? (you will not be able to change this later)" << endl;
    cout << "In a round, a team will play every other team once." << endl << endl << endl;

    int rounds;
    cin >> rounds;

    int numSeason = 1;

    //Coach gameplay option
    while (input != "exit")
    {
        cout << "For every round you can review the Standings and/or review Team information by entering 'review' " << endl;
        cout << "At any time enter 'exit' to leave the game" << endl;
        cout << "Starting season " << numSeason << " . . ." << endl;

        bool reviewStats = true;
        for (int i = 0; i < rounds; i++)
        {
            cout << "Round " << i + 1 << " of Regular Season." << endl;
            setMatchupsFalse(list);
            createMatchups(list); //Create games
            reviewStats = true;
            while (reviewStats == true)
            {
                cout << "Review Standings or Team Info? (yes/no)" << endl;
                cin >> input;
                if (input == "yes" || input == "YES" || input == "Yes")
                {
                    cout << "What information would you like to view (Standings/Team)?  ('back' to override)" << endl;
                    cin >> input;
                    if (input == "Standings" || input == "standings")
                    {
                        calculateWinP(list); //must call this before generating ranks
                        rankTeams(list); //Gives teams a rank
                        printRanks(list); //Print Standings
                        setMaxRank(list, list.size());
                            //reset the ranks after this to prevent future tie issues
                                //I'm going to make a points against variable, will help with ranking issues
                    }
                    else if (input == "Team" || input == "team")
                    {
                        cout << "What team would you like to view" << endl;
                        cin >> input;
                        printTeamInfo(input, list);
                        continue;
                    }
                    else if (input == "back")
                    {
                        continue;
                    }
                }
                else if (input == "no" || input == "NO" || input == "No")
                {
                    reviewStats = false;
                    break;
                }
                else if (input == "exit")
                {
                    return 0;
                }
                else
                {
                    cout << "Invalid input, please try again" << endl;
                }
            }
        }


        calculateWinP(list); //must call this before generating ranks
        rankTeams(list); //Gives teams a rank
        printRanks(list); //Print Standings


        
        cout << "Get ready for the Tournament!" << endl;

        list = orderTeams(list);
        startPlayoffs(list);

        cout << "That concludes Season " << numSeason << endl << endl;
        numSeason++;

        //Reseting for next season
        resetLeague(list);
    }
    cout << "Thank you for Playing!" << endl;

    return 0;
}
