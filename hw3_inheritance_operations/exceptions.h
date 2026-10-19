#pragma once

#include <stdexcept>

class InvalidElement : public std::invalid_argument {
  public:
    using std::invalid_argument::invalid_argument;
};

class InvalidOperator : public std::invalid_argument {
  public:
    using std::invalid_argument::invalid_argument;
};

class InsufficientArgumentCount : public std::invalid_argument {
  public:
    using std::invalid_argument::invalid_argument;
};

class DivideByZeroError : public std::domain_error {
  public:
    using std::domain_error::domain_error;
};

class ModuloByDoubleError : public std::domain_error {
  public:
    using std::domain_error::domain_error;
};
