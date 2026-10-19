#pragma once

#include <stdexcept>

class InvalidElement : public std::invalid_argument { };
class InvalidOperator : public std::invalid_argument { };
class DivideByZeroError : public std::domain_error { };
class ModuloByDoubleError : public std::domain_error { };
