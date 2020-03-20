#include <tennis/model/model.hpp>
#include <tennis/view/console.hpp>

#include <lager/event_loop/manual.hpp>
#include <lager/store.hpp>
#include <lager/watch.hpp>

#include <boost/program_options.hpp>

#include <iostream>
#include <iterator>
#include <optional>

namespace po = boost::program_options;

int main(int ac, char* av[])
{
    std::cout << "tennis console app\n";

    try
    {
        po::options_description desc("tennis console app");
        desc.add_options()("help", "produce help message")("q", "quits application");
        xzr::tennis::view::console::menu::add_options(desc);

        po::variables_map vm;
        po::store(po::parse_command_line(ac, av, desc), vm);
        po::notify(vm);

        if (vm.count("help"))
        {
            std::cout << desc << "\n";
            return 0;
        }

        xzr::tennis::view::console::render tennis_render{"Alice", "Bob"};
        const auto& render = [&tennis_render](const auto& prev, const auto& current) {
            std::cout << tennis_render.draw(current);
        };

        auto store = lager::make_store<xzr::tennis::action::score_action>(xzr::tennis::model::game{},
                                                                          xzr::tennis::model::update,
                                                                          lager::with_manual_event_loop{});
        lager::watch(store, render);

        auto c = char{};
        while (std::cin >> c)
        {
            if (c == 'q')
                break;
            if (const auto act = xzr::tennis::view::console::menu::intent(c))
            {
                store.dispatch(*act);
            }
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "error: " << e.what() << "\n";
        return 1;
    }
    catch (...)
    {
        std::cerr << "Exception of unknown type!\n";
    }

    return 0;
}
