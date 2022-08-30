#include <wlfw/wlfw.hpp>
#include <wlfw/Window.hpp>

auto main(int argc, char** argv) -> int {
    wl::Window window(wl::WindowProps("wlfw window example", 1280, 720, WS_OVERLAPPEDWINDOW));
    std::cout << window.GetWindowProps()->GetTitle() << '\n';
    std::cout << window.GetWindowProps()->GetWidth() << '\n';
    std::cout << window.GetWindowProps()->GetHeight() << '\n';
    std::cout << window.GetWindowProps()->GetStyle() << '\n';

    for(;;) {
        window.Update();
    }

    WLFW_CHECK(-1);
    std::cin.get();
    return 0;
}