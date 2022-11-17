//Authors Nicolas Post and Ryan Greir 
#include <iostream>
#include "Cookware.h"
#include "Monster.h"
#include "Treasure.h"
#include "Member.h"
#include "Inventory.h"
using namespace std;
 
int main () {
    Cookware cook1 = Cookware("pan", 5, .25);
    Cookware cook2 = Cookware("pot", 1, .5);
    assert(cook1.getBreakChance() == .25);
    assert(cook1.getCost() == 5);
    assert(cook1.getName() == "pan");

    Treasure t1 = Treasure("treasure1", 7);
    assert(t1.getPrice() == 7);
    assert(t1.getName() == "treasure1");

    Monster monster1("monster1", 4);
    assert(monster1.getChallengeRating() == 4);
    assert(monster1.getMonsterName() == "monster1");

    Monster monsters[30];
    int size = monster1.readMonster("monsters.txt", monsters, 30);
    // for (int i = 0; i < size; i++)
    //     cout << monsters[i].getMonsterName() << "\t" << monsters[i].getChallengeRating() << endl;

    Member p1("peter");
    assert(p1.getName() == "peter");
    assert(p1.getFullness() == 50);

    Inventory inv = Inventory();
    inv.setWeaponsAt("w1", 0);
    inv.setWeaponsAt("", 1);
    inv.setWeaponsAt("w2", 2);
    inv.setWeaponsAt("w3", 3);
    inv.setWeaponsAt("w4", 4);
    inv.setArmor(4);
    inv.setIngredients(1);
    inv.setGold(100);
    inv.addCookware(cook1);
    inv.addCookware(cook2);
    inv.addTreasure(t1);

    inv.printInv();

    string weapons[5] = {"baby ass sword", "huge sword", "weird axe", "", "bow"};
    Inventory inv1(weapons, 5, 20, 62);

    inv1.printInv();
    
}