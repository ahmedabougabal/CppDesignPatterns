#include <iostream>
using namespace std;

class Dish
{
protected:
  char _dish[20];

public:
  const char *get_dish_name()
  {
    return _dish;
  }
};

class Burger : public Dish
{
public:
  Burger()
  {
    cout << "\n preparing burgers and adding them to a big juicy buns " << endl;
    strcpy_s(_dish, "Beef Burgers");
  }
};

class HotDogs : public Dish
{
public:
  HotDogs()
  {
    cout << "\n Grill Hotdogs, add them to a Sandwich " << endl;
    strcpy_s(_dish, "Hot Dogs");
  }
};

class Side
{
protected:
  char _side[20];

public:
  char *get_side_name()
  {
    return _side;
  }
};

class Fries : public Side
{
public:
  Fries()
  {
    cout << "fry and season potatoes" << endl;
    strcpy_s(_side, "Fries");
  }
};

class Salad : public Side
{
public:
  Salad()
  {
    cout << "adding fresh veggies" << endl;
    strcpy_s(_side, "Salad");
  }
};

class Drink
{
protected:
  char _drink[20];

public:
  Drink()
  {
    cout << "\n fill cup with Soda" << endl;
    strcpy_s(_drink, "soda");
  }
  char *get_drink_name()
  {
    return _drink;
  }
};

class MealCombo
{
private:
  Dish *dish;
  Side *side;
  Drink *drink;
  char _bag[100];

public:
  MealCombo(const char *type)
  {
    sprintf_s(_bag, "\n %s meal combo: ", type);
  }
  void set_dish(Dish *dish_ptr)
  {
    this->dish = dish_ptr;
  }

  void set_side(Side *side_ptr)
  {
    this->side = side_ptr;
  }

  void set_drink(Drink *drink_ptr)
  {
    this->drink = drink_ptr;
  }
  const char *opennMealBag()
  {
    sprintf_s(_bag, "\n  %s %s %s %s", _bag, dish->get_dish_name(), side->get_side_name(), drink->get_drink_name());
    return this->_bag;
  }
};
