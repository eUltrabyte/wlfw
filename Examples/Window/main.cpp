#include <wlfw/Window.hpp>

auto main(int argc, char** argv) -> int {
    wl::Window window(wl::WindowProps("wlfw window example", 1280, 720, wl::Style::Default));

    for(;;) {
        window.Update();
    }

    WLFW_CHECK(-1);
    std::cin.get();
    return 0;
}