#include "./element.h"
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
  } else {
    this->myInt = static_cast<int>(this->getDouble());
    this->amIInt = true;
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
    throw std::invalid_argument("String is neither a valid int nor a double format.");
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
  if ((rhs.amIInt && rhs.getInt() == 0) || (!rhs.amIInt && rhs.getDouble() == 0.0)) {
    throw std::domain_error("Division by 0 attempted!");
  }
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
  if (lhs.amIInt && rhs.amIInt) {
    return Element(lhs.myInt.value() % rhs.myInt.value());
  }
  else {
    throw std::domain_error("Error: attempted to use modulo operator on a double");
  }
}

ostream& operator<<(std::ostream& os, const Element& e) {
  if (e.amIInt) {
    os << *(e.myInt);
  } else {
    os << *(e.myDouble);
  }
  return os;
}
