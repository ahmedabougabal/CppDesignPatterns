#include <iostream>
#include <windows.h>
#include <memory>
using namespace std;
// concept : app requires an obj to be globally accessed , 1 and only one instance of this object.
//* 1- should contain a pointer to itself to access its unique instance.
//* 2- constructor must be set to private, only a singleton itself is able to create a new singleton.
// ! can't use new singleton directly in the main program
/* instantiate an object outside the class? => declare a static method inside the class so that it can access
the private constructor and then instantiate the object from the class */

class Singleton // BEST USECASE : Loggings , note: as many parts of the program can work on only on 1 instance, it is difficult
// to monitor which part has changed the instance (who has changed me?)
{
private:
  Singleton()
  {
    cout << "Singleton object Instantiated" << endl;
  }
  static unique_ptr<Singleton> ptr;
  static CRITICAL_SECTION critical;

public:
  static Singleton *get_instance() //* responsible for instatiating an object
  {
    EnterCriticalSection(&critical);
    if (ptr == nullptr)
    {
      ptr.reset(new Singleton());
    }
    LeaveCriticalSection(&critical);
    return ptr.get(); // return this ptr for access
  }
  ~Singleton()
  {
    cout << "destroying instance\n";
  }
  static void init_critical_section()
  {
    InitializeCriticalSection(&critical);
  }
  static void delete_critical_section()
  {
    DeleteCriticalSection(&critical);
  }
};

// intialize a static member outside the class
unique_ptr<Singleton> Singleton::ptr = nullptr;
CRITICAL_SECTION Singleton::critical;

int main()
{
  Singleton::init_critical_section();
  Singleton *s1 = Singleton::get_instance();
  Singleton *another_instance = Singleton::get_instance();
  cout << s1 << "\n";               // both pointers point to the same memory address
  cout << another_instance << "\n"; // both pointers point to the same memory address
  Singleton::delete_critical_section();
  return 0;
}
/*
simple singleton implementations are //! not thread safe.
if you are running an app where it utilizes multi-threading, both
threads will be trying to call an instance at same time, one finds that
ptr is null so it proeeds to call get_instance and takes time if the
instatiated object is a complex singleton object that would take time
while the other thread finds out that there isn't an instatiated object
yet (instance(ptr in this case) is NULL), so it proceeds in
calling and creating a new one, so both threads have now created
2 instances(objeccts) of the Singleton class, where the second instance of
thread 2 will override the first created instance and losing of data
occurs as a result of //!overriding.

* how to solve ??
--> use lazy initialization : call an instance at the very start
of the execution (at the start of the main() function program), this
means instance will never be NULL, this prevents creation of another
instances from now on.

! what if it is expensive on exectution? (and it is being called on the
!start of the program as of the lazy initialization solution)?

--> 2nd solution (preferred): use critical section but //! costly operation (may slow the app)
* --> EnterCriticalSection(&Critical)
allows only a block of code to be exectued by only 1 thread at a time.
so that when one thread enters this section, other thread will wait
for the first thread to compelete the block of code before it can
enter

*/

// sum it up : this pattern ensures that an object is globally accessible and has only 1 instance.