#pragma once

#include "element.h"
#include "token.h"

#include <memory>
#include <stack>
#include <string>

class Parser {
  private:
    std::stack<std::unique_ptr<Element>> elements;
    std::stack<char> operators;
    bool expectOperand = true;

    static int precedence(char c);

    void reset();
    void reduce();
    void next(const Token& token);
    void op(const std::string& text);
    void num(const std::string& text);
    void opnParen();
    void closeParen();

  public:
    Parser() = default;

    Element* Parse(const std::string& equationStr);
};
