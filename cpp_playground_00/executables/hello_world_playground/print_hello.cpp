#include <our_project/tools/tools.h>

#include <iostream>
#include <map>
#include <thread>

#include "MyString.cpp"
#include "MyYellowString.cpp"

void fun();

void func1();
void func2();

int& GetValue();
void SetValue(const int&& v);

void RefreshForecast(std::map<std::string, int>);

int main() {
  using namespace our_project::tools;

  print_hello();

  // while (true) {
  //   fun();
  // }

  // std::thread worker1{func1};
  // std::thread worker2{func2};

  // func1();
  // func2();
  {
    GetValue() = 32;

    using namespace std;
    cout << GetValue() << endl;

    int i{10};
    i++;
    // SetValue(i);
    SetValue(12);

    cout << GetValue() << endl;
  }
  // system("ls -la");
  // system("sleep 4");

  {
    using namespace std;
    cout << "using move semantic" << endl;
    Entity entity{"ololo"};
    entity.PrintName();

    cout << "----------------" << endl;
  }
  // {
  //
  // using namespace std;
  //   cout << "using explicit semantic" << endl;
  //   Entity entity2;
  //   entity2 = MyString{"ololo2"};
  //   entity2.PrintName();
  // }

  {
    using namespace std;
    cout << "using move semantic with std::string" << endl;
    MyYellowEntity entity{MyYellowString{"xxx"}};
    entity.PrintName();

    cout << "----------------" << endl;
  }

  {
    using namespace std;
    cout << "using threads ..." << endl;

    map<string, int> forecastMap = {
        {"Berlin", 24},
        {"New York", 16},
        {"Dubai", 33},
    };

    thread bgWorker{RefreshForecast, forecastMap};
    cout << system("sleep 8") << endl;
    bgWorker.detach();
  }

  return 0;
}

void fun() {
  int* arr = new int[1024];
  using namespace std;
  cout << arr << endl;
}

void func1() {
  using namespace std;

  for (auto i = 0; i < 256; i++) {
    cout << "+";
  }
  cout << endl;
}

void func2() {
  using namespace std;

  for (auto i = 0; i < 256; i++) {
    cout << "-";
  }
  cout << endl;
}

int& GetValue() {
  static int value = 16;
  return value;
}

void SetValue(const int&& v) { GetValue() = v; }

void RefreshForecast(std::map<std::string, int> forecastMap) {
  using namespace std;
  while (true) {
    for (auto& entity : forecastMap) {
      entity.second++;
      cout << " [ " << entity.first << " = " << entity.second << " ]" << endl;
    }
    cout << "[ current thread id = " << this_thread::get_id() << " ] " << endl;
    this_thread::sleep_for(2000ms);
  }
}
