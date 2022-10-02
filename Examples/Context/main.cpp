#include <wlfw/Context.hpp>

auto main(int argc, char** argv) -> int {
    wl::Window window(wl::WindowProps("wlfw context example", 1280, 720, wl::Style::Default));

    wl::Context context;

    for(;;) {
        window.Update();
    }

    WLFW_CHECK(-1);
    std::cin.get();
    return 0;
}