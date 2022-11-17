//Authors Nicolas Post and Ryan Greir 
#ifndef TREASURE_H
#define TREASURE_H 

#include <iostream>
using namespace std;

class Treasure {
    public:
        Treasure();
        Treasure(string name, int price);

        void setName(string name);
        void setPrice(int price);

        string getName();
        int getPrice();

    private:
        string name_;
        int price_;
};

#endif