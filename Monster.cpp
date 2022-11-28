//Authors Nicolas Post and Ryan Greir 
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Monster.h"

using namespace std;

int split(string input_string, char delimiter, string arr[], int arr_size)
{
    int index = 0;
    int length = input_string.length();
    
    if(input_string == "")
        {
            return 0;
        }

    for(int i = 0; i < length; i++)
    {
        if(input_string[i] == delimiter)
        {
            index++;
            
            if(index +1 > arr_size)
            {
                return -1;
            }
        }

        else
        {
            arr[index] = arr[index] + input_string[i];
        }
    }
    return index + 1;
}

Monster::Monster()
{
    name_ = "";
    challenge_rating_ = 0;
}

Monster::Monster(string name, int rating)
{
    name_ = name;
    challenge_rating_ = rating;
}

int Monster::getChallengeRating()
{
    return challenge_rating_;
}

void Monster::setChallengeRating(int challenge_rating)
{
    challenge_rating_ = challenge_rating;
}

string Monster::getMonsterName()
{
    return name_;
}

void Monster::setMonsterName(string name)
{
    name_ = name;
}

//read in monster.txt
//for (count the number of lines) add to monster count
//initialize the array (num monsters)
//for (populate the monster array)
//make a new monster object for each monster listed
int Monster::readMonster(string file_name, Monster monster_array[], int arr_size)
{
    ifstream file;
    string lines = "";
    int num_monsters = 0;
    

    file.open(file_name);

    if(file.is_open())
    {
        while (!file.eof())
        {
            getline(file, lines);

            if(lines.length() > 0)
            {
                string temp[arr_size]; 

                for (int n = 0; n < arr_size; n++)
                {
                    temp[n] = ""; //reset the temporary array
                }

                int split_value = split(lines, ',', temp, arr_size);

                monster_array[num_monsters].setMonsterName(temp[0]);
                monster_array[num_monsters].setChallengeRating(stoi(temp[1]));
                num_monsters++;
            }
        }
    }
    return num_monsters;
}

