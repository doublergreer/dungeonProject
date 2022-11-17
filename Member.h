//Authors Nicolas Post and Ryan Greir 
#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include "Inventory.h"
using namespace std;

class Member {
    public:    
        Member();
        Member(string name);

        // bool death(string name, Member members[], Inventory inv);
        //This function will remove a member of the party 
        //It will also remove the weapon they were holding 
        //It will remove one armor from the party if the party has armor 

        string getName();
        void setName(string name);

        int getFullness();
        void setFullness(int fullness);

        bool getArmor();
        void setArmor(bool hasArmor);

    private:
        string name_;
        int fullness_ = 50;
        bool has_armor_ = false;
};

#endif