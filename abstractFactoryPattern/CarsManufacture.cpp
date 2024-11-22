#include <iostream>
#include <memory>
using namespace std;

class Door
{
public:
  Door() {};
  virtual void open() = 0;
};

class GasCarDoor : public Door
{
public:
  GasCarDoor()
  {
    cout << "this is the sound of a gas car door" << endl;
  }
  void open()
  {
    cout << "click" << "\n";
  }
};

class ElectricCarDoor : public Door
{
  ElectricCarDoor()
  {
    cout << "this is the sound of an electric car door" << endl;
  }
  void open()
  {
    cout << "zzzzzzzshhhh" << endl;
  }
};

class Engine
{
protected:
  char sound[15];

public:
  Engine()
  {
    strcpy_s(this->sound, "");
  }
  virtual void Run() = 0;
};

class GasEngine : public Engine
{
public:
  GasEngine()
  {
    strcpy_s(this->sound, "V12 vrrrrooomm");
    cout << "making a gas engine sound" << endl;
  }
  void Run()
  {
    cout << this->sound << endl;
    cout << "a gas engine roars as it accelerates" << "\n";
  }
};

class ElectricEngine : public Engine
{
public:
  ElectricEngine()
  {
    strcpy_s(this->sound, "SHHHHH");
    cout << "making an electric engine" << endl;
  }
  void Run()
  {
    cout << this->sound << endl;
    cout << "an electric engine meows as it cuddle" << "\n";
  };
};

//* factories

class Factory
{
public:
  virtual unique_ptr<Door> createDoor() = 0;
  virtual unique_ptr<Engine> createEngine() = 0;
  virtual ~Factory() = default;
};

class GasCarFactory : public Factory
{
  //* Implement the pure virtual functions for every car factory
public:
  unique_ptr<Door> createDoor() override
  {
    return make_unique<GasCarDoor>();
  }

  unique_ptr<Engine> createEngine() override
  {
    return make_unique<GasEngine>();
  }
};

class ElectricCarFactory : public Factory
{
  //* Implement the pure virtual functions for every car factory
public:
  unique_ptr<Door> createDoor() override
  {
    return make_unique<ElectricCarDoor>();
  }

  unique_ptr<Engine> createEngine() override
  {
    return make_unique<ElectricEngine>();
  }
};

enum CarType
{
  Gasoline,
  Electric
};

unique_ptr<Factory> createFactory(CarType t)
{
  switch (t)
  {
  case Gasoline:
    return make_unique<GasCarFactory>();
    break;
  case Electric:
    return make_unique<ElectricCarFactory>();
    break;
  default:
    throw runtime_error("invalid type selection");
  }
}

int main()
{
  int selection;
  cout << "select a car you wish to build\n>> ";
  cout << "1: Gasoline";
  cout << "2: Electric";
  cin >> selection;

  return 0;
}