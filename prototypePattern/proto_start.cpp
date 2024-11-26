#include <iostream>
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
  int set_hair_length(int len)
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
};

int main()
{
  return 0;
}