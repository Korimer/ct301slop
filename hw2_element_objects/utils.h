# pragma once
#include "element.h"

# include <optional>
# include <string>

class BasicOperator {
  public:
    std::string chr;
    BasicOperator(std::string op);

    static bool is_operator(std::string chr);
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

std::optional<Element> convertToElement(std::string s);
std::optional<BasicOperator> convertToBasicOperation(std::string s);
