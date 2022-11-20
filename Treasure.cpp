//Authors Nicolas Post and Ryan Greir 
#include <iostream>
#include <iostream>
#include "Treasure.h"

using namespace std;

Treasure::Treasure()
{
    name_ = "";
    price_ = 0;
}

Treasure::Treasure(string name, int price)
{
    name_ = name;
    price_ = price;
}

string Treasure::getName()
{
    return name_;
}

void Treasure::setName(string name)
{
    name_ = name;
}

int Treasure::getPrice()
{
    return price_;
}

void Treasure::setPrice(int price)
{
    price_ = price;
}


