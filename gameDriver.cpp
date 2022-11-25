#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include "Monster.h"
#include "Treasure.h"
#include "Map.h"
#include "Inventory.h"
#include "Cookware.h"
#define BOLDWHITE   "\033[1m\033[37m" 
#define RESET   "\033[0m"

using namespace std;
using namespace std::this_thread; 
using namespace std::chrono_literals; 

int main()
{
    Inventory game = Inventory();
    Map map;

    int sorcerer_anger = 0, rooms_cleared = 0, num_keys = 0;
    int merchant_menu = 0;

    //Gets the players name and the name of the party members and makes a member class function 
    cout << "Welcome to the dungeon grand adventurer! What is your name and the name of the party members with you?" << endl;
    for(int i = 0; i < 5; i++)
    {
        string name = "";
        cin >> name;
        Member temp(name);
        game.setMemberAt(temp, i);
    }
    game.printInv();

    cout << "Split between your party there are 100 gold pieces." << endl;
    sleep_for(.7s);
    cout << "There is a merchant that sells all sorts of goods, some things you may want to purchase are:" << endl << endl;
    sleep_for(.7s);
    cout << "- INGREDIENTS. To make food, you need to cook raw ingredients." << endl;
    sleep_for(.7s);
    cout << "- COOKWARE. If you want to cook, you need to have cookware first." << endl;
    sleep_for(.7s);
    cout << "- WEAPONS. You'll want at least one weapon per party member to fend off monsters." << endl;
    sleep_for(.7s);
    cout << "- ARMOR. Armor increases the chances of surviving a monster attack." << endl << endl;
    sleep_for(.7s);
    cout << "Your can spend all of your money if you would like to OR you can save some of your money for the adventure that awaits" << endl;
    cout << "There are more merchants along the way. But beware, some merchants in this dungeon are shady characters, and they won't always give you a fair price..." << endl << endl;
   
    //generation serves as a pause, takes some time to load, move to game title screen
    map.spawnRooms();
    map.spawnNPCs();

    cout << BOLDWHITE << "You've run into a merchant while entering the dungeon!" << RESET << endl << endl;
    sleep_for(2s);

    cout << "If you're looking for a place to buy some goods them you have come to the right place..." << endl;
    cout << "Anythings for sale with enough money" << endl << endl;
    sleep_for(2s);
    
    do
    {
        game.printInv();

        cout << "Choose one of the following" << endl;
        cout << "1. Cookware: You will need something to cook those ingredients." << endl;
        cout << "2. Ingredients: To make food, you have to cook raw ingredients. " << endl;
        cout << "3. Weapons: It's dangerous to go alone, take this!" << endl;
        cout << "4. Armor: If you want to survive monster attacks, you will need some armor." << endl;
        cout << "5. Sell treasures: If you find anything shiny, I would be happy to take it off your hands." << endl;
        cout << "6. Leave: Make sure you get everything you need, I'm leaving after this sale!" << endl;
        cin >> merchant_menu;
        
        if(merchant_menu == 1)
        {
            //define cookware objs to be added
            Cookware ceramic_pot("Ceramic Pot", 2, .25);
            Cookware frying_pan("Frying Pan", 10, .1);
            Cookware cauldron("Cauldron", 20, .02);

            int cookware_choice = 0;
            
            while(cookware_choice != 4) {
                cout << endl << endl << "I have a whole assortment of cookware, what kind would you like?" << endl;
                cout << "Each type has a different probability of breaking when used, marked with (XX%)." << endl;
                cout << "\tChoose one of the following:" << endl;
                cout << "\t1. (25%) Ceramic Pot [2 Gold]" << endl;
                cout << "\t2. (10%) Frying Pan [10 Gold]" << endl;
                cout << "\t3. (02%) Cauldron [20 Gold]" << endl;
                cout << "\t4. Exit Menu" << endl;
                cin >> cookware_choice;

                if(cookware_choice == 1 && game.getGold() >= 2)
                {
                    game.setGold(game.getGold() - 2); 
                    game.addCookware(ceramic_pot);
                }
                else if (cookware_choice == 1)
                    cout << "Insufficient Funds" << endl;

                if(cookware_choice == 2 && game.getGold() >= 10)
                {
                    game.setGold(game.getGold() - 10);
                    game.addCookware(frying_pan);
                }
                else if (cookware_choice == 2)
                    cout << "Insufficient Funds" << endl;
                    

                if(cookware_choice == 3 && game.getGold() >= 20)
                {
                    game.setGold(game.getGold() - 20);
                    game.addCookware(cauldron);
                }
                else if (cookware_choice == 3)
                    cout << "Insufficient Funds" << endl;

                if (cookware_choice < 1 || cookware_choice > 4)
                    cout << "Invalid Input" << endl;
            }

        }
        //ingredients menu
        if(merchant_menu == 2)
        {   
            int num_ingredients = -1;
            cout << endl << "I reccomend you purchase at least 10 kg of ingredients per person." << endl << endl;

            cout << "How many kg of ingredients do you need [1 Gold/kg]? (Enter a positive mulitple of 5, or 0 to cancel)" << endl;
            cin >> num_ingredients;

            while(num_ingredients < 0)
            {
                cout << "That is an invalid input. Please enter a positive number." << endl;
                cin >> num_ingredients;
            }

            if(game.getGold() >= num_ingredients && num_ingredients > 0)
            {
                game.setIngredients(game.getIngredients() + num_ingredients);
                game.setGold(game.getGold() - num_ingredients);
                cout << endl << "Success! Your party now has " << game.getIngredients() << " kg of ingredients." << endl << endl << endl;
                cout << "Thank you for your patronage! What else can I get for you?" << endl;
            }
            else
                cout << "Insufficient funds for " << num_ingredients << " ingredients." << endl;
        }
        //weapon buying menu
        //buy up to 5 weapons, first player gets first weapon, second gets second... so on
        if(merchant_menu == 3)
        {
            int weapon_choice = 0, player_index = 0; 

            cout << endl << endl << "I have a plentiful collection of weapons to choose from, what would you like?" << endl << "Note that some of them provide you a special bonus in combat, marked by a (+X).";
            sleep_for(2s);

            do {
                cout << endl << "\tChoose one of the following: " << endl;
                cout << "\t1. Stone Club [2 Gold]" << endl;
                cout << "\t2. Iron Spear [2 Gold]" << endl;
                cout << "\t3. (+1) Mythril Rapier [5 Gold]" << endl;
                cout << "\t4. (+2) Flaming Battle-Axe [15 Gold]" << endl;
                cout << "\t5. (+3) Vorpal Longsword [50 Gold]" << endl;
                cout << "\t6. Cancel" << endl;
                cin >> weapon_choice;

                if (weapon_choice == 1 && game.getGold() >= 2) {
                    game.setGold(game.getGold() - 2); 
                    game.setWeaponsAt("Stone Club", player_index);
                    cout << endl << "Success! Player: " << game.getMember(player_index).getName() << " now has a Stone Club!" << endl;
                    player_index++;
                    cout << "Thank you for your patronage! You have " << game.getGold() << " remaining gold. What else can I get for you?" << endl << endl;
                } else if (weapon_choice == 1)
                    cout << "Insufficient Funds" << endl;

                if (weapon_choice == 2 && game.getGold() >= 2) {
                    game.setGold(game.getGold() - 2); 
                    game.setWeaponsAt("Iron Spear", player_index);
                    cout << endl << "Success! Player: " << game.getMember(player_index).getName() << " now has an Iron Spear!" << endl;
                    player_index++;
                    cout << "Thank you for your patronage! You have " << game.getGold() << " remaining gold. What else can I get for you?" << endl << endl;
                } else if (weapon_choice == 2)
                    cout << "Insufficient Funds" << endl;

                if (weapon_choice == 3 && game.getGold() >= 5) {
                    game.setGold(game.getGold() - 5);
                    game.setWeaponsAt("(+1) Mythril Rapier", player_index);
                    cout << endl << "Success! Player: " << game.getMember(player_index).getName() << " now has a (+1) Mythril Rapier!" << endl;
                    player_index++;
                    cout << "Thank you for your patronage! You have " << game.getGold() << " remaining gold. What else can I get for you?" << endl << endl;
                } else if (weapon_choice == 3)
                    cout << "Insufficient Funds" << endl;

                if (weapon_choice == 4 && game.getGold() >= 15) {
                    game.setGold(game.getGold() - 15);
                    game.setWeaponsAt("(+2) Flaming Battle-Axe", player_index);
                    cout << endl << "Success! Player: " << game.getMember(player_index).getName() << " now has a (+2) Flaming Battle-Axe!" << endl;
                    player_index++;
                    cout << "Thank you for your patronage! You have " << game.getGold() << " remaining gold. What else can I get for you?" << endl << endl;
                } else if (weapon_choice == 4)
                    cout << "Insufficient Funds" << endl;
                
                if (weapon_choice == 5 && game.getGold() >= 50) {
                    game.setGold(game.getGold() - 50);
                    game.setWeaponsAt("(+3) Vorpal Longsword", player_index);
                    cout << endl << "Success! Player: " << game.getMember(player_index).getName() << " now has a (+3) Vorpal Longsword!" << endl;
                    player_index++;
                    cout << "Thank you for your patronage! You have " << game.getGold() << " remaining gold. What else can I get for you?" << endl << endl;
                } else if (weapon_choice == 5)
                    cout << "Insufficient Funds" << endl;

            } while (weapon_choice != 6 && player_index < 5);
        }

        if(merchant_menu == 4)
        {
            int armor_choice = 0;
            cout << "Each suit costs 5 gold. How many suits of armor can I get you? " << endl << "(Enter a positive integer, or 0 to cancel)" << endl;
            cin >> armor_choice;

            if (game.getGold() >= armor_choice*5) {
                 game.setArmor(armor_choice);
                 game.setGold(game.getGold() - (5*armor_choice));
                 cout << endl << "Success! Your party now has " << armor_choice << " suits of armor." << endl;
                 cout << "Thank you for your patronage! What else can I get for you?" << endl;
            }
            else if (armor_choice > 0 && armor_choice <= 5)
                cout << "Insufficient funds for " << armor_choice << " suits of armor." << endl;
            else    
                cout << "Invalid Input" << endl;
        }   
        //treasure buying option
        if(merchant_menu == 5)
        {
            cout << endl << "If you happen to have any of the following items, I'd be happy to take them off your hands." << endl << endl;
            cout << "Uh... you have no treasures, nice try! " << endl;
        }
        //leave option
        if(merchant_menu == 6)
        {
            char confirmation = 'x';
            do {
                //if user says y, set merchant menu to 13, to the terminate do-while loop
                cout << "Are you sure you're finished? You won't be able to buy anything else from me! (y/n)" << endl;
                cin >> confirmation;

                if (confirmation == 'Y' || confirmation == 'y')
                    merchant_menu = 13;
            } while (!(confirmation == 'y' || confirmation == 'Y' || confirmation == 'n' || confirmation == 'N'));
        }
    }while(merchant_menu != 13);

    game.statusUpdate(rooms_cleared, num_keys, sorcerer_anger);

    map.displayMap();
}