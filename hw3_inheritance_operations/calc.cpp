#include "./operation.h"
#include "./exceptions.h"

#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[] ) {
  vector<Operation> all_oprs;

  if (argc == 1) {
    std::cout << "No arguments presented" << std::endl;
    exit(1);
  }
  else if (argc == 2) {
    ifstream file = ifstream(argv[1]);
    if (!file.is_open()) {
      std::cerr << "File could not be opened." << std::endl;
      exit(2);
    }
    int line_count = 1;
    string line;
    while (getline(file, line)) {
      // credit to https://stackoverflow.com/a/61005054
      if (line.size() == 0) {
        continue;
      }
      try {
        all_oprs.push_back(Operation(line));
        line_count++;
      }
      catch (...) {
        if (!file.eof()) {
          std::cerr << "Exited prematurely due to error on line " << line_count << std::endl;
          exit(line_count+2);
        }
        break;
      }
    }

    for (size_t i=0; i<all_oprs.size(); i++) {
      try {
        std::cout << all_oprs[i].compute() << std::endl;
      }
      catch (...) {
        exit(i+3);
      }
    }
  }
  else if (argc == 4) {
    try {
      Element lhs = string(argv[1]);
      Operator op = string(argv[2]);
      Element rhs = string(argv[3]);
      Operation opr = Operation(lhs, op, rhs);
      std::cout << opr.compute() << std::endl;
    } catch (InvalidElement&) {
      std::cerr << "Invalid Element!";
      exit(3);
    } catch (InvalidOperator&) {
      std::cerr << "Invalid Operator!";
      exit(4);
    } catch (DivideByZeroError&) {
      std::cerr << "Math Error occurred.";
      exit(5);
    } catch (ModuloByDoubleError&) {
      std::cerr << "Math Error occurred.";
      exit(5);
    }
  }
  else {
    std::cerr << "Incorrect argument count. Submit 0, 1, or 3.";
    exit(2);
  }


  exit(0);
} 
