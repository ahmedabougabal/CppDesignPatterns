#include <iostream>
#include <memory>
#include <cstring>
#include <stdexcept>
using namespace std;
// this patterns encapsulates the creation of objects and allows you to keep objects of same family together

class Door
{
public:
  Door() {};
  virtual void open() = 0;
  virtual ~Door() = default;
};

class GasCarDoor : public Door
{
public:
  GasCarDoor()
  {
    cout << "this is the sound of a gas car door" << endl;
  }
  void open() override
  {
    cout << "click" << "\n";
  }
};

class ElectricCarDoor : public Door
{
public:
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
    strcpy(this->sound, "");
  }
  virtual void Run() = 0;
  virtual ~Engine() = default;
};

class GasEngine : public Engine
{
public:
  GasEngine()
  {
    strcpy(this->sound, "V12 vrrrrooomm");
    cout << "making a gas engine sound" << endl;
  }
  void Run() override
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
  void Run() override
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
  cout << "1: Gasoline\n";
  cout << "2: Electric\n";
  cin >> selection;

  //* converting selection to enum CarType
  try
  {
    CarType model;
    if (selection == 1)
    {
      (model = CarType::Gasoline);
    }
    else if (selection == 2)
    {
      (model = CarType::Electric);
    }
    else
    {
      throw runtime_error("no models available for your selection");
    }

    auto factory = createFactory(model);
    // manufacture the whole car components
    auto door = factory->createDoor();
    auto engine = factory->createEngine();
    cout << "\nthis is the testing phase of the manufactured components\n";
    door->open();
    engine->Run();
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
    return -1;
  }

  return 0;
}