# pragma once

#include "element.h"
#include <string>

class Operator {
  private:
    char chr;

    static char toChar(std::string);
  public:
    Operator(std::string op):
      Operator(toChar(op)) {};
    Operator(char op);

    static bool is_operator(const char& chr);
    static bool is_operator(const std::string& str);
    Element operate(const Element& lhs, const Element& rhs);

    Operator* clone() const;

    bool requires_nonzero_rhs();
    bool requires_int();

    friend std::ostream& operator<<(std::ostream&, const Operator&);
};
