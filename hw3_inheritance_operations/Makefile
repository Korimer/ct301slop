# Compiler
GPP = g++

# Compilation flags
REQUIRED = -Wall -Wextra -Werror -Wfatal-errors
# You can Modify the Compiler below Compiler 
GPPFlags = $(REQUIRED) -std=c++20
Debug = -g

# source and output names
HWNUM = HW3

# Rename this to the name of your main file
MAIN = calc.cpp
SRC = $(filter-out $(MAIN), $(wildcard *.cpp))
HEADER =  $(wildcard *.h)
OBJ = $(SRC:.cpp=.o)

#Update this with your first and last name
TARNAME = kaden_love
TARFULLNAME = $(HWNUM)_$(TARNAME).tar

# Target Name. This will be the name of the executable created by running "Make"
TARGET = calculator
# The DEFAULT_GOAL variable will make it so that running "make" without any arguments will run "make calculator"
.DEFAULT_GOAL := $(TARGET)

# compile
$(TARGET): $(HWNUM).a
	$(GPP) $(GPPFlags) -o $(TARGET) $(MAIN) $<

%.o: %.cpp $(HEADER)
	$(GPP) $(GPPFlags) -c $< -o $@

$(HWNUM).a: $(OBJ)
	ar -rcs $(HWNUM).a $^

# clean
# Running make clean should clean up any unnecessary components
clean:
	rm -f $(TARGET) *.o *.a $(TARFULLNAME)
	@echo "Removed all object files."

# Debug option "make debug". This enables the GNU Debugger "gdb"
debug: $(SRC)
	$(GPP) $(GPPFlags) ($SRC) $(Debug) -o $(TARGET)
	@echo "Compiled Debug"

package:
	tar -c Makefile $(SRC) $(MAIN) $(HEADER) -f $(TARFULLNAME)
	@echo "Packaged all source, header, and Makefile files into $(HWNUM)_$(TARNAME).tar"
