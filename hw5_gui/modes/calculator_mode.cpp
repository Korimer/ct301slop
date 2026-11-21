#include "modes.h"
#include "../exceptions.h"
#include "../operation.h"
#include "../token.h"

#include <iostream>
#include <memory>
#include <string>
using namespace std;

int RunCalculatorMode(Parser& parser, int argc, char* argv[]) {
  if (argc != 5) {
    cerr << "Calculator mode takes exactly: lhs op rhs.";
    return 2;
  }

  try {
    if (Token(argv[2]).type != TokenType::Number)   { throw InvalidElement("Invalid lhs"); }
    if (Token(argv[3]).type != TokenType::Operator) { throw InvalidOperator("Invalid operator"); }
    if (Token(argv[4]).type != TokenType::Number)   { throw InvalidElement("Invalid rhs"); }

    string expr = string(argv[2]) + " " + argv[3] + " " + argv[4];
    unique_ptr<Element> opr(parser.Parse(expr));
    cout << *opr << endl;
  } catch (InvalidElement&) {
    cerr << "Invalid Element!";
    return 3;
  } catch (InvalidOperator&) {
    cerr << "Invalid Operator!";
    return 4;
  } catch (InvalidEquationStructure&) {
    cerr << "Invalid Equation!";
    return 6;
  } catch (DivideByZeroError&) {
    cerr << "Math Error occurred.";
    return 5;
  } catch (ModuloByDoubleError&) {
    cerr << "Math Error occurred.";
    return 5;
  }
  return 0;
}
