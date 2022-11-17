#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
// #include "Member.h"
#include "Monster.h"
#include "Treasure.h"
#include "Map.h"
#include "Inventory.h"
#include "Cookware.h"
#define BOLDWHITE   "\033[1m\033[37m" 

using namespace std;

int main()
{
    string name = "";
    Inventory game = Inventory();
    int sorcerer_anger = 0;

    //Gets the players name and the name of the party members and makes a member class function 
    cout << "Welcome to the dungeon grand adventurer! What is your name and the name of the party members with you?" << endl;
    for(int i = 0; i < 5; i++)
    {
        cin >> name;
        Member temp(name);
        game.setMemberAt(temp, i);
    }
    game.printInv();

    cout << "Split between the party there is 100 gold pieces." << endl;
    cout << "There is a mearchent that sells all sorts of goods, some things you might want to purchase are:" << endl << endl;
    cout << "- INGREDIENTS. To make food, you have to cook raw ingredients." << endl;
    cout << "- COOKWARE. If you want to cook, you have to have cookware first." << endl;
    cout << "- WEAPONS. You'll want at least one weapon per party member to fend off monsters." << endl;
    cout << "- ARMOR. Armor increases the chances of surviving a monster attack." << endl << endl;
    cout << "Your can spend all of your money here if you would like to OR you can save some of your money for the adventure that awaits" << endl << endl;

    cout << BOLDWHITE "You run into a merchant "
















    
}