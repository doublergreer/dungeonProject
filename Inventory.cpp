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
#define BOLDWHITE   "\033[1m\033[37m" 
#define RESET   "\033[0m"

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

//returns member with said name unless it does not exist, else return blank member
int Inventory::getMemberIndex(string name) {
    for (int i = 0; i < 5; i++) {
        if (party_[i].getName() == name) {
            return i;
        }
    }
    return -1;
}

Member Inventory::getMember(int index) {
    return party_[index];
}

void Inventory::setKeys(int keys) {
    keys_ = keys;
}
int Inventory::getKeys() {
    return keys_;
}

void Inventory::addDeadMonster(Monster m) {
    dead_monsters_.push_back(m);
}

Monster Inventory::getDeadMonster(string name) {
    for (int i = 0; i < dead_monsters_.size(); i++) {
        if (dead_monsters_.at(i).getMonsterName() == name) {
            return dead_monsters_.at(i);
        }
        
    }
    return Monster();
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
    //sleep_for(1.5s);
    printInv();
    //sleep_for(1.5s);
    cout << "PARTY:" << endl;

    for (int i = 0; i < 5; i++) 
        cout << "\t" << party_[i].getName() << "\t| Fullness: " << party_[i].getFullness() << endl;
    cout << "________________________________________" << endl;
    //sleep_for(2s);
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

    if (diff_weapon >= num_weapons && num_weapons != 0) 
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
    sleep_for(2.5s);
    int r2 = random.randomNum(1, 6);

    //actual calculation of the monster fight
    int monster_fight = ((r1 * weapon_stats + diff_bonus) - ((r2 * m.getChallengeRating()) / armor_));

    if(monster_fight > 0)
    {
        //add gold and food
        gold_ += (10 * m.getChallengeRating());
        ingredients_ += (5 * m.getChallengeRating());
        if(misfortuneCalc(10) == true)
        {
            keys_ += 1;
            cout << endl << BOLDWHITE << "\tYour party has found a key!" << RESET << endl << endl;
        }

        dead_monsters_.push_back(m);

        return true;
    }
    else if(monster_fight <= 0)
    {
        gold_ += (int)(gold_ * .75);
        if(ingredients_ - 30 < 0)
        {
            ingredients_ = 0;
        }
        else
        {
           ingredients_ = ingredients_- 30; 
        }
        //make sure there is a check to see if the party members die 
        return false;
    }
    return false;
}


Monster Inventory::monsterPick(int rooms_cleared) {
    Monster arr[21];
    arr[0].readMonster("monsters.txt", arr, 21);

    if (rooms_cleared == 0) {
        cout << endl << endl << "in" << endl;
        aliveAtLevel(0, 3, arr);
    }
    else if (rooms_cleared == 1) {
        aliveAtLevel(4, 7, arr);
    }
    else if (rooms_cleared == 2) {
        aliveAtLevel(8, 11, arr);
    }
    else if (rooms_cleared == 3) {
        aliveAtLevel(12, 15, arr);
    }
    else if (rooms_cleared >= 4) {
        aliveAtLevel(16, 19, arr);
    }
    return Monster("error", 0);
}

