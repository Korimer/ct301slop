#include "modes.h"
#include "../exceptions.h"
#include "../operation.h"
#include <cstddef>

#define SDL_MAIN_HANDLED   // we have our own main(); avoids SDL's Windows main() shim
#include <SDL.h>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct HistoryEntry {
  string expr;
  string result;
  bool   is_error;
};

bool Evaluate(Parser& parser, const string& expr, string& out) {
  try {
    unique_ptr<Element> opr(parser.Parse(expr));
    ostringstream ss;
    ss << *opr;
    out = ss.str();
    return true;
  } catch (const std::exception& e) {
    out = e.what();
  } catch (...) {
    out = "Unknown error.";
  }
  return false;
}

// Draws the calculator UI for one frame.
void DrawCalculator(bool& shouldExit) { //Parser& parser, string& input, vector<HistoryEntry>& history) {
  ImGuiIO& io = ImGui::GetIO();
  ImGui::SetNextWindowPos(ImVec2(0, 0));
  ImGui::SetNextWindowSize(io.DisplaySize);

  bool open = true;
  // If I set NoDecoration here, it removes the built-in title
  // But it seems like some operating systems don't include the built-in title bar by default
  // So I'll keep it here for compatibility (and too bad if it has a double title bar)
  ImGui::Begin("Calculator", &open,
      ImGuiWindowFlags_NoMove |
      ImGuiWindowFlags_NoResize |
      ImGuiWindowFlags_NoCollapse |
      ImGuiWindowFlags_NoSavedSettings);

  ImGui::Text("Hi!!");
  ImGui::End();

  if (!open)
    shouldExit = true;
}

// Referenced extremely closely to the imgui example files
// https://github.com/ocornut/imgui/blob/master/examples/example_sdl2_sdlrenderer2/main.cpp
bool imguiSpinUp(SDL_Window*& window, SDL_Renderer*& renderer) {
  // Create window with SDL_Renderer graphics context
  float main_scale = ImGui_ImplSDL2_GetContentScaleForDisplay(0);
  SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
  window = SDL_CreateWindow("Dear ImGui SDL2+SDL_Renderer example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)(1280 * main_scale), (int)(800 * main_scale), window_flags);
  if (window == nullptr)
  {
    printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
    return 1;
  }
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr)
  {
    SDL_Log("Error creating SDL_Renderer!");
    return 1;
  }
  //SDL_RendererInfo info;
  //SDL_GetRendererInfo(renderer, &info);
  //SDL_Log("Current SDL_Renderer: %s", info.name);

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGuiStyle& style = ImGui::GetStyle();
  ImGui::StyleColorsDark();
  //ImGui::StyleColorsLight();
  //style.FontSizeBase = 16.0f;           // Default to 13.0f when unspecified, which allows crisp legacy font for non-4K screens.
  style.FrameRounding = 3.0f;
  style.GrabRounding = 3.0f;

  // Setup scaling
  style.ScaleAllSizes(main_scale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
  style.FontScaleDpi = main_scale;        // Set initial font scale. (in docking branch: using io.ConfigDpiScaleFonts=true automatically overrides this for every window depending on the current monitor)

  // Setup Platform/Renderer backends
  ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
  ImGui_ImplSDLRenderer2_Init(renderer);

  return 0;
}

void imguiRunLoop(SDL_Window*& window, SDL_Renderer*& renderer) {
  ImGuiIO& io = ImGui::GetIO();

  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  // Main loop
  bool done = false;
  while (!done)
  {
    // Poll and handle events (inputs, window resize, etc.)
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT)
        done = true;
      if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
        done = true;
    }
    if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED)
    {
      SDL_Delay(10);
      continue;
    }

    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    DrawCalculator(done);

    ImGui::Render();
    SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
    SDL_RenderClear(renderer);
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
    SDL_RenderPresent(renderer);

  }
}

int RunGuiMode(Parser& parser) {
  if (false) {
    parser.Parse("lol");
  }
  SDL_Window* window;
  SDL_Renderer* renderer;

  imguiSpinUp(window, renderer);

  Parser baseParser = Parser();
  vector<HistoryEntry> history = vector<HistoryEntry>();
  string input = "lol";

  imguiRunLoop(window, renderer);

  //DrawCalculator(baseParser, input, history);


  return 0;
}
