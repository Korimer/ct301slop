#include "./parser.h"
#include "./modes/modes.h"

#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
  Parser parser;

  if (argc == 1) {
    cout << "No arguments presented" << endl;
    return 1;
  }

  string flag = argv[1];

  if (flag == "-f") return RunFileMode(parser, argc, argv);
  if (flag == "-c") return RunCalculatorMode(parser, argc, argv);
  if (flag == "-g") return RunGuiMode(parser);

  return RunExpressionMode(parser, argc, argv);
}
