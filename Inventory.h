//Authors Nicolas Post and Ryan Greir 
#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <vector>

#include "Cookware.h"
#include "Treasure.h"
#include "Member.h"
using namespace std;

class Inventory {
    public:    
        Inventory();
        Inventory(string weapons[5], int armor, int ingredients, int gold);

        //setter and getters for weapons array
        string getWeapons(int index);
        void setWeaponsAt(string weapon, int index);        

        //setter and getter for total armor
        int getArmor();
        void setArmor(int armor); 

        //setter and getter for ingredients
        int getIngredients();
        void setIngredients(int ingredients);

        //setter and getter for total gold
        int getGold();
        void setGold(int gold);

        //getter for entire vector of cookware
        //we can use built in cookware functions with this vector instead of using inventory
        vector<Cookware> getCookware();
        //returns cookware obj at index
        Cookware getCookwareAt(int index);
        //adds new cookware object at end of array
        void addCookware(Cookware new_ware);

        //returns vector of treasures, see getCookware()
        vector<Treasure> getTreasures();
        //returns treasure obj at index
        Treasure getTreasureAt(int index);
        //adds new treasure obj to end of array
        void addTreasure(Treasure new_treasure);

        void setMemberAt(Member m, int index);
        Member getMemberByName(string name);
        Member getMember(int index);

        //print gold, ingredients, cookware, weapons, armor, and treasures 
        void printInv();

    private:
        string weapons_[5];
        Member party_[5];
        int armor_;
        int ingredients_;
        int gold_ = 100;
        //vector of cookware objects and treasure objects
        vector<Cookware> cookwares_;
        vector<Treasure> treasures_; 
};

#endif