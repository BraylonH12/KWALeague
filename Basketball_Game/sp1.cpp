#include <iostream>
#include <string>
#include <vector>
//#include <math>
#include <stdlib.h>
#include <math.h>
#include <random>

using namespace std;

//Node for each team
struct team
{
    string teamName;
    int wins;
    int loses;
    double winPercent;
    int seed;
    int score;
    int pTotal; //points total
    team* next;
};

//You could honeslty create a struct of the class "Team" and put all the info for the class. 
    // I think this could make it easier to call functions without having to traverse through the list of
    //  nodes each call.
team* buildTeams (string name, team* head)
{
    team *currentTeam = new team;
    currentTeam->teamName = name;
    currentTeam->next = nullptr;
    currentTeam->wins = 0;
    currentTeam->loses = 0;
    currentTeam->winPercent = 0;
    int seed = 0;
    int score = 0;
    int pTotal = 0;

    if (head->next == nullptr)
    {
        head->next = currentTeam;
    }
    else 
    {
        //This doesn't actually create a node, but a temporary placement for the node
        team * temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = currentTeam;
    }

    return currentTeam;
}

//If this method doesn't work, I most likely found the team incorrectly
double calculateWinP(string tName, team* head, int size) //I could modify this to inlcude all teams instead of just one
{ 
    //The size is the league size
    //Figuring out how to access specific team
    //You could make a head node through the main method and make it have null values.
    //Should I delete this first team after the code finds the percent value

    //Steps

    //Find Team
    team* temp = head;
    while (temp->teamName != tName)
    {
        temp = temp->next;
    }

    //Once Found
    int w = 0; //wins

    int l = 0; //loses

    double p = 0; //percentage

    if (temp->loses == 0)
    {
        p = 100.00;
    }
    else if (temp->wins == 0)
    {
        p = 0.00;
    }
    else 
    {
        p = temp->wins / temp->loses;
    }
    return p;
}

void cAllWinP(team* head)
{
    team* temp = head;
    while (temp != nullptr)
    {
        //Once Found
        int w = 0; //wins

        int l = 0; //loses

        double p = 0; //percentage

        if (temp->loses == 0)
        {
            p = 100.00;
        }
        else if (temp->wins == 0)
        {
            p = 0.00;
        }
        else 
        {
            p = temp->wins / temp->loses;
        }
            temp = temp->next;
    }

    return;

}
void printTeams(team *head)
{
    team* temp = head;
    while (temp->next != nullptr)
    {
        cout << temp->teamName << endl;
        temp = temp->next;
    }
    cout << temp->teamName << endl; //accounts for last Team (the last team will have a 'next == nullptr)'

    return;
}

void generateScores(team* head)
{
    team* temp = head; 
    while (temp != nullptr) //I think this statement works for the for loop
    {
        //temp->score = math.random();
        temp = temp->next;
    }
}

void rankTeams(team* head)
{
    //Could I set each teams seed to the max number of teams
    //  and then add or subtract 1 due to their placement 
    team* temp1 = head;
    team* temp2 = head->next;
    while(temp1 != nullptr && temp2 != nullptr) //In this method will the last team compare to the first?
    {
        if (temp1->winPercent < temp2->winPercent)
        {
            temp1->seed = temp1->seed - 1;
        }
        else if (temp1->winPercent > temp2->winPercent)
        {
            break; //Stays the same seed;
        }
        else if (temp1->winPercent == temp2->winPercent)
        {
            if (temp1->pTotal > temp2->pTotal)
            {
                temp1->seed = temp1->seed - 1;
            }
        }
        temp1 = temp1->next;
        temp2 = temp2->next;
        //Account for tie;
    }

    return;
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
    cout << "This program covers an KWA basketball season" << endl;
    cout << "Enter your team names with '-' substituting for spaces" << endl;
    cout << "When you are finished creating teams, type 'finished' to proceed" << endl;

    team* head = new team;
    head->next = nullptr;

    int totalTeams = 0;
    string input;
    cin >> input;
    while (input != "finished")
    {
        buildTeams(input, head);
        totalTeams++;
        cin >> input;
    }

    //Here are all the teams you created
    //PrintTeams();

    cout << "Here are all the entered teams:" << endl;
    printTeams(head);

    //generateScores(head);

    //cAllWinP(head);
    //rank(head);

    cout << "The regular season will now begin" << endl;

    //generateScores(head);
    

    cout << " are the #1 seed" << endl;
    cout << " are the #2 seed" << endl;
    cout << " are the #3 seed" << endl;
    cout << " are the #4 seed" << endl;
    
    cout << "Get ready for the Tournament!" << endl;

    return 0;
}