void Inventory::merchantMenu(int rooms_cleared) {
    int merchant_menu = 0;
    double price_factor;
    
    if (rooms_cleared > 0)
        price_factor = 1 + (.25 * rooms_cleared);
    else
        price_factor = 1;

    

    do
    {
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
                cout << "\t1. (25%) Ceramic Pot [" << (int)(2*price_factor) << " Gold]" << endl;
                cout << "\t2. (10%) Frying Pan [" << (int)(10*price_factor) << " Gold]" << endl;
                cout << "\t3. (02%) Cauldron [" << (int)(20*price_factor) << " Gold]" << endl;
                cout << "\t4. Exit Menu" << endl;
                cin >> cookware_choice;

                if(cookware_choice == 1 && getGold() >= (int)(2*price_factor))
                {
                     setGold(getGold() - (int)(2*price_factor)); 
                     addCookware(ceramic_pot);
                }
                else if (cookware_choice == 1)
                    cout << "Insufficient Funds" << endl << "No items were purchased. Try again." << endl;

                if(cookware_choice == 2 &&  getGold() >= (int)(10*price_factor))
                {
                     setGold( getGold() - (int)(10*price_factor));
                     addCookware(frying_pan);
                }
                else if (cookware_choice == 2)
                    cout << "Insufficient Funds" << endl << "No items were purchased. Try again." << endl;
                    

                if(cookware_choice == 3 &&  getGold() >= (int)(20*price_factor))
                {
                     setGold( getGold() - (int)(20*price_factor));
                     addCookware(cauldron);
                }
                else if (cookware_choice == 3)
                    cout << "Insufficient Funds" << endl << "No items were purchased. Try again." << endl;

                if (cookware_choice < 1 || cookware_choice > 4)
                    cout << "Invalid Input" << endl;
            }

        }
        //ingredients menu
        if(merchant_menu == 2)
        {   
            int num_ingredients = -1;
            cout << endl << "I reccomend you purchase at least 10 kg of ingredients per person." << endl << endl;

            cout << "How many kg of ingredients do you need [" << (int)(1*price_factor) << " Gold/kg]? (Enter a positive mulitple of 5, or 0 to cancel)" << endl;
            cin >> num_ingredients;

            while(num_ingredients < 0)
            {
                cout << "That is an invalid input. Please enter a positive number." << endl;
                cin >> num_ingredients;
            }

            if( getGold() >= num_ingredients * (int)(1*price_factor) && num_ingredients > 0)
            {
                 setIngredients(getIngredients() + num_ingredients);
                 setGold(getGold() - (num_ingredients * (int)(1*price_factor)));
                cout << endl << "Success! Your party now has " <<  getIngredients() << " kg of ingredients." << endl << endl << endl;
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
            string player_name; 

            cout << endl << endl << "I have a plentiful collection of weapons to choose from, what would you like?" << endl << "Note that some of them provide you a special bonus in combat, marked by a (+X).";
            do {
                cout << endl << "\tChoose one of the following: " << endl;
                cout << "\t1. Stone Club [" << (int)(2*price_factor) << " Gold]" << endl;
                cout << "\t2. Iron Spear [" << (int)(2*price_factor) << " Gold]" << endl;
                cout << "\t3. (+1) Mythril Rapier [" << (int)(5*price_factor) << " Gold]" << endl;
                cout << "\t4. (+2) Flaming Battle-Axe [" << (int)(15*price_factor) << " Gold]" << endl;
                cout << "\t5. (+3) Vorpal Longsword [" << (int)(50*price_factor) << " Gold]" << endl;
                cout << "\t6. Cancel" << endl;
                cin >> weapon_choice;

                if (weapon_choice != 6) {
                    cout << endl << "\tWhich party member would you like to recieve this weapon? (player name)" << endl;
                    cin >> player_name;
                }

                while (getMemberByName(player_name).getName() == "") {
                    cout << endl << "No player found by the name: " << player_name << endl;
                    cout << "Please enter the name again" << endl;
                    cin >> player_name;
                }

                player_index = getMemberIndex(player_name);

                if (weapon_choice == 1 &&  getGold() >= (int)(2*price_factor)) {
                     setGold(getGold() - (int)(2*price_factor)); 
                     setWeaponsAt("Stone Club", player_index);
                    cout << endl << "Success! Player: " <<  getMember(player_index).getName() << " now has a Stone Club!" << endl;
                    player_index++;
                    cout << "Thank you for your patronage! You have " <<  getGold() << " remaining gold. What else can I get for you?" << endl << endl;
                } else if (weapon_choice == 1)
                    cout << "Insufficient Funds" << endl << "No items were purchased. Try again." << endl;

                if (weapon_choice == 2 &&  getGold() >= (int)(2*price_factor)) {
                     setGold(getGold() - (int)(2*price_factor)); 
                     setWeaponsAt("Iron Spear", player_index);
                    cout << endl << "Success! Player: " <<  getMember(player_index).getName() << " now has an Iron Spear!" << endl;
                    player_index++;
                    cout << "Thank you for your patronage! You have " << getGold() << " remaining gold. What else can I get for you?" << endl << endl;
                } else if (weapon_choice == 2)
                    cout << "Insufficient Funds" << endl << "No items were purchased. Try again." << endl;

                if (weapon_choice == 3 &&  getGold() >= (int)(5*price_factor)) {
                     setGold( getGold() - (int)(5*price_factor));
                     setWeaponsAt("(+1) Mythril Rapier", player_index);
                    cout << endl << "Success! Player: " <<  getMember(player_index).getName() << " now has a (+1) Mythril Rapier!" << endl;
                    player_index++;
                    cout << "Thank you for your patronage! You have " <<  getGold() << " remaining gold. What else can I get for you?" << endl << endl;
                } else if (weapon_choice == 3)
                    cout << "Insufficient Funds" << endl << "No items were purchased. Try again." << endl;

                if (weapon_choice == 4 &&  getGold() >= (int)(15*price_factor)) {
                     setGold( getGold() - (int)(15*price_factor));
                     setWeaponsAt("(+2) Flaming Battle-Axe", player_index);
                    cout << endl << "Success! Player: " <<  getMember(player_index).getName() << " now has a (+2) Flaming Battle-Axe!" << endl;
                    player_index++;
                    cout << "Thank you for your patronage! You have " <<  getGold() << " remaining gold. What else can I get for you?" << endl << endl;
                } else if (weapon_choice == 4)
                    cout << "Insufficient Funds" << endl << "No items were purchased. Try again." << endl;
                
                if (weapon_choice == 5 &&  getGold() >= (int)(50*price_factor)) {
                     setGold(getGold() - (int)(50*price_factor));
                     setWeaponsAt("(+3) Vorpal Longsword", player_index);
                    cout << endl << "Success! Player: " <<  getMember(player_index).getName() << " now has a (+3) Vorpal Longsword!" << endl;
                    player_index++;
                    cout << "Thank you for your patronage! You have " <<  getGold() << " remaining gold. What else can I get for you?" << endl << endl;
                } else if (weapon_choice == 5)
                    cout << "Insufficient Funds" << endl << "No items were purchased. Try again." << endl;

            } while (weapon_choice != 6 && player_index < 5);
        }

        if(merchant_menu == 4)
        {
            int armor_choice = 0;
            cout << "Each suit costs " << (int)(5*price_factor) << " gold. How many suits of armor can I get you? " << endl << "(Enter a positive integer, or 0 to cancel)" << endl;
            cin >> armor_choice;

            if ( getGold() >= (armor_choice * ((int)(5*price_factor)))) {
                  setArmor(armor_choice + armor_);
                  setGold( getGold() - armor_choice * ((int)(5*price_factor)));
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
        {   int sell_menu;
        
            cout << endl << "If you happen to have any of the following items, I'd be happy to take them off your hands." << endl << endl;
            cout << "1) Silver ring - 10 gold pieces each" << endl;
            cout << "2) Ruby necklace - 20 gold pieces each" << endl;
            cout << "3) Emerald bracelet - 30 gold pieces each" << endl;
            cout << "4) Diamond circlet - 40 gold pieces each" << endl;
            cout << "5) Gem-encrusted goblet - 50 gold pieces each" << endl;
            cin >> sell_menu;
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

        printInv();

    }while(merchant_menu != 13);

}

bool Inventory::misfortuneCalc(int percent_chance)
{
    int reduced_num = percent_chance / 10;

    srand(time(NULL));
    int rand_num = (rand() % (10 - 1 + 1)) + 1;
    
    if(rand_num > 1 && rand_num <= reduced_num)
    {
        return true; //there is misfortune 
    }
    else
    {
        return false; //there is no misfortune
    }
}

void Inventory::applyMisfortune(bool in_room) {
    Map rand;
    int r = rand.randomNum(0,100);

    if (r > 0 && r <= 30) {
        //robbed
        cout << BOLDWHITE << "MISFORTUNE" << RESET << endl;
        cout << endl << "Oh no! Your party has been robbed." << endl;

        r = rand.randomNum(1,3);

        //lose 10kg ingredients
        if (r == 1) {
            cout << endl << "Your party has lost 10kg of ingredients." << endl;
            if (ingredients_ >= 10)
                ingredients_ -= 10;
            else 
                ingredients_ = 0;
        }
        //lose cookware item
        else if (r == 2) {
            cout << endl << "Your party has lost 1 cookware item." << endl;

            if (cookwares_.size() > 0){
                    cookwares_.pop_back();
            } else
                cout << endl << "Lucky for you all, there are no cookwares to take" << endl;
        }
        //lose armor
        else if (r == 3) {
            cout << endl << "Your party has lost 1 piece of armor." << endl;
            int r2 = rand.randomNum(0,4);

            if (armor_ > 0)  {   
                while(!(party_[r2].getArmor())) {
                    r2 = rand.randomNum(0,4);
                }
                cout << endl << party_[r2].getName() << " has lost their armor." << endl;
                party_[r2].setArmor(false);
                armor_ -= 1;
            }
            else
                cout << endl << "Lucky for you all, there is no armor to take" << endl;

        }
    }

    //weapon or armor breaks
    else if (r > 30 && r <= 40) {
        r = rand.randomNum(0,10);
        int num_weapons;

        cout << BOLDWHITE << "MISFORTUNE" << RESET << endl;

        //count weapons
        for (int i = 0; i < 5; i++) {
            if (weapons_[i].length() > 0) 
                num_weapons++;
        }

        //weapon
        if (r >= 0 && r <=5 && num_weapons > 0) {    
            while (!(weapons_[r].length() > 0)) {
                r = rand.randomNum(0,4);
            }
            cout << endl << party_[r].getName() << "'s weapon has broken." << endl;
            weapons_[r] = "";
        }
        //armor
        else if (armor_ > 0){
            while(!(party_[r].getArmor())) {
                r = rand.randomNum(0,4);
            }
            cout << endl << party_[r].getName() << "'s armor has broken." << endl;
            party_[r].setArmor(false);
            armor_ -= 1;
        }
        //else, no misfortune
    }
    else if (r > 40 && r <= 70) {
        //food poisoning, party member loses 10 pts hunger
        r = rand.randomNum(0,4);

        cout << BOLDWHITE << "MISFORTUNE" << RESET << endl;
        
        if (party_[r].getFullness() > 10) {
            cout << endl << party_[r].getName() << " has gotten food poisoning and lost 10 points of fullness!" << endl;
            party_[r].setFullness(party_[r].getFullness() - 10);
        }
        else {
            cout << endl << party_[r].getName() << " has gotten food poisoning died of hunger immediately!" << endl;
            death(party_[r]);
        }
    }
    else if (r > 70 && in_room) 
    {
        //team member locked in previous room
        r = rand.randomNum(1, 4);

        cout << BOLDWHITE << "MISFORTUNE" << RESET << endl;
        
        while (!(party_[r].getName().length() > 0)) {
            r = rand.randomNum(1, 4);
        }
        cout << endl << party_[r].getName() << " has gotten trapped in the room! Your party must continue on!" << endl; 
        death(party_[r]);   
    }
}

Monster Inventory::aliveAtLevel(int bound1, int bound2, Monster arr[21]) {
    Map rand;

    //traverse dead monster vector
        for(int i = 0; i < 21; i++)
        {
            //picking lvl 1 monster
            int random = rand.randomNum(bound1, bound2); 
            int not_equal = 0;

            for (int j = 0; j < dead_monsters_.size(); j++)
            {   
                //check monter pick isnt on dead monsters
                if (arr[random].getMonsterName() != dead_monsters_.at(j).getMonsterName())
                {
                    not_equal++;
                }
            }
            if (not_equal >= dead_monsters_.size()) {
                return arr[random];
            }
        }
        return Monster();
}


//This function will remove a member of the party 
//It will also remove the weapon they were holding 
//It will remove one armor from the party if the party has armor
void Inventory::death(Member member)
{
    for (int i = 0; i < 5; i++) {
        if (party_[i].getName() == member.getName()) {
            party_[i] = Member();
            party_[i].setFullness(0);
            weapons_[i] = "";
            if (member.getArmor()) {
                armor_ -= 1;
                member.setArmor(false);
            }
        }    
    }
}

int Inventory::doorPuzzle(int choice)
{
    Map doorgame;
    int comp_pick = doorgame.randomNum(1, 3);

    int boulder = 1;
    int shears = 2;
    int parchment = 3;
    int num_lose;

    //cout << comp_pick << endl;
    
    if(comp_pick == 1)
    {
        if(choice == 1)
        {
            return 0;
        }
        else if(choice == 2)
        {
            return -1;
        }
        else if(choice == 3)
        {
            return 1;
        }
    }
    if(comp_pick == 2)
    {
        if(choice == 2)
        {
            return 0;
        }
        else if(choice == 3)
        {
            return -1;
        }
        else if(choice == 1)
        {
            return 1;
        }
    }
    if(comp_pick == 3)
    {
        if(choice == 3)
        {
            return 0;
        }
        else if(choice == 2)
        {
            return -1;
        }
        else if(choice == 1)
        {
            return 1;
        }
        
    }
}
//if (comp picks rock and you pick scissors) 
// comp wins

