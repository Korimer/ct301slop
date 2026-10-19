# pragma once

#include "element.h"
#include <string>

class Operator {
  private:
    std::string chr;
  public:
    Operator(std::string op);

    static bool is_operator(std::string chr);
    Element operate(Element lhs, Element rhs);

    bool requires_nonzero_rhs();
    bool requires_int();
};

