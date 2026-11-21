# Makefile generated via claude, double-checked by me

# Depends on sdl2 -
# On linux, libsdl2-dev
# On windows, mingw-w64-x86_64-SDL2


GPP     = g++
TARGET  = calculator
MAIN    = calc.cpp
HWNUM   = HW5
TARNAME = kaden_love

SRC    = $(filter-out $(MAIN), $(wildcard *.cpp))
HEADER = $(wildcard *.h)
OBJ    = $(SRC:.cpp=.o)

# ImGui sources, bundled in ./imgui
IMGUI     = imgui
IMGUI_OBJ = $(addprefix $(IMGUI)/, imgui.o imgui_draw.o imgui_tables.o imgui_widgets.o \
            backends/imgui_impl_sdl2.o backends/imgui_impl_sdlrenderer2.o)

SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LIBS   := $(shell sdl2-config --libs)

STRICT = -Wall -Wextra -Werror -Wfatal-errors -std=c++20
INC    = -I$(IMGUI) -I$(IMGUI)/backends $(SDL_CFLAGS)

$(TARGET): $(MAIN) $(HEADER) $(OBJ) $(IMGUI_OBJ)
	$(GPP) $(STRICT) $(INC) $(MAIN) $(OBJ) $(IMGUI_OBJ) $(SDL_LIBS) -o $@

# Your code: strict flags
%.o: %.cpp $(HEADER)
	$(GPP) $(STRICT) $(INC) -c $< -o $@

# ImGui code: relaxed flags (no -Werror), takes priority over the rule above
$(IMGUI_OBJ): %.o: %.cpp
	$(GPP) -std=c++20 $(INC) -c $< -o $@

clean:
	rm -f $(TARGET) $(TARGET).exe $(OBJ) $(IMGUI_OBJ) $(HWNUM)_$(TARNAME).tar

package:
	tar -c Makefile $(SRC) $(MAIN) $(HEADER) $(IMGUI) -f $(HWNUM)_$(TARNAME).tar

.PHONY: clean package
