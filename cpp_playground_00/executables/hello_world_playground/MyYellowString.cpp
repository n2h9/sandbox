#include <iostream>
#include <string>

class MyYellowString {
 public:
  MyYellowString() = default;
  MyYellowString(const std::string& value) {
    using namespace std;
    m_value = new string{value};

    cout << "MyYellowString created!" << endl;
  }

  MyYellowString(const MyYellowString& other) {
    using namespace std;
    m_value = new string{*other.m_value};
    cout << "MyYellowString copied!" << endl;
  }

  MyYellowString(MyYellowString&& other) : m_value(other.m_value) {
    using namespace std;
    other.m_value = nullptr;
    cout << "MyYellowString moved!" << endl;
  }

  ~MyYellowString() {
    using namespace std;
    delete m_value;
    cout << "MyYellowString deleted!" << endl;
  }

  void Print() const {
    using namespace std;
    cout << *m_value << endl;
  }

 private:
  std::string* m_value;
};

class MyYellowEntity {
 public:
  MyYellowEntity(const MyYellowString& name) : m_name(name) {
    using namespace std;
    cout << "MyYellowEntity created!" << endl;
  }
  MyYellowEntity(MyYellowString&& name) : m_name(std::move(name)) {
    using namespace std;
    cout << "MyYellowEntity created! (move semantics)" << endl;
  }

  ~MyYellowEntity() {
    using namespace std;
    cout << "MyYellowEntity deleted!" << endl;
  }

  void PrintName() { m_name.Print(); }

 private:
  const MyYellowString m_name;
};