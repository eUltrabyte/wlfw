#include <wlfw/Window.hpp>

auto main(int argc, char** argv) -> int {
    wl::Window firstWindow(wl::WindowProps("wlfw first window example", 600, 600, wl::Style::Default));
    wl::Window secondWindow(wl::WindowProps("wlfw second window example", 500, 500, wl::Style::Default));

    for(;;) {
        firstWindow.Update();
        secondWindow.Update();
    }

    WLFW_CHECK(-1);
    std::cin.get();
    return 0;
}