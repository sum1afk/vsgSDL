#include <vsgSDL/version.hpp>
#include <vsgSDL/keyboard.hpp>
#include <vsgSDL/mouse.hpp>

namespace vsgSDL {
    class vsgSDL_LIB Window {
    public:
        Window();
        ~Window();

        std::function<void(const vsg::ref_ptr<vsg::Window>)> focusGained;
        std::function<void(const vsg::ref_ptr<vsg::Window>)> focusLost;
        std::function<void(const char[SDL_TEXTINPUTEVENT_TEXT_SIZE])> textInput;
        std::function<void(const vsg::ref_ptr<vsg::Viewer>)> render;
        std::function<void(const vsg::ref_ptr<vsg::Window>,
                           const vsg::ref_ptr<vsg::Viewer>,
                           const vsg::ref_ptr<vsg::WindowTraits>)> renderInit;
        std::function<void(const vsg::ref_ptr<vsg::Viewer>)> renderDeinit;

        bool create(std::string title, int x, int y, uint32_t width, uint32_t height, Uint32 sdlWinFlags,
                    bool vulkanDebugLayer, bool vulkanAPIDumpLayer, std::string vulkanDynLib = "");

        bool process(const bool continuousKey);
    private:
        vsg::ref_ptr<vsg::WindowTraits> traits;
        vsg::ref_ptr<vsg::Instance> instance;
        vsg::ref_ptr<vsg::Surface> surface;
        vsg::ref_ptr<vsg::Window> adapter;
        vsg::ref_ptr<KeyboardMap> keyboardMap;
        SDL_Window *sdlWindow;
        vsg::ref_ptr<vsg::Viewer> viewer;

        bool initInstance(std::string title, uint32_t width, uint32_t height,
                          bool debugLayer, bool apiDumpLayer);
        bool initSDL();
        bool initSDLVulkan(std::string dynLib = "") const;
        bool initSDLVulkanSurface();
    protected:
        void pollEvents(const bool continuousKey);

        void pollContinuousLast();
        void pollContinuous();

        int oldKeyCountSDL;
        Uint8 *oldKeyStateSDL;

        void keyPressEvent(const SDL_KeyboardEvent *e) const;
        void keyReleaseEvent(const SDL_KeyboardEvent *e) const;
        void mouseMoveEvent(const SDL_MouseMotionEvent *e) const;
        void mousePressEvent(const SDL_MouseButtonEvent *e) const;
        void mouseReleaseEvent(const SDL_MouseButtonEvent *e) const;
        void wheelEvent(const SDL_MouseWheelEvent *e) const;
        void moveEvent(const SDL_WindowEvent *e) const;
        void resizeEvent(const SDL_WindowEvent *e) const;

        vsg::clock::time_point sdlTimeToVSG(Uint32 timestamp) const;
    };
}
