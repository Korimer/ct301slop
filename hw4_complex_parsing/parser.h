#pragma once

#include "token.h"
#include "element.h"
#include "operator.h"

#include <cstddef>
#include <memory>
#include <stack>
#include <string>
#include <vector>

class Parser {
  private:
    std::stack<std::unique_ptr<Element>> elements = std::stack<std::unique_ptr<Element>>();
    std::stack<std::unique_ptr<Operator>> operators = std::stack<std::unique_ptr<Operator>>();

    void reset();

    void next(const Token& token);
    void reduce();

    void opnParen();
    void closeParen();
    void num();
    void op();

  public:
    Parser() = default;
    Element* Parse(const std::string& equationStr);
};
