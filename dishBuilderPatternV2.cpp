#include "stdafx.h"
#include <iostream>
#include <sstream>

using namespace std;

// Base Entree class
class Entree
{
protected:
  char _entree[20];

public:
  Entree(const char *name)
  {
    strcpy_s(_entree, name);
    cout << "preparing " << name << " as main dish" << endl;
  }

  const char *getEntree()
  {
    return _entree;
  }
};

// Base Side class
class Side
{
protected:
  char _side[20];

public:
  Side(const char *side)
  {
    strcpy_s(_side, side);
    cout << "preparing desserts..." << side;
  }

  char *getSide()
  {
    return _side;
  }
};

class Drink
{
protected:
  char _drink[20];

public:
  Drink(const char *drink_name)
  {
    strcpy_s(_drink, drink_name);
    cout << "Fill cup with : " << drink_name << endl;
  }
  char *getDrink()
  {
    return _drink;
  }
};

// Complex MealCombo object that contains an Entree, a Side and a Drink object
class MealCombo
{
private:
  Entree *entree;
  Side *side;
  Drink *drink;
  char _bag[100];

public:
  MealCombo(const char *type)
  {
    sprintf_s(_bag, "\n %s meal combo:", type);
  }
  void setEntree(Entree *e)
  {
    entree = e;
  }
  void setSide(Side *s)
  {
    side = s;
  }
  void setDrink(Drink *d)
  {
    drink = d;
  }
  const char *openMealBag()
  {
    sprintf_s(_bag, "%s %s, %s, %s", _bag, entree->getEntree(), side->getSide(), drink->getDrink());
    return _bag;
  }
};

int main()
{
  MealCombo *combo = new MealCombo("regular");
  Drink *drink = new Drink("orange");
  Entree *dish = new Entree("chicken legs");
  Side *side = new Side("potatoes");

  combo->setEntree(dish);
  combo->setDrink(drink);
  combo->setSide(side);

  cout << combo->openMealBag();
  // delete all pointers
  delete combo;
  delete dish;
  delete drink;
  delete side;
}