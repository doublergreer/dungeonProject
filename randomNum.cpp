
#include <iostream>
#include<chrono>
#include<thread>
using namespace std;
using namespace std::this_thread; 
using namespace std::chrono_literals; 

//calculates a random number between two bounds
int randomNum(int first_num, int last_num) {
    srand(time(NULL));
    return (rand() % (last_num - first_num + 1)) + first_num;
}

int main () {
    cout << randomNum(1,3);

}