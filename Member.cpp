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

//This function will remove a member of the party 
//It will also remove the weapon they were holding 
//It will remove one armor from the party if the party has armor
// bool Member::death(string name, Member members[], Inventory inv)
// {
//     for (int i = 0; i < 5; i++) {
//         if (members[i].name_ == name) {
//             members[i] = Member();
//             members[i].setFullness(0);
//             inv.setWeaponsAt("", i);
//             if (members[i].has_armor_) {
//                 inv.setArmor(inv.getArmor()-1);
//                 members[i].has_armor_ = false;
//             }
//         }
//     }
//     return 0;
// }