#include <iostream>
#include <string.h>
using namespace std;

class Coffee
{
protected:
  char coffee_type[20];
  virtual void set_type(const char *type)
  {
    strcpy_s(this->coffee_type, type);
  }
  const virtual char *get_type() const
  {
    return this->coffee_type;
  }

public:
  virtual void prepare_coffee() const = 0; // read-only (using const) (promise: won't change object's state)
  virtual void brew_coffee() const = 0;
  virtual void serve_coffee() const = 0;
  virtual ~Coffee() = default;
};

class Cappuccino : public Coffee
{
public:
  Cappuccino()
  {
    set_type("Cappuccino");
  }

  void prepare_coffee() const override
  {
    cout << "preparing Cappuccino" << endl;
  }
  void brew_coffee() const override
  {
    cout << "brewing Cappuccino" << endl;
  }
  void serve_coffee() const override
  {
    cout << "serving Cappuccino" << endl;
  }
};

class Espresso : public Coffee
{
public:
  Espresso()
  {
    set_type("Espresso");
  }

  void prepare_coffee() const override
  {
    cout << "preparing " << coffee_type << endl;
  }
  void brew_coffee() const override
  {
    cout << "brewing " << coffee_type << endl;
  }
  void serve_coffee() const override
  {
    cout << "serving " << coffee_type << endl;
  }
};
