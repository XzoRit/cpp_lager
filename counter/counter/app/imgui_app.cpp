#include <counter/view/model/model.hpp>

#include <counter/view/gui/imgui.hpp>

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
using namespace std::string_literals;
struct sdl
{
    sdl()
    {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
            throw std::runtime_error{"SDL_Init failed "s + SDL_GetError()};
    }
    ~sdl() noexcept
    {
        SDL_Quit();
    }
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
        SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE |
                                                         SDL_WINDOW_MAXIMIZED | SDL_WINDOW_ALLOW_HIGHDPI);
        handle = SDL_CreateWindow("counter imgui app",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  1280,
                                  720,
                                  window_flags);
        if (!handle)
            throw std::runtime_error{"SDL_CreateWindow failed "s + SDL_GetError()};
    }
    ~sdl_window() noexcept
    {
        SDL_DestroyWindow(handle);
    }
    SDL_Window* handle{nullptr};
};

struct sdl_gl_context
{
    explicit sdl_gl_context(SDL_Window* window) : gl_context{SDL_GL_CreateContext(window)}
    {
        if (!gl_context)
            throw std::runtime_error{"SDL_GL_CreateContext failed "s + SDL_GetError()};

        SDL_GL_MakeCurrent(window, gl_context);
        SDL_GL_SetSwapInterval(1);
    }
    ~sdl_gl_context() noexcept
    {
        SDL_GL_DeleteContext(gl_context);
    }

    SDL_GLContext gl_context{};
};

struct imgui_context
{
    imgui_context(SDL_Window* window, SDL_GLContext gl_context) : win{window}, gl_ctx{gl_context}
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
        const auto size{ImGui::GetIO().DisplaySize};
        glViewport(0, 0, (int)size.x, (int)size.y);

        glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(win);
    }
    SDL_Window* win{nullptr};
    SDL_GLContext gl_ctx{};
};
} // namespace
int main()
{
    try
    {
        [[maybe_unused]] sdl sdl_context{};
        sdl_window window{};
        sdl_gl_context gl_context{window.handle};
        imgui_context gui_context{window.handle, gl_context.gl_context};

        auto loop = lager::sdl_event_loop{};
        auto store = lager::make_store<xzr::counter::action::action>(xzr::counter::view::model::model{},
                                                                     xzr::counter::view::model::update,
                                                                     lager::with_sdl_event_loop{loop});

        loop.run(
            [&](const SDL_Event& ev) {
                ImGui_ImplSDL2_ProcessEvent(&ev);
                return (ev.type != SDL_QUIT);
            },
            [&](auto&&) {
                gui_context.new_frame();
                {
                    xzr::counter::view::imgui::draw(store, store.get());
                    ImGui::ShowDemoWindow();
                }
                gui_context.render();
                return true;
            });
    }
    catch (const std::exception& e)
    {
        return 1;
    }
    catch (...)
    {
        return 2;
    }
    return 0;
}
