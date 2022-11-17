
#include <iostream>
#include<chrono>
#include<thread>
using namespace std;
using namespace std::this_thread; 
using namespace std::chrono_literals; 

//calculates a random number between two bounds
int randomNum(int first_num, int last_num, double rand_seed) {
    srand(rand_seed);
    return (rand() % (last_num - first_num + 1)) + first_num;
}

int main () {
    // cout << "Random number between 1 and 10:\t" << randomNum(1, 10) << endl;
    int num = 0, num21s = 0;
    int sleep_time;
    for (int i = 0; i < 10; i++) {
        for (int k = 0; k < 10; k++) {
            //sleep_for(500ms);
            num = randomNum(1,100, time(NULL));

            if (num == 21)
                num21s++;

            cout << num << "\t";

        }
        cout << endl;
    }
    cout << endl << endl << "Number of 21's: " << num21s << endl;

}