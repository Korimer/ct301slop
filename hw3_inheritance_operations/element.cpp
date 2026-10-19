#include "./element.h"
#include "exceptions.h"
#include <iostream>
#include <optional>
#include <regex>

using namespace std;

double Element::Value() const {
  if (this->IsInt()) { return this->getInt(); }
  else { return this->getDouble(); }
}
int Element::IntValue() const {
  return static_cast<int>(this->Value());
}
double Element::DoubleValue() const {
  return static_cast<double>(this->Value());
}
void Element::Value(double newVal) {
  if (this->IsInt()) {
    this->myInt = static_cast<int>(newVal);
    this->myDouble = nullopt;
  } else {
    this->myDouble = static_cast<double>(newVal);
    this->myInt = nullopt;
  }
}
void Element::ChangeType() {
  if (this->IsInt()) {
    this->myDouble = static_cast<double>(this->getInt());
    this->amIInt = false;
    this->myInt = nullopt;
  } else {
    this->myInt = static_cast<int>(this->getDouble());
    this->amIInt = true;
    this->myDouble = nullopt;
  }
}


regex intregex = regex("^\\-?\\d+$");
regex doubleregex = regex("^\\-?\\d*\\.\\d+$");

Element::Element(const std::string &s) {
  if (std::regex_match(s, intregex)) {
    amIInt = true;
    myInt = std::stoi(s);
    myDouble = std::nullopt;
  } 
  else if (std::regex_match(s, doubleregex)) {
    amIInt = false;
    myInt = std::nullopt;
    myDouble = std::stod(s);
  } 
  else {
    throw InvalidElement("String is neither a valid int nor a double format.");
  }
}

bool Element::canConvertToElement(const std::string &s) {
  if (regex_match(s, intregex)) {
    return true;
  }
  if (regex_match(s, doubleregex)) {
    return true;
  }
  else {
    return false;
  }
}

void isNotZero(const Element& rhs) {
  if ((rhs.IsInt() && (rhs.getInt() == 0)) || (rhs.IsDouble() && (rhs.getDouble() == 0.0))) {
    throw DivideByZeroError("rhs is zero on division or modulo!");
  }
}

Element* Element::Clone() const {
  return new Element(*this);
}

Element operator+(const Element& lhs, const Element& rhs) {
  Element value = lhs.DoubleValue() + rhs.DoubleValue();
  if (lhs.IsInt() && rhs.IsInt()) {
    value.ChangeType();
  }
  return value;
}

Element operator-(const Element& lhs, const Element& rhs) {
  Element value = lhs.DoubleValue() - rhs.DoubleValue();
  if (lhs.IsInt() && rhs.IsInt()) {
    value.ChangeType();
  }
  return value;
}

Element operator*(const Element& lhs, const Element& rhs) {
  Element value = lhs.DoubleValue() * rhs.DoubleValue();
  if (lhs.IsInt() && rhs.IsInt()) {
    value.ChangeType();
  }
  return value;
}

Element operator/(const Element& lhs, const Element& rhs) {
  isNotZero(rhs);
  Element value = lhs.DoubleValue() / rhs.DoubleValue();
  if (lhs.IsInt() && rhs.IsInt()) {
    value.ChangeType();
  }
  return value;
}

Element operator%(const Element& lhs, const Element& rhs) {
  isNotZero(rhs);
  if (lhs.IsDouble() && rhs.IsDouble()) {
    throw ModuloByDoubleError("Attempted to modulo by a double!");
  }

  Element value = Element(lhs.IntValue() % rhs.IntValue());
  return value;
}

ostream& operator<<(std::ostream& os, const Element& e) {
  if (e.amIInt) {
    os << *(e.myInt);
  } else {
    os << *(e.myDouble);
  }
  return os;
}
