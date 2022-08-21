#include <wlfw/wlfw.hpp>

auto main(int argc, char** argv) -> int {
    wl::NativeWindow window;
    std::cout << window.GetWindowProps()->GetTitle() << '\n';
    std::cout << window.GetWindowProps()->GetWidth() << '\n';
    std::cout << window.GetWindowProps()->GetHeight() << '\n';
    std::cout << window.GetWindowProps()->GetStyle() << '\n';

    WLFW_CHECK(-1);
    std::cin.get();
    return 0;
}