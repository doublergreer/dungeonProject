#include <iostream>
using namespace std;

//calculates a random number between two bounds
int randomNum(int first_num, int last_num) {
    srand(time(NULL));
    return (rand() % (last_num - first_num + 1)) + first_num;
}
