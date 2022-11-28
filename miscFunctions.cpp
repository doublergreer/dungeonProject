#include <iostream>
#include <fstream>
using namespace std;


int split1(string input_string, char delimiter, string arr[], int arr_size)
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

bool misfortuneCalc(int percent_chance)
{
    int reduced_num = percent_chance / 10;

    srand(time(NULL));
    int rand_num = (rand() % (10 - 1 + 1)) + 1;
    
    if(rand_num > 1 && rand_num <= reduced_num)
    {
        return true; //there is misfortune 
    }
    else
    {
        return false; //there is no misfortune
    }
}

int readRiddles(string file_name, string riddles[][2], int arr_size) {
    ifstream file;
    string lines = "";
    int num_riddles = 0;
    

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
                int split_value = split1(lines, '~', temp, arr_size);

                riddles[num_riddles][0] = temp[0];
                riddles[num_riddles][1] = temp[1];
                num_riddles++;
            }
        }
    }
    return num_riddles;
}
