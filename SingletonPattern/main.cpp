#include <iostream>
using namespace std;
// concept : app requires an obj to be globally accessed , 1 and only one instance of this object.
//* 1- should contain a pointer to itself to access its unique instance.
//* 2- constructor must be set to private, only a singleton itself is able to create a new singleton.
// ! can't use new singleton directly in the main program
/* instantiate an object outside the class? => declare a static method inside the class so that it can access
the private constructor and then instantiate the object from the class */

class Singleton
{
private:
  Singleton()
  {
    cout << "Singleton object Instantiated" << endl;
  }
  static Singleton *ptr;

public:
  static void get_instance() //* responsible for instatiating an object
  {
    ptr = new Singleton();
  }
  ~Singleton()
  {
    delete this->ptr;
  }
};

// intialize a static member outside the class
Singleton *Singleton::ptr = nullptr;
int main()
{
  Singleton *s = nullptr;
  s->get_instance();
  return 0;
}
// sum it up : this pattern ensures that an object is globally accessible and has only 1 instance.