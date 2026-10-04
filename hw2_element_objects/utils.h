# pragma once
#include "number.h"

# include <optional>
# include <string>

using namespace std;


class BasicOperator {
  public:
    string chr;
    BasicOperator(string op);

    static bool is_operator(string chr);
    Element operate(Element lhs, Element rhs);
};

class Operation {
  private:
    Element lhs;
    BasicOperator op;
    Element rhs;

  public:
    Operation(Element lhs, BasicOperator op, Element rhs):
      lhs(lhs), op(op), rhs(rhs) {}

    bool is_valid();
    Element compute();
};

optional<Element> convertToElement(string s);
optional<BasicOperator> convertToBasicOperation(string s);
