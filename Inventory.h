//Authors Nicolas Post and Ryan Greer 
#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <vector>
#include <array>
#include "Cookware.h"
#include "Treasure.h"
#include "Member.h"
#include "Monster.h"
using namespace std;

class Inventory {
    public:    
        Inventory();
        Inventory(string weapons[5], int armor, int ingredients, int gold);

        //setter and getters for weapons array
        string getWeapons(int index);
        void setWeaponsAt(string weapon, int index);  
        int getNumWeapons();      

        //setter and getter for total armor
        int getArmor();
        void setArmor(int armor); 
        void setMemberArmor(int index, bool armor);

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
        void removeCookware(int index);

        //returns vector of treasures, see getCookware()
        vector<Treasure> getTreasures();
        //returns treasure obj at index
        Treasure getTreasureAt(int index);
        //adds new treasure obj to end of array
        void addTreasure(Treasure new_treasure);

        void setMemberAt(Member m, int index);
        Member getMemberByName(string name);
        int getMemberIndex(string name);
        Member getMember(int index);
        int getNumMembers();
        void setMemberFullnessAt(int index, int fullness);

        //setter and getter for keys
        void setKeys(int keys);
        int getKeys();

        //setter and getter for monsters_killed
        void setMonstersKilled(int num_monsters);
        int getMonstersKilled();

        //setters and getters for dead_monster vector
        void addDeadMonster(Monster m);
        Monster getDeadMonster(string name);

        //monster fight
        bool monsterFight(Monster m);

        //print gold, ingredients, cookware, weapons, armor, and treasures 
        void printInv();
        void statusUpdate(int rooms_cleared, int keys, int anger);
        void merchantMenu(int rooms_cleared);
        int findTreausre(string t_name);

        //selects a monster to fight
        Monster monsterPick(int rooms_cleared);
        //gets misfortune calculated
        bool misfortuneCalc(int percent_chance);
        void applyMisfortune(bool in_room);
        
        Monster aliveAtLevel(int bound1, int bound2, Monster arr[21]);

        void death(Member member);

        int doorPuzzle(int choice);

        void bubbleSort(vector <int> & final_score);

        void writeGameStats(int rooms_cleared, int anger, int num_spaces, int num_turns);

    private:
        string weapons_[5];
        Member party_[5];
        int armor_;
        int ingredients_;
        int gold_ = 100;
        int keys_ = 0;
        int monsters_killed_ = 0;
        //vector of cookware objects and treasure objects
        vector<Cookware> cookwares_;
        vector<Treasure> treasures_; 

        //vector of dead monsters for spawning reference
        vector<Monster> dead_monsters_;
};

#endif