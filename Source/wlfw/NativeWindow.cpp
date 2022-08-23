#include "Window.hpp"

namespace wl {
    NativeWindow::NativeWindow(const WindowProps& windowProps) {
        m_windowProps = std::make_shared<WindowProps>(windowProps);
    }

    void NativeWindow::SetWindowProps(const WindowProps& windowProps) {
        m_windowProps = std::make_shared<WindowProps>(windowProps);
    }
        
    std::shared_ptr<WindowProps>& NativeWindow::GetWindowProps() {
        return m_windowProps;
    }
};