//Authors Nicolas Post and Ryan Greir  
#ifndef COOKWARE_H
#define COOKWARE_H

#include <iostream>
using namespace std;

class Cookware {
    public:
        Cookware();
        Cookware(string name, int cost, double chance_of_breaking_);

        string getName();
        void setName(string name);

        int getCost();
        void setCost(int cost);

        double getBreakChance();
        //This function will be used when the player decides to cook something 
        //It will take into account what type of cookware it is 
        //Next it will use a random number generator based off the chance percentage
        //If the cookware does break it will ouput a message and remove the cookware
        //If it doesn't break then it will just continue working until the next tim ethe function is called
    
    private:
        string name_;
        int cost_;
        double chance_of_breaking_;
};

#endif