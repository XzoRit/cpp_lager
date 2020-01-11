#include <tennis/view/imgui.hpp>

#include <lager/event_loop/sdl.hpp>
#include <lager/store.hpp>

#include <imgui.h>
#include <imgui_impl_opengl2.h>
#include <imgui_impl_sdl.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <optional>
#include <stdexcept>
#include <string>
#include <variant>

namespace
{
struct sdl
{
  sdl()
  {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
      throw std::runtime_error{ std::string{ "SDL_Init failed " } + SDL_GetError() };
  }

  ~sdl() noexcept { SDL_Quit(); }
};

struct sdl_window
{
  sdl_window()
  {
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    handle = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
  }

  ~sdl_window() noexcept { SDL_DestroyWindow(handle); }

  SDL_Window* handle{ nullptr };
};

struct sdl_gl_context
{
  explicit sdl_gl_context(SDL_Window* window)
    : gl_context{ SDL_GL_CreateContext(window) }
  {
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1);
  }

  ~sdl_gl_context() noexcept { SDL_GL_DeleteContext(gl_context); }

  SDL_GLContext gl_context{};
};

struct imgui_context
{
  imgui_context(SDL_Window* window, SDL_GLContext gl_context) : win{ window }
  {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(win, gl_context);
    ImGui_ImplOpenGL2_Init();
  }

  void new_frame()
  {
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplSDL2_NewFrame(win);
    ImGui::NewFrame();
  }

  void render()
  {
    ImGui::Render();

    ImGuiIO& io = ImGui::GetIO();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);

    const ImVec4 back_ground_color{ 0.5f, 0.5, 0.5, 0.5f };
    glClearColor(back_ground_color.x, back_ground_color.y, back_ground_color.z, back_ground_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(win);
  }

  SDL_Window* win{ nullptr };
};

void draw(imgui_context& view, int model)
{
  // Our state
  static bool show_demo_window = true;
  static bool show_another_window = false;
  static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  // 1. Show the big demo window (Most of the sample code is in
  // ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear
  // ImGui!).
  if (show_demo_window)
    ImGui::ShowDemoWindow(&show_demo_window);

  // 2. Show a simple window that we create ourselves. We use a Begin/End pair
  // to created a named window.
  {
    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and
                                   // append into it.

    ImGui::Text("This is some useful text."); // Display some text (you can use
                                              // a format strings too)
    ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our
                                                       // window open/close
                                                       // state
    ImGui::Checkbox("Another Window", &show_another_window);

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f); // Edit 1 float using a slider
                                                 // from 0.0f to 1.0f
    ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats
                                                            // representing a
                                                            // color

    if (ImGui::Button("Button")) // Buttons return true when clicked (most
                                 // widgets return true when edited/activated)
      counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text(
      "Application average %.3f ms/frame (%.1f FPS)",
      1000.0f / ImGui::GetIO().Framerate,
      ImGui::GetIO().Framerate);
    ImGui::End();
  }

  // 3. Show another simple window.
  if (show_another_window)
  {
    ImGui::Begin("Another Window", &show_another_window); // Pass a pointer to
                                                          // our bool variable
                                                          // (the window will
                                                          // have a closing
                                                          // button that will
                                                          // clear the bool when
                                                          // clicked)
    ImGui::Text("Hello from another window!");
    if (ImGui::Button("Close Me"))
      show_another_window = false;
    ImGui::End();
  }
}

std::optional<int> intent(const SDL_Event& event)
{
  if (event.type == SDL_KEYDOWN)
  {
    switch (event.key.keysym.sym)
    {
    case SDLK_UP:
      return 1;
    case SDLK_DOWN:
      return 2;
    case SDLK_SPACE:
      return 0;
    default:
      break;
    }
  }
  return std::nullopt;
}

int update(int model, int action)
{
  model = action;
  return model;
}
}
int main()
{
  [[maybe_unused]] sdl sdl_context{};
  sdl_window window{};
  sdl_gl_context gl_context{ window.handle };
  imgui_context gui_context{ window.handle, gl_context.gl_context };

  auto loop = lager::sdl_event_loop{};
  auto store = lager::make_store<int>(int{}, update, lager::with_sdl_event_loop{ loop });

  watch(
    store, [&](int prev_model, int curr_model) { draw(gui_context, curr_model); });

  // initial draw
  gui_context.new_frame();
  draw(gui_context, store.get());
  gui_context.render();

  // this the while(!done)-loop
  loop.run(
    [&](const SDL_Event& ev) {
      ImGui_ImplSDL2_ProcessEvent(&ev);
      const bool done{ ev.type != SDL_QUIT };

      gui_context.new_frame();

      if (auto act = intent(ev))
        store.dispatch(*act);

      draw(gui_context, store.get());

      gui_context.render();

      return done;
    },
    lager::poll{});

  return 0;
}
