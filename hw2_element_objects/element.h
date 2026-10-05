# pragma once

#include <iostream>
# include <optional>
# include <string>

class Element {
  private:
    bool amIInt;
    std::optional<int> myInt;
    std::optional<float> myFloat;
  public:
    Element(int i):
      amIInt(true), myInt(i), myFloat(std::nullopt) {}
    Element(float f):
      amIInt(false), myInt(std::nullopt), myFloat(f) {}
    Element(const std::string& newVal);

    static bool canConvertToElement(const std::string &s);

    bool IsInt() { return this->amIInt; }
    bool IsFloat() { return !this->amIInt; }
    int getInt() { return this->myInt.value(); }
    float getFloat() { return this->myFloat.value(); }

    const double Value();
    const int IntValue();
    const double DoubleValue();
    void Value(double newVal);
    void ChangeType();
    
    void print() {
      if (this->IsInt()) {
        std::cout << this->myInt.value() << std::endl;
      } else {
        std::cout << this->myFloat.value() << std::endl;
      }
    }

    // credit to https://stackoverflow.com/questions/8475940/overloading-operator-for-printing-as-a-member
    // and https://www.geeksforgeeks.org/cpp/operator-overloading-cpp/
    // for the overloading tips
    friend Element operator+(const Element& lhs, const Element& rhs);
    friend Element operator-(const Element& lhs, const Element& rhs);
    friend Element operator*(const Element& lhs, const Element& rhs);
    friend Element operator/(const Element& lhs, const Element& rhs);
    friend Element operator%(const Element& lhs, const Element& rhs);
};

