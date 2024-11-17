#include <iostream>
#include <cstring>
#include <cstdio> // For sprintf_s (requires a buffer size param to prevent buffer overflows)
/* we can also use stringstream instead of sprintf_s */
#include <sstream>
using namespace std;
// understanding the (builder pattern implementation)

class Dish
{
protected:
  char _dish[10];

public:
  const char *getDish()
  {
    return _dish;
  }
};

class Side
{
protected:
  char _side[10];

public:
  const char *getSide()
  {
    return _side;
  }
};

class Drink
{
protected:
  char *drink[10]; // *  array of 10 char pointers
public:
  Drink()
  {
    cout << "fill cup with orange juice\n";
    for (int i = 0; i < 10; ++i)
    {
      drink[i] = nullptr;
    }
  }

  void setDrink(int index, const char *drink_name)
  {
    // if index is valid, we allocate memory for the new string
    if (index >= 0 && index < 10) // validation for safety
    {
      if (drink[index] != nullptr)
      {
        delete[] drink[index];
      }

      drink[index] = new char[strlen(drink_name) + 1]; // adding 1 to account for the null terminated string as the string is an array of characters
      strcpy(drink[index], drink_name);                // copy drink name to destination drink[index]
    }
  }

  char *getDrink(int index)
  {
    return drink[index];
  }

  string printDrinks()
  {
    stringstream ss;
    for (int i = 0; i < 10; ++i)
    {
      if (drink[i] != nullptr)
      {
        ss << drink[i] << " ";
      }
    }
    return ss.str();
  }
  ~Drink()
  {
    for (int i = 0; i < 10; i++)
    {
      delete[] drink[i];
    }
  };
};

// Complex MealCombo object that contains an Entree, a Side and a Drink object
class MealCombo
{
private:
  Dish *dish;
  Side *side;
  Drink *drink;
  char bag[100];

public:
  stringstream ss;

  MealCombo(const char *type)
  {
    ss << "bag" << type;
    cout << ss.str();
  }
};

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