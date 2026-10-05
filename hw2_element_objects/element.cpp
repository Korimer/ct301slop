#include "./element.h"
#include <iostream>
#include <optional>

using namespace std;

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

