#include "modes.h"
#include "../operation.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
using namespace std;

int RunFileMode(Parser& parser, int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "File mode takes exactly one file.";
    return 2;
  }

  ifstream file(argv[2]);
  if (!file.is_open()) {
    cerr << "File could not be opened." << endl;
    return 2;
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
      cerr << "Exited prematurely due to error on line " << line_count << endl;
      return line_count + 2;
    }
    cout << *opr << endl;
  }
  return 0;
}
