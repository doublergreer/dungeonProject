//Authors Nicolas Post and Ryan Greir 
#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Monster
{
    public:
        Monster();
        Monster(string name, int rating);

        void setChallengeRating(int challenge_rating);
        int getChallengeRating();

        void setMonsterName(string monster_name);
        string getMonsterName();

        int readMonster(string file_name, Monster monster_array[], int arr_size);
        //read in monster.txt
        //for (count the number of lines) add to monster count
        //initialize the array (num monsters)
        //for (populate the monster array)
        //make a new monster object for each monster listed
    

    private:
        string name_;
        int challenge_rating_;

};

#endif