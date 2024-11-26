#include <iostream>
#include <cstring>
using namespace std;

class Animal
{
protected:
  char hair_color[10];
  int hair_length, tail, weight, height, age;
  int intelligence, stubborness, aggressiveness;

public:
  virtual Animal *clone() = 0; // should implement a clone method (pure virtual function) as to apply such pattern
  // no getters (no way i can get one of those attributes outside the class)
  void set_hair_length(int len)
  {
    this->hair_length = len;
  }
  void set_hair_color(const char *color)
  {
    strcpy_s(this->hair_color, color);
  }
  void set_tail(int _tail)
  {
    this->tail = _tail;
  }
  void set_weight(int _weight)
  {
    this->weight = _weight;
  }
  void set_height(int _height)
  {
    this->height = _height;
  }
  void set_age(int _age)
  {
    this->age = _age;
  }
};

// create the derived sheep class
class Sheep : public Animal
{
public:
  Sheep()
  {
    this->hair_length = 5;
    this->stubborness = 3;
    this->aggressiveness = 2;
    this->intelligence = 7;
  }
  Sheep *clone() override
  {
    return new Sheep(*this);
  }
  void shearing()
  {
    this->hair_length -= 2;
  }
};

// create the derived cow class
class Cow : public Animal
{
public:
  Cow()
  {
    this->stubborness = 6;
    this->aggressiveness = 5;
    this->intelligence = 8;
  }
  // ! override the clone method
  Cow *clone() override
  {
    return new Cow(*this);
  }
};

int main()
{
  // create initial instance of a Sheep
  Sheep *sheep = new Sheep();
  sheep->set_hair_color("orange");
  sheep->set_tail(5);
  sheep->set_weight(95);
  sheep->set_height(1);
  sheep->set_age(5);

  // Instantiate a Cow object
  Cow *cow = new Cow();
  cow->set_hair_color("yellow");
  cow->set_tail(20);
  cow->set_weight(150);
  cow->set_height(23);
  cow->set_age(3);

  Animal *farm[4]; // array which will store the objects of cloned objects
  farm[0] = sheep->clone();
  farm[1] = cow->clone();
  // change a child object property
  farm[1]->set_weight(1000);
  farm[2] = sheep->clone();
  // shear a sheep and clone it
  sheep->shearing();
  farm[3] = sheep->clone();
  return 0;
}