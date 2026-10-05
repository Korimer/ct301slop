#include "./element.h"
#include <iostream>
#include <optional>
#include <regex>

using namespace std;

// todo:
const double Value();
const int IntValue();
const double DoubleValue();
void Value(double newVal);
void ChangeType();


regex intregex = regex("^\\-?\\d+$");
regex floatregex = regex("^\\-?\\d*\\.\\d+$");

Element::Element(const std::string &s) {
  if (std::regex_match(s, intregex)) {
    amIInt = true;
    myInt = std::stoi(s);
    myFloat = std::nullopt;
  } 
  else if (std::regex_match(s, floatregex)) {
    amIInt = false;
    myInt = std::nullopt;
    myFloat = std::stof(s);
  } 
  else {
    throw std::invalid_argument("String is neither a valid int nor a float format.");
  }
}

bool Element::canConvertToElement(const std::string &s) {
  if (regex_match(s, intregex)) {
    int as_int = stoi(s);
    return true;
  }
  if (regex_match(s, floatregex)) {
    float as_float = stof(s);
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
    return Element(static_cast<float>(lhs.myInt.value()) + rhs.myFloat.value());
  } else if (!lhs.amIInt && rhs.amIInt) {
    return Element(lhs.myFloat.value() + static_cast<float>(rhs.myInt.value()));
  } else {
    return Element(lhs.myFloat.value() + rhs.myFloat.value());
  }
}

Element operator-(const Element& lhs, const Element& rhs) {
  if (lhs.amIInt && rhs.amIInt) {
    return Element(lhs.myInt.value() - rhs.myInt.value());
  } else if (lhs.amIInt && !rhs.amIInt) {
    return Element(static_cast<float>(lhs.myInt.value()) - rhs.myFloat.value());
  } else if (!lhs.amIInt && rhs.amIInt) {
    return Element(lhs.myFloat.value() - static_cast<float>(rhs.myInt.value()));
  } else {
    return Element(lhs.myFloat.value() - rhs.myFloat.value());
  }
}

Element operator*(const Element& lhs, const Element& rhs) {
  if (lhs.amIInt && rhs.amIInt) {
    return Element(lhs.myInt.value() * rhs.myInt.value());
  } else if (lhs.amIInt && !rhs.amIInt) {
    return Element(static_cast<float>(lhs.myInt.value()) * rhs.myFloat.value());
  } else if (!lhs.amIInt && rhs.amIInt) {
    return Element(lhs.myFloat.value() * static_cast<float>(rhs.myInt.value()));
  } else {
    return Element(lhs.myFloat.value() * rhs.myFloat.value());
  }
}

Element operator/(const Element& lhs, const Element& rhs) {
  if (lhs.amIInt && rhs.amIInt) {
    return Element(lhs.myInt.value() / rhs.myInt.value());
  } else if (lhs.amIInt && !rhs.amIInt) {
    return Element(static_cast<float>(lhs.myInt.value()) / rhs.myFloat.value());
  } else if (!lhs.amIInt && rhs.amIInt) {
    return Element(lhs.myFloat.value() / static_cast<float>(rhs.myInt.value()));
  } else {
    return Element(lhs.myFloat.value() / rhs.myFloat.value());
  }
}

Element operator%(const Element& lhs, const Element& rhs) {
  if (lhs.amIInt && rhs.amIInt) {
    return Element(lhs.myInt.value() % rhs.myInt.value());
  }
  else {
    std::cerr << "Error: attempted to use modulo operator on a float" << std::endl;
    exit(1);
  }
}

