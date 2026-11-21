#include "modes.h"
#include "../operation.h"

#include <iostream>
#include <memory>
#include <string>
using namespace std;

int RunExpressionMode(Parser& parser, int argc, char* argv[]) {
  for (int i = 1; i < argc; i++) {
    unique_ptr<Element> opr;
    try {
      opr.reset(parser.Parse(argv[i]));
    } catch (...) {
      return 2 + i;
    }

    string eq = argv[i];
    size_t b = eq.find_first_not_of(" \t");
    size_t e = eq.find_last_not_of(" \t");
    eq = eq.substr(b, e - b + 1);

    cout << eq << " = " << *opr << endl;
  }
  return 0;
}
