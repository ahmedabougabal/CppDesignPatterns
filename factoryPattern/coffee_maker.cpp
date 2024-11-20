#include <iostream>
#include <string.h>
#include <memory> //* modern approach for memory handling & cleanup
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
    cout << "preparing " << get_type() << endl;
  }
  void brew_coffee() const override
  {
    cout << "brewing " << get_type() << endl;
  }
  void serve_coffee() const override
  {
    cout << "serving " << get_type() << endl;
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
    cout << "preparing " << get_type() << endl;
  }
  void brew_coffee() const override
  {
    cout << "brewing " << get_type() << endl;
  }
  void serve_coffee() const override
  {
    cout << "serving " << get_type() << endl;
  }
};

// class coffeeMakerFactory : public Coffee (//!using inheritance is a wrong practice here )
//* this class needs to run independently and just return coffee objects
class coffeeMakerFactory
{
private:
  // Coffee *coffee_ptr; //! will update this to a unique ptr as a best practice approach
  unique_ptr<Coffee> coffee_ptr;

public:
  unique_ptr<Coffee> get_coffee()
  {
    int choice;
    cout << "Choose the type of coffee you wish to make" << endl;
    cout << "1 for espresso" << endl;
    cout << "2 for Cappuccino" << endl;
    cin >> choice;
    switch (choice)
    {
    case 1:
      this->coffee_ptr = make_unique<Espresso>();
      // this->coffee_ptr = new Espresso();
      break;
    case 2:
      this->coffee_ptr = make_unique<Cappuccino>();
      break;
    default:
      cout << "Invalid choice, Try Again\n";
      return nullptr;
    }
    return move(coffee_ptr); // return the create coffe object
  }
};

int main()
{
  coffeeMakerFactory factory;
  auto coffe = factory.get_coffee();
  if (coffe)
  {
    coffe->prepare_coffee();
    coffe->brew_coffee();
    coffe->serve_coffee();
  }
  return 0;
}