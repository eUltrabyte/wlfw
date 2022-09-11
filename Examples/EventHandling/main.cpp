#include <wlfw/Window.hpp>

void WindowClosed() {
    std::cout << "Our Window Closed\n";
}

void WindowResized(std::stringstream& data) {
    char junk = '0';
    int width = 0;
    int height = 0;
    data >> width >> junk >> height;
    std::cout << "Our Window Resized : " << width << " : " << height << '\n'; 
}

void WindowMoved(std::stringstream& data) {
    char junk = '0';
    int x = 0;
    int y = 0;
    data >> x >> junk >> y;
    std::cout << "Our Window Moved : " << x << " : " << y << '\n';
}

void WindowGainedFocus() {
    std::cout << "Our Window Gained Focus" << '\n';
};

void WindowLostFocus() {
    std::cout << "Our Window Lost Focus" << '\n';
};

void MouseScrolled(std::stringstream& data) {
    char junk = '0';
    bool pressed = false;
    int direction = 0;
    data >> pressed >> junk >> direction;
    std::cout << "Our Mouse Scrolled : " << pressed << " : " << direction << '\n'; 
};

void MouseMoved(std::stringstream& data) {
    char junk = '0';
    int x = 0;
    int y = 0;
    data >> x >> junk >> y;
    std::cout << "Our Mouse Moved : " << x << " : " << y << '\n'; 
};

void ButtonPressed(std::stringstream& data) {
    int button = 0;
    data >> button;
    std::cout << "Our Button Pressed : " << button << '\n'; 
};

void ButtonReleased(std::stringstream& data) {
    int button = 0;
    data >> button;
    std::cout << "Our Button Released : " << button << '\n'; 
};

void KeyPressed(std::stringstream& data) {
    int key = 0;
    data >> key;
    std::cout << "Our Key Pressed : " << key << '\n'; 
};

void KeyReleased(std::stringstream& data) {
    int key = 0;
    data >> key;
    std::cout << "Our Key Pressed : " << key << '\n'; 
};

void KeyRepeated(std::stringstream& data) {
    int key = 0;
    data >> key;
    std::cout << "Our Key Repeated : " << key << '\n';
};

auto main(int argc, char** argv) -> int {
    wl::EventHandler handler;
    handler.SetWindowClosedCallback(WindowClosed);
    handler.SetWindowResizedCallback(WindowResized);
    handler.SetWindowMovedCallback(WindowMoved);
    handler.SetWindowGainedFocusCallback(WindowGainedFocus);
    handler.SetWindowLostFocusCallback(WindowLostFocus);
    handler.SetMouseScrolledCallback(MouseScrolled);
    handler.SetMouseMovedCallback(MouseMoved);
    handler.SetButtonPressedCallback(ButtonPressed);
    handler.SetButtonReleasedCallback(ButtonReleased);
    handler.SetKeyPressedCallback(KeyPressed);
    handler.SetKeyReleasedCallback(KeyReleased);
    handler.SetKeyRepeatedCallback(KeyRepeated);

    wl::Window window(wl::WindowProps("wlfw window example", 1280, 720, wl::Style::Default));
    window.SetEventHandler(handler);

    for(;;) {
        window.Update();
    }

    WLFW_CHECK(-1);
    std::cin.get();
    return 0;
}