#include "./operation.h"
#include "./exceptions.h"
#include "./parser.h"
#include "./token.h"

#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[] ) {
  Parser parser;

  if (argc == 1) {
    std::cout << "No arguments presented" << std::endl;
    exit(1);
  }

  string flag = argv[1];

  if (flag == "-f") {
    if (argc != 3) {
      std::cerr << "File mode takes exactly one file.";
      exit(2);
    }
    ifstream file = ifstream(argv[2]);
    if (!file.is_open()) {
      std::cerr << "File could not be opened." << std::endl;
      exit(2);
    }
    int line_count = 0;
    string line;
    while (getline(file, line)) {
      line_count++;
      if (line.empty()) continue;
      unique_ptr<Element> opr;
      try {
        opr.reset(parser.Parse(line));
      } catch (...) {
        std::cerr << "Exited prematurely due to error on line " << line_count << std::endl;
        exit(line_count + 2);
      }
      std::cout << *opr << std::endl;
    }
  }
    else if (flag == "-c") {
    try {
      if (argc != 5) {
        std::cerr << "Calculator mode takes exactly: lhs op rhs.";
        exit(2);
      }
      if (Token(argv[2]).type != TokenType::Number)   { throw InvalidElement("Invalid lhs"); }
      if (Token(argv[3]).type != TokenType::Operator) { throw InvalidOperator("Invalid operator"); }
      if (Token(argv[4]).type != TokenType::Number)   { throw InvalidElement("Invalid rhs"); }
      string expr = string(argv[2]) + " " + argv[3] + " " + argv[4];
      unique_ptr<Element> opr(parser.Parse(expr));
      std::cout << *opr << std::endl;
    } catch (InvalidElement&) {
      std::cerr << "Invalid Element!";
      exit(3);
    } catch (InvalidOperator&) {
      std::cerr << "Invalid Operator!";
      exit(4);
    } catch (InvalidEquationStructure&) {
      std::cerr << "Invalid Equation!";
      exit(6);
    } catch (DivideByZeroError&) {
      std::cerr << "Math Error occurred.";
      exit(5);
    } catch (ModuloByDoubleError&) {
      std::cerr << "Math Error occurred.";
      exit(5);
    }
  }
  else {
    for (int i = 1; i < argc; i++) {
      unique_ptr<Element> opr;
      try {
        opr.reset(parser.Parse(argv[i]));
      } catch (...) {
        exit(2 + i);
      }

      string eq = argv[i];
      size_t b = eq.find_first_not_of(" \t");
      size_t e = eq.find_last_not_of(" \t");
      eq = eq.substr(b, e - b + 1);

      std::cout << eq << " = " << *opr << std::endl;
    }
  }

  exit(0);
}
