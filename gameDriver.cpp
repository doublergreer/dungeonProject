#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <fstream>
#include "Monster.h"
#include "Treasure.h"
#include "Map.h"
#include "Inventory.h"
#include "Cookware.h"
#include "Leaderboard.h"
#include "miscFunctions.cpp"
#define BOLDWHITE   "\033[1m\033[37m" 
#define BOLDRED     "\033[1m\033[31m"
#define RESET   "\033[0m"

using namespace std;
using namespace std::this_thread; 
using namespace std::chrono_literals; 

int main()
{
    //initializers and whatnot
    Inventory game = Inventory();
    Map map;
    

    //treasure objects
    Treasure silver_ring("Silver Ring", 10);
    Treasure ruby_necklace("Ruby Necklace", 20);
    Treasure emerald_bracelet("Emerald Bracelet", 30);
    Treasure diamond_circlet("Diamond Circlet", 40);
    Treasure gem_goblet("Gem-encrusted Goblet", 50);

    string riddles[20][2];
    readRiddles("riddles.txt", riddles, 20);

    int sorcerer_anger = 0, rooms_cleared = 0, spaces_explored = 0;

    ifstream file;
    string lines = "";

    file.open("dungeonEscape.txt");

    if(file.is_open())
    {
        while (!file.eof())
        {
            getline(file, lines);
            cout << BOLDWHITE << lines << RESET << endl;
        }
    }
    file.close();

    cout << endl << endl << "\t\tLOADING..." << endl;
    map.spawnRooms();

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

    //intro
    cout << "Split between your party there are 100 gold pieces." << endl;
    sleep_for(1.5s);
    cout << "There is a merchant that sells all sorts of goods, some things you may want to purchase are:" << endl << endl;
    sleep_for(.1s);
    cout << "- INGREDIENTS. To make food, you need to cook raw ingredients." << endl;
    sleep_for(.7s);
    cout << "- COOKWARE. If you want to cook, you need to have cookware first." << endl;
    sleep_for(.7s);
    cout << "- WEAPONS. You'll want at least one weapon per party member to fend off monsters." << endl;
    sleep_for(.7s);
    cout << "- ARMOR. Armor increases the chances of surviving a monster attack." << endl << endl;
    sleep_for(.1s);
    cout << "Your can spend all of your money if you would like to OR you can save some of your money for the adventure that awaits" << endl;
    cout << "There are more merchants along the way. But beware, some merchants in this dungeon are shady characters, and they won't always give you a fair price..." << endl << endl;
   
    //generation serves as a pause, takes some time to load, move to game title screen
    map.spawnNPCs();

    cout << BOLDWHITE << "You've run into a merchant while entering the dungeon!" << RESET << endl << endl;
    sleep_for(2s);

    cout << "If you're looking for a place to buy some goods them you have come to the right place..." << endl;
    cout << "Anythings for sale with enough money" << endl << endl;
    sleep_for(2s);
    
    int merchant_menu = 0;


    //merchant loop
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
        
        //cookware
        if(merchant_menu == 1)
        {
            //define cookware objs to be added
            Cookware ceramic_pot("Ceramic Pot", 2, .25);
            Cookware frying_pan("Frying Pan", 10, .1);
            Cookware cauldron("Cauldron", 20, .02);

            int cookware_choice = 0;
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
                cout << "Insufficient Funds" << endl << "No items were purchased. Try again." << endl;

            if(cookware_choice == 2 && game.getGold() >= 10)
            {
                game.setGold(game.getGold() - 10);
                game.addCookware(frying_pan);
            }
            else if (cookware_choice == 2)
                cout << "Insufficient Funds" << endl << "No items were purchased. Try again." << endl;
                

            if(cookware_choice == 3 && game.getGold() >= 20)
            {
                game.setGold(game.getGold() - 20);
                game.addCookware(cauldron);
            }
            else if (cookware_choice == 3)
                cout << "Insufficient Funds" << endl << "No items were purchased. Try again." << endl;

            if (cookware_choice < 1 || cookware_choice > 4)
                cout << "Invalid Input" << endl;

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
                    cout << "Insufficient Funds" << endl << "No items were purchased. Try again." << endl;

                else if (weapon_choice == 2 && game.getGold() >= 2) {
                    game.setGold(game.getGold() - 2); 
                    game.setWeaponsAt("Iron Spear", player_index);
                    cout << endl << "Success! Player: " << game.getMember(player_index).getName() << " now has an Iron Spear!" << endl;
                    player_index++;
                    cout << "Thank you for your patronage! You have " << game.getGold() << " remaining gold. What else can I get for you?" << endl << endl;
                } else if (weapon_choice == 2)
                    cout << "Insufficient Funds" << endl << "No items were purchased. Try again." << endl;

                else if (weapon_choice == 3 && game.getGold() >= 5) {
                    game.setGold(game.getGold() - 5);
                    game.setWeaponsAt("(+1) Mythril Rapier", player_index);
                    cout << endl << "Success! Player: " << game.getMember(player_index).getName() << " now has a (+1) Mythril Rapier!" << endl;
                    player_index++;
                    cout << "Thank you for your patronage! You have " << game.getGold() << " remaining gold. What else can I get for you?" << endl << endl;
                } else if (weapon_choice == 3)
                    cout << "Insufficient Funds" << endl << "No items were purchased. Try again." << endl;

                else if (weapon_choice == 4 && game.getGold() >= 15) {
                    game.setGold(game.getGold() - 15);
                    game.setWeaponsAt("(+2) Flaming Battle-Axe", player_index);
                    cout << endl << "Success! Player: " << game.getMember(player_index).getName() << " now has a (+2) Flaming Battle-Axe!" << endl;
                    player_index++;
                    cout << "Thank you for your patronage! You have " << game.getGold() << " remaining gold. What else can I get for you?" << endl << endl;
                } else if (weapon_choice == 4)
                    cout << "Insufficient Funds" << endl << "No items were purchased. Try again." << endl;
                
                else if (weapon_choice == 5 && game.getGold() >= 50) {
                    game.setGold(game.getGold() - 50);
                    game.setWeaponsAt("(+3) Vorpal Longsword", player_index);
                    cout << endl << "Success! Player: " << game.getMember(player_index).getName() << " now has a (+3) Vorpal Longsword!" << endl;
                    player_index++;
                    cout << "Thank you for your patronage! You have " << game.getGold() << " remaining gold. What else can I get for you?" << endl << endl;
                } else if (weapon_choice == 5)
                    cout << "Insufficient Funds" << endl << "No items were purchased. Try again." << endl;
                else
                    cout << endl << "Invalid Input. Try again" << endl;

            } while (weapon_choice != 6 && player_index < 5);
        }
        //armor menu
        if(merchant_menu == 4)
        {
            int armor_choice = 0;
            cout << "Each suit costs 5 gold. How many suits of armor can I get you? " << endl << "(Enter a positive integer, or 0 to cancel)" << endl;
            cin >> armor_choice;

            if (game.getGold() >= armor_choice*5) {
                //assign armor to indivivual members
                for (int i = 0; i < armor_choice && game.getArmor() <= 5;) {
                    if (!(game.getMember(i).getArmor())) {
                        game.setMemberArmor(i, true);
                        i++;
                    }
                 }
                 game.setArmor(armor_choice + game.getArmor());
                 game.setGold(game.getGold() - (5*armor_choice));
                 cout << endl << "Success! Your party now has " << armor_choice << " suits of armor." << endl;
                 cout << "Thank you for your patronage! What else can I get for you?" << endl;
            }
            else if (armor_choice > 0 && armor_choice <= 5)
                cout << "Insufficient funds for " << armor_choice << " suits of armor." << endl;
            else if (armor_choice < 0)  
                cout << "Invalid Input" << endl;
            else if (armor_choice > 5)
                cout << "You only have 5 players... where are the extra suits going?" << endl << "No suits were purchased. Try again." << endl;
                sleep_for(2s);
        }   
        //treasure buying option
        if(merchant_menu == 5)
        {
            cout << endl << "If you happen to have any of the following items, I'd be happy to take them off your hands." << endl << endl;
            sleep_for(1s);
            cout << "Uh... you have no treasures, nice try! " << endl;
            sleep_for(2s);
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

    int num_turns = 1;
    bool quit = false, exit = false;
    bool enough_players = true;
    //action loop
    do {
        game.statusUpdate(rooms_cleared, game.getKeys(), sorcerer_anger);
        cout << endl;
        sleep_for(.5s);
        map.displayMap();

        //if space is an npc space display npc menu
        if (map.isNPCLocation(map.getPlayerRow(), map.getPlayerCol())) {
            int npc_menu = 0; 
            cout << BOLDWHITE << "Turn " << num_turns << RESET;
            cout << endl << endl << BOLDWHITE << "\tAN NPC OCCUPIES YOUR CURRENT SPACE! HOW WILL YOU PROCEED?" << endl << RESET;
            cout << endl << "NPC SPACE ACTIONS:" << endl;
            cout << "\t1. Move Away: 1 space in any of the cardinal directions" << endl;
            cout << "\t2. Speak to NPC" << endl;
            cout << "\t3. Give Up: accept the dungeon as your new home" << endl;
            cin >> npc_menu;

            if (npc_menu == 1) {
                map.printMoveMenu();
                //call misfortune calculator
                bool misfortune_check = game.misfortuneCalc(20);
                if(misfortune_check == true)
                {
                    cout << endl << "\tUnlucky! Each player lost one fullness point." << endl << endl;
                    for(int i = 0; i < 5; i++)
                    {
                        //remove one fullness from each player
                        if (game.getMember(i).getName().length() > 0) {
                            game.setMemberFullnessAt(i, game.getMember(i).getFullness() - 1);
                        }
                    }
                }
                if (!(map.isExplored(map.getPlayerRow(), map.getPlayerCol())) || map.isDungeonExit(map.getPlayerRow(), map.getPlayerCol()) || map.isRoomLocation(map.getPlayerRow(), map.getPlayerCol()) || map.isNPCLocation(map.getPlayerRow(), map.getPlayerCol())) {
                    sorcerer_anger++;
                }
                num_turns++;
            }
            //talk to npc
            if (npc_menu == 2) {
                //maybe make npc dialogue look different from reguylar text
                cout << "Hello Travelers. How may I help you today?" << endl;
                sleep_for(.5s);
                cout << "\t" << game.getMember(0).getName() << ": Hi, we were looking to purchase some goods." << endl;
                sleep_for(1.5s);
                cout << "The good news is, I happen to have some goods." << endl;
                sleep_for(2s);
                cout << "The bad news is that you need to solve a puzzle in order to use my services..." << endl;
                sleep_for(3s);

                //get random riddle from array
                int r = map.randomNum(0, 19);
                cout << "Here is your riddle: " << endl << "\t" << riddles[r][0] << endl;
                string answer;
                cin >> answer;

                //correct answer
                if (answer == riddles[r][1]) {
                    //open the menu
                    sleep_for(1s);
                    cout << endl << "Well... that was alright I guess." << endl << endl << "Here are my offerings:" << endl << endl;
                    sleep_for(1s);
                    game.merchantMenu(rooms_cleared);
                }
                //incorrect answer
                else {
                    //spawn a monster n say something mean
                    sleep_for(1s);
                    cout << "I am sorry but that is incorrect, the correct answer was: " << riddles[r][1] << endl << "Now you must suffer the consequences for your lack of intellegence." << endl << endl;
                    sleep_for(1s);
                    Monster monster = game.monsterPick(rooms_cleared);
                    
                    //make sure monster exists
                    if (monster.getMonsterName() != "error") {    //introduce monster
                        cout << "OH NO! a " << monster.getMonsterName() << " appeared right infront of you. Escaping it will be difficult." << endl;
                        sleep_for(1s);

                        int fight_menu = 0;
                        cout << endl << "You now have two options..." << endl;
                        cout << "\t1) Attack: this can go well if you are well equipped with weapons and armor" << endl;
                        cout << "\t2) Surrender: leave one of your party members behind and flee the scene" << endl;
                        cin >> fight_menu;

                        while (fight_menu != 1 && fight_menu != 2) {
                            cout << endl << "Invalid Input, please try again." << endl;
                            cin >> fight_menu;
                        }


                        if (fight_menu == 1 && game.getNumWeapons() > 0) {    
                            //attack
                            if (game.monsterFight(monster)) {
                                cout << endl << "\tYou and your party have managed to win the fight with " << monster.getMonsterName() << ". Congratulations!" << endl; 
                            } else if (game.getNumWeapons() <= 0) {
                                cout << endl << "Your party has no weapons. You must now surrender." << endl;
                                fight_menu = 2;
                            }
                        }

                        if (fight_menu == 2) {
                            if (game.getNumMembers() >= 1) {
                                //surrender
                                //pick random member
                                r = map.randomNum(1,4);

                                //checks that random party member isnt already dead
                                while (!(game.getMember(r).getName().length() > 0)) {
                                    r = map.randomNum(1, 4);
                                }
                                cout << endl << "You have chosen to surrender " << game.getMember(r).getName() << ". Hope it was worth it." << endl;
                                game.death(game.getMember(r));
                                cout << "The remainder of your party has escaped the monster to fight another day." << endl;
                            }
                        }
                        //monster misfortune
                    }
                    else {
                        cout << endl << "Looks like there are no monsters left at this level... Clear another room to fight higher level monsters." << endl;
                    }

                    //monster hunger
                    //no matter outcome of monster battle 
                    bool misfortune_check = game.misfortuneCalc(50);
                    if(misfortune_check == true)
                    {
                        cout << endl << "\tUnlucky! Each player lost one fullness point after the encounter." << endl << endl;
                        for(int i = 0; i < 5; i++)
                        {
                            //remove one fullness from each player
                            if (game.getMember(i).getName().length() > 0) {
                                game.setMemberFullnessAt(i, game.getMember(i).getFullness() - 1);
                            }
                        }
                    }
                }
                num_turns++;
                map.removeNPC(map.getPlayerRow(), map.getPlayerCol());
                spaces_explored++;
            }
            if(npc_menu == 3)
            {
                cout << "You give up on your adventure? I saw this coming too, what a shame." << endl;
                //write game stats to a seperate file to then keep track of leaderboard
                quit = true;
            }
        }
        //if space is room, display room menu
        else if (map.isRoomLocation(map.getPlayerRow(), map.getPlayerCol())) {
            int room_menu = 0; 
            cout << endl << endl << BOLDWHITE << "\tYOUR CURRENT SPACE IS A ROOM! HOW WILL YOU PROCEED?" << endl << RESET;
            cout << BOLDWHITE << "Turn " << num_turns << RESET;
            cout << endl << "ROOM ACTIONS:" << endl;
            cout << "\t1. Move: 1 space in any of the cardinal directions" << endl;
            cout << "\t2. Open the door: having a key helps..." << endl;
            cout << "\t3. Give Up: accept the dungeon as your new home" << endl;
            cin >> room_menu;

            if (room_menu == 1) {
                map.printMoveMenu();
                //call misfortune calculator
                bool misfortune_check = game.misfortuneCalc(20);
                if(misfortune_check == true)
                {
                    cout << endl << "\tUnlucky! Each player lost one fullness point." << endl << endl;
                    for(int i = 0; i < 5; i++)
                    {
                        //remove one fullness from each player
                        if (game.getMember(i).getName().length() > 0) {
                            game.setMemberFullnessAt(i, game.getMember(i).getFullness() - 1);
                        }
                    }
                }
                if (!(map.isExplored(map.getPlayerRow(), map.getPlayerCol())) || map.isDungeonExit(map.getPlayerRow(), map.getPlayerCol()) || map.isRoomLocation(map.getPlayerRow(), map.getPlayerCol()) || map.isNPCLocation(map.getPlayerRow(), map.getPlayerCol())) {
                    sorcerer_anger++;
                }
                num_turns++;
            }
            if (room_menu == 2) {
                if (game.getKeys() > 0) {
                    bool in_room = true;
                    game.setKeys(game.getKeys() - 1);

                    // if (rooms_cleared == 4) {
                    //     file.open("wizardImage.txt");

                    //     if(file.is_open())
                    //     {
                    //         while (!file.eof())
                    //         {
                    //             getline(file, lines);
                    //             cout << BOLDWHITE << lines << RESET << endl;
                    //         }
                    //     }
                    //     file.close();
                    // }

                    //pick monster 2 levels higher
                    Monster m = game.monsterPick(rooms_cleared + 1);
                    //fight monster 
                    cout << endl << "There is a " << m.getMonsterName() << " inside this room. You and your team will have to fight it." << endl;
                    bool win = game.monsterFight(m);

                    if (win) {
                        rooms_cleared++;
                        cout << endl << endl << "Congratulations, you have defeated the monster and cleared room " << rooms_cleared << "!" << endl;
                        if(game.misfortuneCalc(60)) {
                            game.applyMisfortune(in_room);
                        }
                        map.removeRoom(map.getPlayerRow(), map.getPlayerCol());
                        spaces_explored++;
                    }
                    else {
                        cout << endl << endl << "Your team failed to defeat the monster." << endl << "You have been kicked out of the room. In order to clear the room you must find another key." << endl;
                        //monster fighting consequence
                        if(game.misfortuneCalc(40)) {
                            game.applyMisfortune(in_room);
                        }
                    }
                } else 
                {
                    int game_choice = 0;
                    int num_lose = 0;

                    cout << "You have attempted to get inside a room without a key, and as a result you have fallen into a trap." << endl << "In order to get out, you must win a game of boulder, parchment, shears." << endl << "If you lose three times, you will suffer the consequences of your foolishness." << endl << endl;
                    cout << "Pick one option:" << endl;
                    cout << "\t1. Boulder" << endl;
                    cout << "\t2. Shears" << endl;
                    cout << "\t3. Parchment" << endl;
                    cin >> game_choice;

                    int result = game.doorPuzzle(game_choice);
    
                    while(result == 0 && num_lose < 3)
                    {
                        cout << "tie" << endl;
                        cout << "enter choice " << endl;
                        cout << "1. Boulder" << endl;
                        cout << "2. Shears" << endl;
                        cout << "3. Parchment" << endl;
                        cin >> game_choice;
                        result = game.doorPuzzle(game_choice); 
                    }
                    while(result == -1 && num_lose < 3)
                    {
                        num_lose++;
                        cout << "lost" << endl;
                        cout << "How many times you lost: " << num_lose << endl << endl;
                        cout << "enter choice " << endl;
                        cout << "1. Boulder" << endl;
                        cout << "2. Shears" << endl;
                        cout << "3. Parchment" << endl;
                        cin >> game_choice;
                        result = game.doorPuzzle(game_choice); 
                
                    }
                    if(result == 1 && num_lose <= 3)
                    {
                        cout << "won" << endl;
                    }
                    if(result == 3)
                    {
                        cout << "you are dead" << endl;
                    }
                
                    if (num_lose >= 3) {
                        //play rpc
                        int r = map.randomNum(1, 4);

                        cout << endl << BOLDWHITE << "\tUNLUCKY... YOU LOST 3 TIMES" << RESET << endl;

                        //checks that random party member isnt already dead
                        while (!(game.getMember(r).getName().length() > 0)) {
                            r = map.randomNum(1, 4);
                        }

                        cout << endl << game.getMember(r).getName() << " has passed away due to " << game.getMember(0).getName() << "'s  lack of finesse. "<< endl; 
                        game.death(game.getMember(r));   
                        
                    }
                }
            }
            if (room_menu == 3) {
                quit = true;
            }
        }
        //else display normal action menu
        else {  
            int action_menu = 0; 
            cout << BOLDWHITE << "Turn " << num_turns << RESET;
            cout << endl << "ACTIONS:" << endl;
            cout << "\t1. Move: 1 space in any of the cardinal directions" << endl;
            cout << "\t2. Investigate: your current space" << endl;
            cout << "\t3. Pick a fight: cause a random monster to appear" << endl;
            cout << "\t4. Cook and Eat: use ingredients to increase fullness" << endl;
            cout << "\t5. Give Up: accept the dungeon as your new home" << endl;
            cin >> action_menu;

            if (action_menu == 1) {
                map.printMoveMenu();
                num_turns++;
                //call misfortune calculator
                bool misfortune_check = game.misfortuneCalc(20);
                if(misfortune_check == true)
                {
                    cout << endl << "\tUnlucky! Each player lost one fullness point." << endl << endl;
                    for(int i = 0; i < 5; i++)
                    {
                        //remove one fullness from each player
                        game.setMemberFullnessAt(i, game.getMember(i).getFullness() - 1);
                    }
                }
                if (!(map.isExplored(map.getPlayerRow(), map.getPlayerCol())) || map.isDungeonExit(map.getPlayerRow(), map.getPlayerCol()) || map.isRoomLocation(map.getPlayerRow(), map.getPlayerCol()) || map.isNPCLocation(map.getPlayerRow(), map.getPlayerCol())) {
                    sorcerer_anger++;
                }
            }

            if (action_menu == 2) {
                if (!(map.isExplored(map.getPlayerRow(), map.getPlayerCol()))) {
                    cout << endl << endl << "\tWould you like to explore the current space?" << endl;
                    cout << "\t\tOutcomes: (only one can occur)" << endl;
                    cout << "\t\t10 percent chance you find a key" << endl;
                    cout << "\t\t20 percent chance you find a treasure" << endl;
                    cout << "\t\t20 percent chance a random monster spawns" << endl;
                    cout << endl << "\tAfter Investigating: 50 percent chance each member's fullness drops by 1" << endl;
                    
                    char explore;

                    cout << endl << "y/n?\t";
                    cin >> explore;

                    while (explore != 'y' && explore != 'n') {
                        cout << "Please enter a valid input:\t";
                        cin >> explore;
                    }

                    if (explore == 'y') {
                        //run odds and stuff
                        int exploreChance = map.randomNum(0,100);
                        if (exploreChance >= 0 && exploreChance <= 10) {
                            //bold this
                            cout << endl << BOLDWHITE << "\tYour party has found a key!" << RESET << endl << endl;
                            game.setKeys(game.getKeys() + 1);
                        }
                        else if (exploreChance > 10 && exploreChance <= 30) {
                            cout << endl << BOLDWHITE << "\tYour party has found a Treasure!" << RESET << endl << endl;
                            
                            //adjusting all treasures by -1
                            //e.g. this was supposed to be 1 room cleared, but that makes no sense
                            if (rooms_cleared == 0) {
                                game.addTreasure(silver_ring);
                                cout << BOLDWHITE << "\t" << silver_ring.getName() << " has been added to your inventory." << RESET << endl << endl;
                            }
                            if (rooms_cleared == 1) {
                                game.addTreasure(ruby_necklace);
                                cout << BOLDWHITE << "\t" << ruby_necklace.getName() << " has been added to your inventory." << RESET << endl << endl;
                            }
                            if (rooms_cleared == 2) {
                                game.addTreasure(emerald_bracelet);
                                cout << BOLDWHITE << "\t" << emerald_bracelet.getName() << " has been added to your inventory." << RESET << endl << endl;
                            }
                            if (rooms_cleared == 3) {
                                game.addTreasure(diamond_circlet);
                                cout << BOLDWHITE << "\t" << diamond_circlet.getName() << " has been added to your inventory." << RESET << endl << endl;
                            }
                            if (rooms_cleared >= 4) {
                                game.addTreasure(gem_goblet);
                                cout << BOLDWHITE << "\t" << gem_goblet.getName() << " has been added to your inventory." << RESET << endl << endl;
                            }
                        }
                        else if (exploreChance > 30 && exploreChance <= 50) {
                            //fight random monster
                            Monster m = game.monsterPick(rooms_cleared);
                            //make sure monster exists
                            if (m.getMonsterName() != "error" && m.getMonsterName().length() > 0) {
                                cout << "OH NO! a " << m.getMonsterName() << " is occupying this space. You have two options: "<< endl;
                                sleep_for(1s);

                                int fight_menu = 0;
                                cout << endl << "You now have two options..." << endl;
                                cout << "\t1) Attack: this can go well if you are well equipped with weapons and armor" << endl;
                                cout << "\t2) Surrender: leave one of your party members behind and flee the scene" << endl;
                                cin >> fight_menu;

                                while (fight_menu != 1 && fight_menu != 2) {
                                    cout << endl << "Invalid Input, please try again." << endl;
                                    cin >> fight_menu;
                                }


                                if (fight_menu == 1 && game.getNumWeapons() > 0) {    
                                    //attack
                                    if (game.monsterFight(m)) {
                                        cout << endl << "\tYou and your party have managed to win the fight with " << m.getMonsterName() << ". Congratulations!" << endl; 
                                    } else if (game.getNumWeapons() <= 0) {
                                        cout << endl << "Your party has no weapons. You must now surrender." << endl;
                                        fight_menu = 2;
                                    }
                                }

                                if (fight_menu == 2) {
                                    if (game.getNumMembers() >= 1) {
                                        //surrender
                                        //pick random member
                                        int r = map.randomNum(1,4);

                                        //checks that random party member isnt already dead
                                        while (!(game.getMember(r).getName().length() > 0)) {
                                            r = map.randomNum(1, 4);
                                        }
                                        cout << endl << "You have chosen to surrender " << game.getMember(r).getName() << ". Hope it was worth it." << endl;
                                        game.death(game.getMember(r));
                                        cout << "The remainder of your party has escaped the monster to fight another day." << endl;
                                    }
                                }
                            }
                            else {
                                cout << endl << "Looks like there are no monsters left at this level... Clear another room to fight higher level monsters." << endl;
                            }
                        }   
                        
                        else {
                            cout << endl << "The space appears to be empty..." << endl;
                        }
                        map.exploreSpace(map.getPlayerRow(), map.getPlayerCol());
                        spaces_explored++;
                        //incremenent num_turns for each action taken, otherwise pretend turn didnt happen and display menu again
                        num_turns++;
                    }
                } else
                    cout << endl << "This space has already been investiaged." << endl;
            }

            if (action_menu == 3) {
                //pick random monster
                Monster monster = game.monsterPick(rooms_cleared);
                //make sure monster exists
                if (monster.getMonsterName() != "error") {    //introduce monster
                    cout << "OH NO! a " << monster.getMonsterName() << " appeared right infront of you. Escaping it will be difficult." << endl;
                    sleep_for(1s);

                    int fight_menu = 0;
                    cout << endl << "You now have two options..." << endl;
                    cout << "\t1) Attack: this can go well if you are well equipped with weapons and armor" << endl;
                    cout << "\t2) Surrender: leave one of your party members behind and flee the scene" << endl;
                    cin >> fight_menu;

                    while (fight_menu != 1 && fight_menu != 2) {
                        cout << endl << "Invalid Input, please try again." << endl;
                        cin >> fight_menu;
                    }


                    if (fight_menu == 1 && game.getNumWeapons() > 0) {    
                        //attack
                        if (game.monsterFight(monster)) {
                            cout << endl << "\tYou and your party have managed to win the fight with " << monster.getMonsterName() << ". Congratulations!" << endl; 
                        } else if (game.getNumWeapons() <= 0) {
                            cout << endl << "Your party has no weapons. You must now surrender." << endl;
                            fight_menu = 2;
                        }
                    }

                    if (fight_menu == 2) {
                        if (game.getNumMembers() >= 1) {
                            //surrender
                            //pick random member
                            int r = map.randomNum(1,4);

                            //checks that random party member isnt already dead
                            while (!(game.getMember(r).getName().length() > 0)) {
                                r = map.randomNum(1, 4);
                            }
                            cout << endl << "You have chosen to surrender " << game.getMember(r).getName() << ". Hope it was worth it." << endl;
                            game.death(game.getMember(r));
                            cout << "The remainder of your party has escaped the monster to fight another day." << endl;
                        }
                    }
                }
                else {
                    cout << endl << "Looks like there are no monsters left at this level... Clear another room to fight higher level monsters." << endl;
                }
                //monster hunger
                //no matter outcome of monster battle 
                bool misfortune_check = game.misfortuneCalc(50);
                if(misfortune_check == true)
                {
                    cout << endl << "\tUnlucky! Each player lost one fullness point after the encounter." << endl << endl;
                    for(int i = 0; i < 5; i++)
                    {
                        //remove one fullness from each player
                        game.setMemberFullnessAt(i, game.getMember(i).getFullness() - 1);
                    }
                }
            }

            if (action_menu == 4)
            {
                int num_ingredients = 0;
                int cookware_choice = 0;
                bool success = false;
                do
                {
                    cout << "How many kg of ingredients would you like to use? (must be in increments of 5kg) " << endl;
                    cin >> num_ingredients;

                    while(num_ingredients % 5 != 0)
                    {
                        cout << "Please enter a multiple of 5." << endl;
                        cin >> num_ingredients;
                    }
                    if(num_ingredients < 5)
                    {
                        cout << "You need at least 5 ingredients to cook anything." << endl;
                    }
                    while(num_ingredients > game.getIngredients())
                    {
                        cout << "You don't have enough ingredients for that big of a meal." << endl;
                        cout << "Enter a smaller amount of ingredients. " << endl;
                        cin >> num_ingredients;
                    }
                    
                    if(game.getCookware().size() > 0)
                    {
                        cout << "Which cookware would you like to use?" << endl;
                        for(int i = 0; i < game.getCookware().size(); i++)
                        {
                           cout << i+1 << ") " << game.getCookwareAt(i).getName() << endl;   
                        }
                        cin >> cookware_choice;
                        while(cookware_choice > game.getCookware().size() || cookware_choice < 1)
                        {
                            cout << "Invalid Input. Please pick again." << endl;
                            cin >> cookware_choice;
                        }

                        cout << endl << "Success! Your party has been fed!" << endl;
                        success = true;
                        int new_fullness = 0;
                        new_fullness = num_ingredients / 5;
                        game.setIngredients(game.getIngredients() - num_ingredients);

                        for(int i = 0; i < 5; i++)
                        {
                            if(game.getMember(i).getFullness() + new_fullness <= 50) {
                            game.setMemberFullnessAt(i, new_fullness + game.getMember(i).getFullness());
                            }
                            else if(game.getMember(i).getFullness() + new_fullness > 50) {
                            game.setMemberFullnessAt(i, 50);
                            }
                        }
                    }
                    

                } while(num_ingredients >= 5 && game.getCookware().size() > 0 && !success);

                if (success == true) {
                    if (game.misfortuneCalc(game.getCookwareAt(cookware_choice-1).getBreakChance())) {
                        cout << endl << "Unlucky... your "<< game.getCookwareAt(cookware_choice-1).getName() << " has broken." << endl;
                        game.removeCookware(cookware_choice-1);
                    }
                }

                num_turns++;

                
            }
        

            if (action_menu == 5) {
                quit = true;
            }
        }

        for (int i = 0; i < 4; i++) {
            if (game.getMember(i).getFullness() <= 0 && game.getMember(i).getName().length() > 0) {
                cout << endl << game.getMember(i).getName() << " has died of starvation. Rest In Peace." << endl;
                game.death(game.getMember(i));
            }
        }

        //check num players, counts num players other than user
        if (game.getNumMembers() < 1)
            enough_players = false;
        
    } while (!quit && enough_players && sorcerer_anger < 100 && game.getMember(0).getName().length() > 0 && !exit);

    //game end scenarios
    if (quit)
    {
        cout << endl << "The adventurers could not make it out of the dungeon." << endl << endl << endl << endl;
        
        file.open("gameOver.txt");
        if(file.is_open())
        {
            while (!file.eof())
            {
                getline(file, lines);
                cout << BOLDRED << lines << RESET << endl;
            }
        }
        file.close();
    }

    if (!enough_players)
    {
        cout << endl << "Where has your party gone? You cannot escape the dungeon solo." << endl << endl << endl << endl;

        file.open("gameOver.txt");
        if(file.is_open())
        {
            while (!file.eof())
            {
                getline(file, lines);
                cout << BOLDRED << lines << RESET << endl;
            }
        }
        file.close();
    }

    if (sorcerer_anger >= 100)
    {
        cout << endl << "Sorcerer anger level 100. You have angered the sorcerer and he has destroyed the dungeon with you and your party inside it.";
        for(int i = 0; i < 5; i++)
        {
            game.death(game.getMember(i));
        }
        cout << endl << endl << endl << endl;

        file.open("gameOver.txt");
        if(file.is_open())
        {
            while (!file.eof())
            {
                getline(file, lines);
                cout << BOLDRED << lines << RESET << endl;
            }
        }
        file.close();
    }
    
    if (game.getMember(0).getName().length() == 0) 
    {
        cout << endl << "Your main character has died. How can you escape the dungeon without a leader?" << endl << endl << endl << endl;

        file.open("gameOver.txt");
        if(file.is_open())
        {
            while (!file.eof())
            {
                getline(file, lines);
                cout << BOLDRED << lines << RESET << endl;
            }
        }
        file.close();
    }

    //write to files
    string leaderboard_name;
    //prompt user for name for leaderboard here
    cout << endl << endl << "Enter a name for the leaderboard: \t";
    cin >> leaderboard_name;

    Leaderboard latest_board(leaderboard_name);
    latest_board.calculateScore(game.getMonstersKilled(), rooms_cleared, sorcerer_anger);

    //read leaderboard text file into vector
    vector<Leaderboard> leader_vec;
    latest_board.readLeaderboard("leaderboard.txt", leader_vec);

    //add user score to board vector
    leader_vec.push_back(latest_board);

    //print vector to screen
    sleep_for(1s);
    cout << "________________________________________";
    cout << endl << "LEADERBOARD" << endl;
    cout << "________________________________________" << endl;
    cout << "Player Name:\tScore:" << endl;
    for (int i = 0; i < leader_vec.size(); i++) {
        cout << leader_vec.at(i).getName() << "\t" << leader_vec.at(i).getScore() << endl;
    }


    //publish updated vector to leaderboard text file
    latest_board.writeLeaderboard(leader_vec);

    //gamestats writing
    game.writeGameStats(rooms_cleared, sorcerer_anger, spaces_explored, num_turns);
    
}