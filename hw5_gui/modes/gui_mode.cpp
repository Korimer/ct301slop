#include "modes.h"
#include "../exceptions.h"
#include "../operation.h"

#define SDL_MAIN_HANDLED   // we have our own main(); avoids SDL's Windows main() shim
#include <SDL.h>

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#include <cstdio>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// Not used yet; will be needed once there's an "=" button.
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
void DrawCalculator(string& input, bool& shouldExit) {
  ImGuiIO& io = ImGui::GetIO();
  ImGuiStyle& style = ImGui::GetStyle();
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

  ImGui::Text("%s", input.empty() ? "0" : input.c_str());
  ImGui::Separator();

  static const char* keys[4][4] = {
    {"7", "8", "9", "/"},
    {"4", "5", "6", "*"},
    {"1", "2", "3", "-"},
    {"0", ".", "C", "+"},
  };
  const float btnW = (ImGui::GetContentRegionAvail().x - 3 * style.ItemSpacing.x) / 4;
  const float btnH = ImGui::GetFrameHeight() * 1.8f;

  for (int r = 0; r < 4; r++) {
    for (int c = 0; c < 4; c++) {
      if (c > 0) ImGui::SameLine();
      if (ImGui::Button(keys[r][c], ImVec2(btnW, btnH))) {
        if (string(keys[r][c]) == "C") input.clear();
        else                           input += keys[r][c];
      }
    }
  }

  ImGui::End();

  if (!open)
    shouldExit = true;
}

// Referenced extremely closely to the imgui example files
// https://github.com/ocornut/imgui/blob/master/examples/example_sdl2_sdlrenderer2/main.cpp
bool imguiSpinUp(SDL_Window*& window, SDL_Renderer*& renderer) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
    printf("Error: SDL_Init(): %s\n", SDL_GetError());
    return false;
  }

  // Create window with SDL_Renderer graphics context
  float main_scale = ImGui_ImplSDL2_GetContentScaleForDisplay(0);
  SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
  window = SDL_CreateWindow("Calculator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)(360 * main_scale), (int)(480 * main_scale), window_flags);
  if (window == nullptr)
  {
    printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
    SDL_Quit();
    return false;
  }
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr)
  {
    SDL_Log("Error creating SDL_Renderer!");
    SDL_DestroyWindow(window);
    SDL_Quit();
    return false;
  }

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGuiStyle& style = ImGui::GetStyle();
  ImGui::StyleColorsDark();
  style.FrameRounding = 3.0f;
  style.GrabRounding = 3.0f;

  // Setup scaling
  style.ScaleAllSizes(main_scale);
  style.FontScaleDpi = main_scale;

  // Setup Platform/Renderer backends
  ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
  ImGui_ImplSDLRenderer2_Init(renderer);

  return true;
}

void imguiShutdown(SDL_Window* window, SDL_Renderer* renderer) {
  ImGui_ImplSDLRenderer2_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void imguiRunLoop(SDL_Window*& window, SDL_Renderer*& renderer, string& input) {
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

    DrawCalculator(input, done);

    ImGui::Render();
    SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
    SDL_RenderClear(renderer);
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
    SDL_RenderPresent(renderer);
  }
}

int RunGuiMode(Parser& parser) {
  (void)parser;   // will be used when the "=" button is added

  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  if (!imguiSpinUp(window, renderer))
    return 1;

  string input;
  imguiRunLoop(window, renderer, input);

  imguiShutdown(window, renderer);
  return 0;
}
