#include <counter/model/model.hpp>
#include <counter/view/console.hpp>

#include <lager/event_loop/manual.hpp>
#include <lager/event_loop/queue.hpp>
#include <lager/store.hpp>
#include <lager/watch.hpp>

#include <boost/program_options.hpp>

#include <iostream>
#include <iterator>
#include <optional>

namespace po = boost::program_options;

namespace
{
void render(const xzr::counter::model::model& /*prev*/, const xzr::counter::model::model& current)
{
    xzr::counter::view::console::render(current);
}
} // namespace
int main(int ac, char* av[])
{
    std::cout << "counter console app\n";

    try
    {
        po::options_description desc("options for counter console app");
        desc.add_options()("help", "produce help message")("q", "quits application");
        xzr::counter::view::console::menu::add_options(desc);

        po::variables_map vm;
        po::store(po::parse_command_line(ac, av, desc), vm);
        po::notify(vm);

        if (vm.count("help"))
        {
            std::cout << desc << "\n";
            return 0;
        }
        std::cout << desc << "\n";
        auto evt_q = lager::queue_event_loop{};
        auto store = lager::make_store<xzr::counter::action::action>(xzr::counter::model::model{},
                                                                     xzr::counter::model::update,
                                                                     lager::with_manual_event_loop{});
        lager::watch(store, render);

        auto c = char{};
        while (std::cin >> c)
        {
            if (c == 'q')
                break;
            if (const auto act = xzr::counter::view::console::menu::intent(c))
            {
                store.dispatch(*act);
            }
            evt_q.step();
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
        return 1;
    }

    return 0;
}
