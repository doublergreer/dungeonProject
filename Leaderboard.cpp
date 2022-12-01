#include <iostream>
#include <vector>
#include <fstream>
#include "Leaderboard.h"
using namespace std;

Leaderboard::Leaderboard() {
    name_ = "";
    score_ = 0;
}
Leaderboard::Leaderboard(string name) {
    name_ = name;
    score_ = 0;
}
Leaderboard::Leaderboard(string name, int score) {
    name_ = name;
    score_ = score;
}

int Leaderboard::getScore()
{
    return score_;
}
void Leaderboard::setScore(int score)
{
    score_ = score;
}

string Leaderboard::getName()
{
    return name_;
}
void Leaderboard::setName(string name) {
    name_ = name;
}

int Leaderboard::calculateScore(int monsters_killed, int rooms_cleared, int sorcerer_anger) {
    score_ = (monsters_killed + rooms_cleared) / sorcerer_anger;
    
    return score_;
}

void Leaderboard::writeLeaderboard(vector<Leaderboard> vec) {
    ofstream fout;
    fout.open("leaderboard.txt");
    for (int i = 0; i < vec.size(); i++) {
        fout << vec.at(i).getName() << "," << vec.at(i).getScore() << endl;
    }
}

//swap for bubblesort with pass by reference
void swap(vector<Leaderboard>& vec, int startIndex, int endIndex) {
    Leaderboard temp = vec.at(startIndex);
    vec.at(startIndex) = vec.at(endIndex);
    vec.at(endIndex) = temp;
}

//
 void Leaderboard::bubbleSort(vector<Leaderboard>& final_score)
 {
    bool swapped = true;
    do
    {
        swapped = false;
        for(int i = 0; i < final_score.size()-1; i++)
        {
            //if left is bigger than right, swap, do this until there are no more swaps
            if (final_score.at(i).getScore() < final_score.at(i+1).getScore())
            {
                swap(final_score, i, i+1);
                swapped = true; 
            }
        }
    } while(swapped);
}