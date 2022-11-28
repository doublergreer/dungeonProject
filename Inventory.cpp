//Authors Nicolas Post and Ryan Greir 
#include <iostream>
#include <iostream>
#include <chrono>
#include <thread>
// #include "Member.h"
#include "Inventory.h"
#include "Cookware.h"
#include "Treasure.h"
#include "Monster.h"
#include "Map.h"

using namespace std;
using namespace std::this_thread; 
using namespace std::chrono_literals; 

Inventory::Inventory()
{
    for(int i = 0; i < 5; i++)
    {
        weapons_[i] = "";
    }

    armor_ = 0;
    ingredients_ = 0;
}

Inventory::Inventory(string weapons[5], int armor, int ingredients, int gold)
{
    for(int i = 0; i < 5; i++)
    {
        weapons_[i] = weapons[i];
    }

    armor_ = armor;
    ingredients_ = ingredients;
    gold_ = gold;
}

string Inventory::getWeapons(int index)
{
    return weapons_[index];
}
void Inventory::setWeaponsAt(string weapon, int index)
{
    weapons_[index] = weapon;
}

int Inventory::getArmor()
{
    return armor_;
}

void Inventory::setArmor(int armor)
{
    armor_ = armor;
}

int Inventory::getIngredients()
{
    return ingredients_;
}

void Inventory::setIngredients(int ingredients)
{
    ingredients_ = ingredients;
}

int Inventory::getGold()
{
    return gold_;
}

void Inventory::setGold(int gold)
{
    gold_ = gold;
}

vector<Cookware> Inventory::getCookware() {
    return cookwares_;
}
Cookware Inventory::getCookwareAt(int index) {
    return cookwares_.at(index);
}
void Inventory::addCookware(Cookware new_ware) {
    cookwares_.push_back(new_ware);
}

vector<Treasure> Inventory::getTreasures() {
    return treasures_;
}
Treasure Inventory::getTreasureAt(int index) {
    return treasures_.at(index);
}
void Inventory::addTreasure(Treasure new_treasure) {
    treasures_.push_back(new_treasure);
}

void Inventory::setMemberAt(Member m, int index) {
    party_[index] = m;
}
//returns member with said name unless it does not exist, else return blank member
Member Inventory::getMemberByName(string name) {
    for (int i = 0; i < 5; i++) {
        if (party_[i].getName() == name) {
            return party_[i];
        }
    }
    return Member();
}
Member Inventory::getMember(int index) {
    return party_[index];
}

void Inventory::printInv() {
    cout << "________________________________________" << endl;
    cout << "INVENTORY:" << endl;
    cout << "\tGold: " << gold_ << endl;
    cout << "\tIngredients: " << ingredients_ << " kg"  << endl;
    cout << "\tCookware: ";
    for (int i = 0; i < cookwares_.size(); i++)
        cout << cookwares_.at(i).getName() << "\t";
    cout << endl << endl;

    cout << "\tWeapons:" << endl;

    for (int i = 0; i < 5; i++) 
        cout << "\t\t" << party_[i].getName() << ": " << weapons_[i] << endl;
    
    cout << "\tArmor: " << armor_ << endl;

    cout << "\tTreasures: ";
    for (int i = 0; i < treasures_.size(); i++)
        cout << treasures_.at(i).getName() << "\t";
    cout << endl << "________________________________________" << endl;
}

//print status each turn
void Inventory::statusUpdate(int rooms_cleared, int keys, int anger) {
    cout << "________________________________________" << endl;
    cout << "STATUS:" << endl;
    cout << "\tRooms Cleared: " << rooms_cleared << " | Keys: " << keys << " | Anger Level: " << anger << endl;
    sleep_for(1.5s);
    printInv();
    sleep_for(1.5s);
    cout << "PARTY:" << endl;

    for (int i = 0; i < 5; i++) 
        cout << "\t" << party_[i].getName() << "\t| Fullness: " << party_[i].getFullness() << endl;
    cout << "________________________________________" << endl;
    sleep_for(2s);
}

//monster fight 
//random num generator in miscFunctions.cpp
bool Inventory::monsterFight(Monster m) 
{
    int num_weapons = 0;
    int add_1 = 0;
    int add_2 = 0;
    int add_3 = 0;

    for (int i = 0; i < 5; i++)
    {
        if(weapons_[i] != "")
        {
            if(weapons_[i].substr(0,4) == "(+1)")
            {
                add_1++;
            }
            if(weapons_[i].substr(0,4) == "(+2)")
            {
                add_2++;
            } 
            if(weapons_[i].substr(0,4) == "(+3)")
            {
                add_3++;
            }
            num_weapons++;
        }
    }

    int weapon_stats = 0; 

    weapon_stats = num_weapons + add_1 + add_2 + add_3;

    int diff_weapon = 0;
    int diff_bonus = 0;

    for (int i = 0; i < 5; i++)
    {
        if (weapons_[i] != weapons_[0] && weapons_[i] != weapons_[1] && weapons_[i] != weapons_[2] && weapons_[i] != weapons_[3] && weapons_[i] != weapons_[4]) 
        {
            diff_weapon++;
        }
    }

    if (diff_weapon >= num_weapons) 
    {
        diff_bonus = 4;
    }
    else
    {
        diff_bonus = 0;
    }

    Map random;

    //generate random numbers
    int r1 = random.randomNum(1, 6);
    int r2 = random.randomNum(1, 6);

    //actual calculation of the monster fight
    int monster_fight = (r1 * weapon_stats + diff_bonus) - ((r2 * m.getChallengeRating()) / armor_);

    if(monster_fight > 0)
    {
        return true;
    }
    //else if(monster_fight <= 0)
    //{
        return false;
    //}
}


