//Authors Nicolas Post and Ryan Greir 
#include <iostream>
#include <iostream>
#include "Inventory.h"
#include "Member.h"

using namespace std;

Member::Member()
{
    name_ = "";
    has_armor_ = false;
}

Member::Member(string name)
{
    name_ = name;
    has_armor_ = false;
}

string Member::getName()
{
    return name_;
}

void Member::setName(string name)
{
    name_ = name;
}

int Member::getFullness()
{
    return fullness_;
}

void Member::setFullness(int fullness)
{
    fullness_ = fullness;
}

bool Member::getArmor()
{
    return has_armor_;
}

void Member::setArmor(bool hasArmor)
{
    has_armor_ = hasArmor;
}

