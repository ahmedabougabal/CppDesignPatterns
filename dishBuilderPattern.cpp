#include <iostream>
#include <cstring>
#include <cstdio> // For sprintf_s (requires a buffer size param to prevent buffer overflows)
/* we can also use stringstream instead of sprintf_s */
#include <sstream>
#include <string.h>
using namespace std;
// understanding the (builder pattern implementation)

class Dish
{
private:
  string dish;

public:
  void setDish(const string &dish)
  {
    this->dish = dish;
  }

  const string &getDish() const
  {
    return this->dish;
  }
};

class Side
{
private:
  string side;

public:
  void setSide(const string &inp_side)
  {
    this->side = inp_side;
  }

  const string &getSide() const
  {
    return this->side;
  }
};

class Drink
{
protected:
  string drinks[10];
  int currentDrink = 0; //! this is an attempt to make the class Drink Indepdendent

public:
  Drink()
  {
    cout << "\nInitializing drinks refills...\n";
  }

  void setDrink(const string &drink_name)
  {
    // if index is valid, we allocate memory for the new string
    if (this->currentDrink < 10) // validation for safety
    {
      drinks[currentDrink++] = drink_name;
      cout << "added drink: " << drink_name << endl;
    }
    else
    {
      cout << "drinks capacity has been reached" << endl;
    }
  }

  string getDrink() const
  {
    if (currentDrink > 0)
    {
      return drinks[currentDrink - 1];
    }
    else
    {
      return "no drinks have been set.";
    }
  }

  string printDrinks() const
  {
    stringstream ss;
    for (int i = 0; i < currentDrink; ++i)
    {
      ss << drinks[i];
      if (i < currentDrink - 1)
        ss << ", ";
    }
    return ss.str();
  }
  // * removed destructor as i have imported string.h preprocessor directive which handles its memory deallocation
};

// Complex MealCombo object that contains an Entree, a Side and a Drink object
class MealCombo
{
private:
  Dish *dish = nullptr;
  Side *side = nullptr;
  Drink *drink = nullptr;
  string desc;

public:
  // create setters for the composed objects
  void set_dish(Dish *dish_ptr)
  {
    this->dish = dish_ptr;
  }

  void set_drink(Drink *drink_ptr)
  {
    this->drink = drink_ptr;
  }

  void set_side(Side *side_ptr)
  {
    this->side = side_ptr;
  }

  string get_meal_box() const
  {
    stringstream ss;
    if (drink)
    {
      ss << "drink: " << drink->getDrink();
      ss << endl;
    }
    else
    {
      ss << "no drinks in the meal box";
    }
    if (dish)
    {
      ss << "main dish is " << dish->getDish();
      ss << endl;
    }
    else
    {
      ss << "no dish item here";
      ss << endl;
    }
    if (side)
    {
      ss << "your desserts : " << side->getSide();
      ss << endl;
    }
    else
    {
      ss << "no side items here";
      cout << endl;
    }
    string result = ss.str();
    return result.c_str();
  }

  MealCombo(const string &type) : dish(nullptr), side(nullptr), drink(nullptr)
  {
    cout << "meal combo " << type << endl;
  }

  ~MealCombo()
  {
    delete dish;
    delete side;
    delete drink;
  }
};

int main()
{
  MealCombo *meal = new MealCombo("Cheat meal");
  Drink *drink = new Drink();
  drink->setDrink("apple juice");
  meal->set_drink(drink);

  Side *side = new Side();
  side->setSide("konafa");
  meal->set_side(side);

  Dish *dish_ptr = new Dish();
  dish_ptr->setDish("chicks");
  meal->set_dish(dish_ptr);

  cout << meal->get_meal_box();
  delete meal;
  return 0;
}

/*
sth i would like to add : strings are an array of characters and the last char is called a null terminated string
which adds one to the actual string size.

Before setting any drinks:
drink array:  [nullptr][nullptr][nullptr][nullptr][nullptr][nullptr][nullptr][nullptr][nullptr][nullptr]
indices:         0       1        2        3        4        5        6        7        8        9

After setting "Cola" at index 0:
drink[0] = new char[5];  // strlen("Cola") + 1 = 5
drink array:  [ptr1][nullptr][nullptr][nullptr][nullptr][nullptr][nullptr][nullptr][nullptr][nullptr]
                ↓
Memory:        ['C']['o']['l']['a']['\0']

After setting "Coffee" at index 1:
drink[1] = new char[7];  // strlen("Coffee") + 1 = 7
drink array:  [ptr1][ptr2][nullptr][nullptr][nullptr][nullptr][nullptr][nullptr][nullptr][nullptr]
                ↓     ↓
Memory:        ['C']['o']['l']['a']['\0']
                     ['C']['o']['f']['f']['e']['e']['\0']

After setting "Tea" at index 2:
drink[2] = new char[4];  // strlen("Tea") + 1 = 4
drink array:  [ptr1][ptr2][ptr3][nullptr][nullptr][nullptr][nullptr][nullptr][nullptr][nullptr]
                ↓     ↓     ↓
Memory:        ['C']['o']['l']['a']['\0']
                     ['C']['o']['f']['f']['e']['e']['\0']
                           ['T']['e']['a']['\0']

*/