#include "../parser.h"

// Claude helped with reorganization splitting these into different files
// Didn't realize I could have multiple files contribute to a single header
// Though that's somewhat intuitive in hindsight....
int RunCalculatorMode(Parser& parser, int argc, char* argv[]);
int RunFileMode(Parser& parser, int argc, char* argv[]);
int RunGuiMode(Parser& parser);
int RunExpressionMode(Parser& parser, int argc, char* argv[]);
