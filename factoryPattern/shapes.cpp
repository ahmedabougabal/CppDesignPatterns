#include <iostream>
#include <cstring>
#include <math.h>
#include <vector>
#include <memory>
#define M_PI 3.14159265358979323846
using namespace std;

class Shape
{
private:
  char shape_name[20];

protected:
  void setName(const char *inpName)
  {
    strncpy(shape_name, inpName, sizeof(this->shape_name) - 1);
    this->shape_name[sizeof(this->shape_name) - 1] = '\0'; // ensure null termination
  }

public:
  const char *getName() const
  {
    return this->shape_name;
  }
  virtual double getArea() = 0;
};

class Circle : public Shape
{
private:
  float radii;

public:
  Circle(float r) : radii(r)
  {
    setName("that's a Circle");
  }
  double getArea() override
  {
    return M_PI * pow(radii, 2);
  }
};

class Square : public Shape
{
private:
  float length;

public:
  Square(float L) : length(L)
  {
    setName("this is a Square");
  }
  double getArea() override
  {
    return this->length * this->length;
  }
};

enum Type
{
  CIRCLE,
  SQUARE
};

class factory
{
  /*creating and returning shape objects on demand*/
public:
  unique_ptr<Shape> create(Type t, float dimension)
  {
    switch (t)
    {
    case CIRCLE:
      return make_unique<Circle>(dimension);
    case SQUARE:
      return make_unique<Square>(dimension);
    default:
      return nullptr;
    }
  }
};

int main()
{
  factory f;
  vector<unique_ptr<Shape>> shapes;
  shapes.push_back(f.create(CIRCLE, 5));
  shapes.push_back(f.create(SQUARE, 8));

  for (const auto &shape : shapes)
  {
    cout << "area of " << shape->getName() << " is " << shape->getArea() << "\n";
  }
  return 0;
}