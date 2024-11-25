#include <iostream>
#include <cstring>
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

class HotDog : public Dish
{
public:
  HotDog()
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

// base builder
class MealBuilder
{
protected:
  MealCombo *_meal;

public:
  //* adds pure virtual functions for the concrete classes to override
  virtual void cook_dish() {};
  virtual void prepare_side() {};
  virtual void pour_drink() {};
  MealCombo *get_meal()
  {
    return _meal;
  }
};

// Concrete Builder for a Burger Meal which has a burger, fries and a drink
// your code here

class BurgerMeal : public MealBuilder
{
public:
  BurgerMeal()
  {
    this->_meal = new MealCombo("BurgersMeal");
  };
  void cook_dish() override //! missed this override keyword
  {
    Burger *burger_ptr = new Burger; //! another fixed bug, () are optional
    this->_meal->set_dish(burger_ptr);
  }
  void prepare_side() override
  {
    Fries *fries = new Fries;
    this->_meal->set_side(fries);
  }
  void pour_drink() override
  {
    Drink *burger_drink_ptr = new Drink();
    this->_meal->set_drink(burger_drink_ptr);
  }
  const char *openMealBag()
  {
    return this->_meal->opennMealBag();
  }
  ~BurgerMeal()
  {
    delete this->_meal;
  };
};

// Concrete Builder for a Hotdog Meal which has a hotdog, salad and a drink
// your code here
class HotDogMeal : public MealBuilder
{

public:
  HotDogMeal()
  {
    this->_meal = new MealCombo("HotDog");
    // a pointer should hold / point-to the address of an object of the same type of the pointer except for polymorphhism where a child class is derived from base class
    /*
    this->_meal = new MealCombo("hotfog");
    error occurs because _meal is declared as a character array (char _meal[100]),
    but you're trying to assign a pointer to a MealCombo object to it.
    These types are incompatible.
    */
  }
  void cook_dish()
  {
    Dish *hotdog = new HotDog(); //! fixed bug : repplaced new Dish() with new HotDog(), won't cook dish on execution
    this->meal_combo_hot_dog_meal->set_dish(hotdog);
  }
  void prepare_side()
  {
    Salad *salad_ptr = new Salad();
    this->meal_combo_hot_dog_meal->set_side(salad_ptr);
  }
  void pour_drink()
  {
    Drink *drink_ptr = new Drink();
    this->meal_combo_hot_dog_meal->set_drink(drink_ptr);
  }
  const char *openMealBag()
  {
    return this->meal_combo_hot_dog_meal->opennMealBag();
  }

  ~HotDogMeal()
  {
    delete this->meal_combo_hot_dog_meal;
  };
};

int main()
{
  HotDogMeal *hot_dog_ptr = new HotDogMeal();
  hot_dog_ptr->cook_dish();
  hot_dog_ptr->prepare_side();
  hot_dog_ptr->pour_drink();
  cout << "meal contnets : ";
  cout << hot_dog_ptr->openMealBag();
  delete hot_dog_ptr;
  return 0;
}