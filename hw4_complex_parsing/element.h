# pragma once

#include <iostream>
# include <optional>
# include <string>

class Element {
  private:
    bool amIInt;
    std::optional<int> myInt;
    std::optional<double> myDouble;
  public:
    Element(int i):
      amIInt(true), myInt(i), myDouble(std::nullopt) {}
    Element(double f):
      amIInt(false), myInt(std::nullopt), myDouble(f) {}
    Element(const std::string& newVal);

    static bool canConvertToElement(const std::string &s);

    virtual bool IsInt() const { return this->amIInt; }
    virtual bool IsDouble() const { return !this->amIInt; }
    int getInt() const { return this->myInt.value(); }
    double getDouble() const { return this->myDouble.value(); }

    virtual double Value() const ;
    virtual int IntValue() const ;
    virtual double DoubleValue() const ;
    void Value(double newVal);
    void ChangeType();
    
    void print() {
      if (this->IsInt()) {
        std::cout << this->myInt.value() << std::endl;
      } else {
        std::cout << this->myDouble.value() << std::endl;
      }
    }

    virtual Element* Clone() const;
    virtual ~Element() = default;

    // credit to https://stackoverflow.com/questions/8475940/overloading-operator-for-printing-as-a-member
    // and https://www.geeksforgeeks.org/cpp/operator-overloading-cpp/
    // for the overloading tips
    friend Element operator+(const Element& lhs, const Element& rhs);
    friend Element operator-(const Element& lhs, const Element& rhs);
    friend Element operator*(const Element& lhs, const Element& rhs);
    friend Element operator/(const Element& lhs, const Element& rhs);
    friend Element operator%(const Element& lhs, const Element& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Element& e);
};

