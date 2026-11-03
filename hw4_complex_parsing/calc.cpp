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
  vector<unique_ptr<Element>> all_oprs;

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
      try {
        all_oprs.emplace_back(parser.Parse(line));
      } catch (...) {
        std::cerr << "Exited prematurely due to error on line " << line_count << std::endl;
        exit(line_count + 2);
      }
    }

    for (size_t i=0; i<all_oprs.size(); i++) {
      std::cout << all_oprs[i]->Value() << std::endl;
    }
  }
  else {
    string expr;
    vector<int> tokenToArg;
    for (int i = 1; i < argc; i++) {
      expr += string(argv[i]) + " ";
      istringstream words = istringstream(argv[i]);
      string w;
      while (words >> w) { tokenToArg.push_back(i); }
    }
    try {
      unique_ptr<Element> opr(parser.Parse(expr));
      std::cout << opr->Value() << std::endl;
    } catch (...) {
      int t = parser.ErrorIndex();
      int arg = (t >= 1 && t <= (int)tokenToArg.size()) ? tokenToArg[t - 1] : argc - 1;
      exit(2 + arg);
    }
  }

  exit(0);
}
