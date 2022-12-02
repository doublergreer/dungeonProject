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
    score_ = ((double) (monsters_killed + rooms_cleared) / sorcerer_anger) * 1000;
    
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

int splitScore(string input_string, char delimiter, string arr[], int arr_size)
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
            
            // if(index +1 > arr_size)
            // {
            //     return -1;
            // }
        }

        else
        {
            arr[index] = arr[index] + input_string[i];
        }
    }
    return index + 1;
}

//read in monster.txt
//for (count the number of lines) add to monster count
//initialize the array (num monsters)
//for (populate the monster array)
//make a new monster object for each monster listed
int Leaderboard::readLeaderboard(string file_name, vector<Leaderboard> & vec)
{
    ifstream file;
    string lines = "";
    int num_scores = 0;
    int arr_size = 0;
    

    file.open(file_name);

    //get number of lines 
    while (getline(file, lines))
        arr_size++;

    file.close();

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

                int split_value = splitScore(lines, ',', temp, arr_size);

                Leaderboard t;
                t.setName(temp[0]);
                t.setScore(stoi(temp[1]));

                vec.push_back(t);
                num_scores++;
            }
        }
    }
    file.close();
    return num_scores;
}