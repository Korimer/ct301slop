#include "modes.h"
#include "../exceptions.h"
#include "../operation.h"

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

namespace {

struct HistoryEntry {
  string expr;
  string result;
  bool   is_error;
};

// Evaluates one expression. Returns true on success; `out` holds the result
// or an error message.
bool Evaluate(Parser& parser, const string& expr, string& out) {
  try {
    unique_ptr<Element> opr(parser.Parse(expr));
    ostringstream ss;
    ss << *opr;
    out = ss.str();
    return true;
  } catch (InvalidElement&) {
    out = "Invalid Element!";
  } catch (InvalidOperator&) {
    out = "Invalid Operator!";
  } catch (InvalidEquationStructure&) {
    out = "Invalid Equation!";
  } catch (DivideByZeroError&) {
    out = "Math Error occurred.";
  } catch (ModuloByDoubleError&) {
    out = "Math Error occurred.";
  } catch (...) {
    out = "Unknown error.";
  }
  return false;
}

// Draws the calculator UI for one frame.
void DrawCalculator(Parser& parser, string& input, vector<HistoryEntry>& history) {
  ImGuiIO& io = ImGui::GetIO();
  ImGui::SetNextWindowPos(ImVec2(0, 0));
  ImGui::SetNextWindowSize(io.DisplaySize);
  ImGui::Begin("Calculator", nullptr,
               ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
               ImGuiWindowFlags_NoSavedSettings);

  auto submit = [&]() {
    if (input.empty()) return;
    string out;
    bool ok = Evaluate(parser, input, out);
    history.push_back({input, out, !ok});
    if (ok) input = out;   // chain results into the next calculation
    else    input.clear();
  };

  // --- input line ---
  ImGui::SetNextItemWidth(-FLT_MIN);
  if (ImGui::InputText("##input", &input[0], input.capacity() + 1,
                       ImGuiInputTextFlags_EnterReturnsTrue |
                       ImGuiInputTextFlags_CallbackResize,
                       [](ImGuiInputTextCallbackData* d) -> int {
                         if (d->EventFlag == ImGuiInputTextFlags_CallbackResize) {
                           auto* s = static_cast<string*>(d->UserData);
                           s->resize(static_cast<size_t>(d->BufTextLen));
                           d->Buf = &(*s)[0];
                         }
                         return 0;
                       }, &input)) {
    submit();
    ImGui::SetKeyboardFocusHere(-1);   // keep focus on the input after Enter
  }

  // --- keypad ---
  static const char* keys[] = {
    "7", "8", "9", "/",
    "4", "5", "6", "*",
    "1", "2", "3", "-",
    "0", ".", "%", "+",
  };
  const float w = (ImGui::GetContentRegionAvail().x -
                   3 * ImGui::GetStyle().ItemSpacing.x) / 4.0f;
  for (int i = 0; i < 16; i++) {
    if (ImGui::Button(keys[i], ImVec2(w, 40))) {
      string k = keys[i];
      bool is_op = (k == "/" || k == "*" || k == "-" || k == "+" || k == "%");
      input += is_op ? " " + k + " " : k;   // parser expects spaces around operators
    }
    if (i % 4 != 3) ImGui::SameLine();
  }
  const float w3 = (ImGui::GetContentRegionAvail().x -
                    2 * ImGui::GetStyle().ItemSpacing.x) / 3.0f;
  if (ImGui::Button("C", ImVec2(w3, 40))) input.clear();
  ImGui::SameLine();
  if (ImGui::Button("DEL", ImVec2(w3, 40)) && !input.empty()) input.pop_back();
  ImGui::SameLine();
  if (ImGui::Button("=", ImVec2(w3, 40))) submit();

  // --- history ---
  ImGui::SeparatorText("History");
  ImGui::BeginChild("history");
  for (const auto& h : history) {
    ImGui::TextDisabled("%s", h.expr.c_str());
    if (h.is_error) ImGui::TextColored(ImVec4(1.0f, 0.4f, 0.4f, 1.0f), "  %s", h.result.c_str());
    else            ImGui::Text("  = %s", h.result.c_str());
  }
  if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) ImGui::SetScrollHereY(1.0f);
  ImGui::EndChild();

  ImGui::End();
}

}  // namespace

int RunGuiMode(Parser& parser) {
  SDL_SetMainReady();
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    cerr << "SDL_Init failed: " << SDL_GetError() << endl;
    return 1;
  }

  SDL_Window* window = SDL_CreateWindow(
      "Calculator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 380, 640,
      SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
  if (!window) {
    cerr << "SDL_CreateWindow failed: " << SDL_GetError() << endl;
    SDL_Quit();
    return 1;
  }

  SDL_Renderer* renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  if (!renderer) renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  if (!renderer) {
    cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::GetIO().IniFilename = nullptr;   // don't litter imgui.ini
  ImGui::StyleColorsDark();
  ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
  ImGui_ImplSDLRenderer2_Init(renderer);

  string input;
  vector<HistoryEntry> history;
  bool running = true;

  while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT) running = false;
      if (event.type == SDL_WINDOWEVENT &&
          event.window.event == SDL_WINDOWEVENT_CLOSE &&
          event.window.windowID == SDL_GetWindowID(window)) running = false;
    }

    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    DrawCalculator(parser, input, history);

    ImGui::Render();
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
    SDL_RenderPresent(renderer);
  }

  ImGui_ImplSDLRenderer2_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
