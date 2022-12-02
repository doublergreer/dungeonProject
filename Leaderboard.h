//Authors Nicolas Post and Ryan Greer 
#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Leaderboard {
    public:
        Leaderboard();
        Leaderboard(string name);
        Leaderboard(string name, int score);

        int getScore();
        void setScore(int score);

        string getName();
        void setName(string name);

        int calculateScore(int monsters_killed, int rooms_cleared, int sorcerer_anger);

        void writeLeaderboard(vector<Leaderboard> vec);
        void bubbleSort(vector <Leaderboard> & final_score);
        int readLeaderboard(string file_name, vector<Leaderboard> & vec);

    private:
        int score_;
        string name_;
}; 

#endif