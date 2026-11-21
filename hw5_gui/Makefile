# Makefile generated via claude, double-checked by me

GPP     = g++
TARGET  = calculator
MAIN    = calc.cpp
HWNUM   = HW5
TARNAME = kaden_love

SRC    = $(filter-out $(MAIN), $(wildcard *.cpp modes/*.cpp))
HEADER = $(wildcard *.h modes/*.h)
OBJ    = $(SRC:.cpp=.o)

# ImGui sources, bundled in ./imgui
IMGUI     = imgui
IMGUI_OBJ = $(addprefix $(IMGUI)/, imgui.o imgui_draw.o imgui_tables.o imgui_widgets.o \
            backends/imgui_impl_sdl2.o backends/imgui_impl_sdlrenderer2.o)

# ---------------------------------------------------------------------------
# SDL2 detection: warn loudly if SDL.h / libsdl2 is missing
#
# Windows (MinGW): install SDL2 through MSYS2, then build from the
# "MSYS2 MinGW 64-bit" shell (not the plain MSYS shell), so that g++ and
# sdl2-config both come from the mingw64 toolchain:
#     pacman -S mingw-w64-x86_64-SDL2 mingw-w64-x86_64-toolchain
# ---------------------------------------------------------------------------
SDL_CONFIG := $(shell command -v sdl2-config 2>/dev/null)

ifeq ($(SDL_CONFIG),)
  SDL_MISSING := 1
else
  SDL_CFLAGS := $(shell sdl2-config --cflags)
  SDL_LIBS   := $(shell sdl2-config --libs)
  # sdl2-config exists, but make sure SDL.h is really reachable
  SDL_HEADER_OK := $(shell echo '\#include <SDL.h>' | $(GPP) $(SDL_CFLAGS) -E -x c++ - >/dev/null 2>&1 && echo yes)
  ifneq ($(SDL_HEADER_OK),yes)
    SDL_MISSING := 1
  endif
endif

ifeq ($(SDL_MISSING),1)
  $(warning ################################################################)
  $(warning #                                                              #)
  $(warning #   WARNING: SDL.h NOT FOUND -- libsdl2 IS NOT INSTALLED!      #)
  $(warning #                                                              #)
  $(warning #   You need to install the SDL2 development package:          #)
  $(warning #     Debian/Ubuntu:  sudo apt install libsdl2-dev             #)
  $(warning #     Fedora:         sudo dnf install SDL2-devel              #)
  $(warning #     Arch:           sudo pacman -S sdl2                      #)
  $(warning #     macOS - brew:   brew install sdl2                        #)
  $(warning #     Windows MinGW:  pacman -S mingw-w64-x86_64-SDL2          #)
  $(warning #                       ...run from the MSYS2 MinGW64 shell    #)
  $(warning #                                                              #)
  $(warning #   The build will almost certainly fail without it.           #)
  $(warning #                                                              #)
  $(warning #   ...Please note this is a prerequisite for imgui,           #)
  $(warning #   as opposed to something missing within the code            #)
  $(warning #   that I have submitted.                                     #)
  $(warning #                                                              #)
  $(warning ################################################################)
endif

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
	tar -c Makefile README.md $(SRC) $(MAIN) $(HEADER) $(IMGUI) -f $(HWNUM)_$(TARNAME).tar

.PHONY: clean package
