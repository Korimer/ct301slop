# pragma once
#include "number.h"

# include <optional>
# include <string>

using namespace std;


class BasicOperator {
  private:
    string chr;
  public:
    BasicOperator(string op);

    static bool is_operator(string chr);
    Number operate(Number lhs, Number rhs);
};

class Operation {
  private:
    Number lhs;
    BasicOperator op;
    Number rhs;

  public:
    Operation(Number lhs, BasicOperator op, Number rhs):
      lhs(lhs), op(op), rhs(rhs) {}

    Number compute();
};

optional<Number> convertToNumber(string s);
optional<BasicOperator> convertToBasicOperation(string s);
