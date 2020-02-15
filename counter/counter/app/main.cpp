#include <counter/model/model.hpp>

#include <lager/event_loop/manual.hpp>
#include <lager/event_loop/queue.hpp>
#include <lager/store.hpp>
#include <lager/watch.hpp>

#include <boost/program_options.hpp>

#include <iostream>
#include <iterator>
#include <optional>

namespace po = boost::program_options;

inline const auto intent = [](auto e) -> std::optional<xzr::counter::action::action> {
    if (e == '+')
        return xzr::counter::action::increment{};
    if (e == '-')
        return xzr::counter::action::decrement{};
    if (e == '=')
        return xzr::counter::action::reset{0};
    return std::nullopt;
};

inline const auto render = [](const auto &prev, const auto &current) {
    std::cout << "previous value = " << prev.value << '\n';
    std::cout << "current value = " << current.value << '\n';
};

int main(int ac, char *av[])
{
    std::cout << "lager app\n";

    try
    {
        po::options_description desc("options for lager app");
        desc.add_options()("help", "produce help message")("+", "increments counter by 1")(
            "-", "decrements counter by 1")("=", "resets counter to 0")("q", "quits application");

        po::variables_map vm;
        po::store(po::parse_command_line(ac, av, desc), vm);
        po::notify(vm);

        if (vm.count("help"))
        {
            std::cout << desc << "\n";
            return 0;
        }
        std::cout << desc << "\n";
    }
    catch (std::exception &e)
    {
        std::cerr << "error: " << e.what() << "\n";
        return 1;
    }
    catch (...)
    {
        std::cerr << "Exception of unknown type!\n";
    }

    auto evt_q = lager::queue_event_loop{};
    auto store = lager::make_store<xzr::counter::action::action>(
        xzr::counter::model::model{}, xzr::counter::model::update, lager::with_manual_event_loop{}
        // events will be queued and only executed
        // after q.step() has been called
        // lager::with_queue_event_loop{evt_q}
    );
    lager::watch(store, render);

    auto c = char{};
    while (std::cin >> c)
    {
        if (c == 'q')
            break;
        if (const auto act = intent(c))
        {
            store.dispatch(*act);
        }
        evt_q.step();
    }

    return 0;
}
