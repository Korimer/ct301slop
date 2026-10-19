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
  if (lhs.amIInt && rhs.amIInt) {
    return Element(lhs.myInt.value() + rhs.myInt.value());
  } else if (lhs.amIInt && !rhs.amIInt) {
    return Element(static_cast<double>(lhs.myInt.value()) + rhs.myDouble.value());
  } else if (!lhs.amIInt && rhs.amIInt) {
    return Element(lhs.myDouble.value() + static_cast<double>(rhs.myInt.value()));
  } else {
    return Element(lhs.myDouble.value() + rhs.myDouble.value());
  }
}

Element operator-(const Element& lhs, const Element& rhs) {
  if (lhs.amIInt && rhs.amIInt) {
    return Element(lhs.myInt.value() - rhs.myInt.value());
  } else if (lhs.amIInt && !rhs.amIInt) {
    return Element(static_cast<double>(lhs.myInt.value()) - rhs.myDouble.value());
  } else if (!lhs.amIInt && rhs.amIInt) {
    return Element(lhs.myDouble.value() - static_cast<double>(rhs.myInt.value()));
  } else {
    return Element(lhs.myDouble.value() - rhs.myDouble.value());
  }
}

Element operator*(const Element& lhs, const Element& rhs) {
  if (lhs.amIInt && rhs.amIInt) {
    return Element(lhs.myInt.value() * rhs.myInt.value());
  } else if (lhs.amIInt && !rhs.amIInt) {
    return Element(static_cast<double>(lhs.myInt.value()) * rhs.myDouble.value());
  } else if (!lhs.amIInt && rhs.amIInt) {
    return Element(lhs.myDouble.value() * static_cast<double>(rhs.myInt.value()));
  } else {
    return Element(lhs.myDouble.value() * rhs.myDouble.value());
  }
}

Element operator/(const Element& lhs, const Element& rhs) {
  isNotZero(rhs);
  if (lhs.amIInt && rhs.amIInt) {
    return Element(lhs.myInt.value() / rhs.myInt.value());
  } else if (lhs.amIInt && !rhs.amIInt) {
    return Element(static_cast<double>(lhs.myInt.value()) / rhs.myDouble.value());
  } else if (!lhs.amIInt && rhs.amIInt) {
    return Element(lhs.myDouble.value() / static_cast<double>(rhs.myInt.value()));
  } else {
    return Element(lhs.myDouble.value() / rhs.myDouble.value());
  }
}

Element operator%(const Element& lhs, const Element& rhs) {
  isNotZero(rhs);
  if (lhs.IsInt() || rhs.IsInt()) {
    throw ModuloByDoubleError("Attempted to modulo by a double!");
  }
  return Element(lhs.IntValue() % rhs.IntValue());
}

ostream& operator<<(std::ostream& os, const Element& e) {
  if (e.amIInt) {
    os << *(e.myInt);
  } else {
    os << *(e.myDouble);
  }
  return os;
}
