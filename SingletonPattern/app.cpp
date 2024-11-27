#include <iostream>
using namespace std;

class Leader
{
private:
  static Leader *_instance;
  Leader()
  {
    cout << "instatiated test" << endl;
  }

public:
  static Leader *getInstance()
  {
    if (_instance == nullptr)
    {
      _instance = new Leader();
    }
    return _instance;
  }
  ~Leader()
  {
  }
  void do_sth()
  {
    cout << "lead the team" << "\n";
  }
  static void make_announcement()
  {
    cout << "hey folks";
  }
};

Leader *Leader::_instance = nullptr;
int main()
{
  Leader *l = nullptr;
  if (l == NULL)
  {
    l->getInstance();
    l->do_sth();
  }
  cout << "=================\n";
  Leader *lead = lead->getInstance();
  lead->do_sth();
  lead->make_announcement();
  return 0;
}