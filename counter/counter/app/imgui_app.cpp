#include <counter/model/model.hpp>

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
            throw std::runtime_error{std::string{"SDL_Init failed "} + SDL_GetError()};
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
        SDL_WindowFlags window_flags =
            (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
        handle =
            SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
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
    imgui_context(SDL_Window* window, SDL_GLContext gl_context) : win{window}
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

        const ImVec4 back_ground_color{0.5f, 0.5, 0.5, 0.5f};
        glClearColor(back_ground_color.x, back_ground_color.y, back_ground_color.z, back_ground_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(win);
    }

    SDL_Window* win{nullptr};
};

void draw(lager::context<xzr::counter::action::action> ctx, xzr::counter::model::model m)
{
    ImGui::Begin("Counter");

    ImGui::AlignTextToFramePadding();
    ImGui::Text("Hold to repeat:");
    ImGui::SameLine();

    float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
    ImGui::Text("%d", m.value);
    ImGui::PushButtonRepeat(true);
    if (ImGui::ArrowButton("##down", ImGuiDir_Down))
        ctx.dispatch(xzr::counter::action::decrement{});
    ImGui::SameLine(0.0f, spacing);
    if (ImGui::ArrowButton("##up", ImGuiDir_Up))
        ctx.dispatch(xzr::counter::action::increment{});
    ImGui::PopButtonRepeat();
    ImGui::SameLine();
    if (ImGui::Button("reset"))
        ctx.dispatch(xzr::counter::action::reset{});

    ImGui::End();
}

std::optional<xzr::counter::action::action> intent(const SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
            return xzr::counter::action::increment{};
        case SDLK_DOWN:
            return xzr::counter::action::decrement{};
        case SDLK_SPACE:
            return xzr::counter::action::reset{0};
        default:
            return std::nullopt;
        }
    }
    return std::nullopt;
}
} // namespace
int main()
{
    [[maybe_unused]] sdl sdl_context{};
    sdl_window window{};
    sdl_gl_context gl_context{window.handle};
    imgui_context gui_context{window.handle, gl_context.gl_context};

    auto loop = lager::sdl_event_loop{};
    auto store = lager::make_store<xzr::counter::action::action>(xzr::counter::model::model{},
                                                                 xzr::counter::model::update,
                                                                 lager::with_sdl_event_loop{loop});

    loop.run(
        [&](const SDL_Event& ev) {
            ImGui_ImplSDL2_ProcessEvent(&ev);
            return (ev.type != SDL_QUIT);
        },
        [&](auto&&) {
            gui_context.new_frame();
            {
                draw(store, store.get());
                ImGui::ShowDemoWindow();
            }
            gui_context.render();
            return true;
        });

    return 0;
}
