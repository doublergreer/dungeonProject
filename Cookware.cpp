//Authors Nicolas Post and Ryan Greir  
#include <iostream>
#include <iostream>
#include "Cookware.h"

using namespace std;

Cookware::Cookware()
{
    name_ = "";
    cost_ = 0;
    chance_of_breaking_ = 0;
}

Cookware::Cookware(string name, int cost, double chance_of_breaking)
{
    name_ = name;
    cost_ = cost;
    chance_of_breaking_ = chance_of_breaking;
}

string Cookware::getName()
{
    return name_;
}

void Cookware::setName(string name)
{
    name = name_;
}

int Cookware::getCost()
{
    return cost_;
}

void Cookware::setCost(int cost)
{
    cost = cost_;
}

double Cookware::getBreakChance()
{
    //This function will be used when the player decides to cook something 
    //It will take into account what type of cookware it is 
    //Next it will use a random number generator based off the chance percentage
    //If the cookware does break it will ouput a message and remove the cookware
    //If it doesn't break then it will just continue working until the next tim ethe function is called
    return chance_of_breaking_;
}



