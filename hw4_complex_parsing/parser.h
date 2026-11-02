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
    std::stack<Element> elements = std::stack<Element>();
    std::stack<Operator> operators = std::stack<Operator>();

    void reset();

    void next(const Token& token);

    void opnParen();
    void closeParen();
    void num();
    void op();

  public:
    Parser() = default;
    Element* Parse(const std::string& equationStr);
};
