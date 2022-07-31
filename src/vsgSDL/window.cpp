#include <vsgSDL/window.hpp>

#include <vsg/viewer/Viewer.h>
#include <vsg/viewer/WindowAdapter.h>
#include <vsg/ui/ScrollWheelEvent.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include<vsg/all.h>

namespace vsgSDL {
    static constexpr auto instanceSurfaceName = []() constexpr {
        #if defined(VK_USE_PLATFORM_WIN32_KHR)
        return VK_KHR_WIN32_SURFACE_EXTENSION_NAME;
        #elif defined(VK_USE_PLATFORM_XLIB_KHR)
        return VK_KHR_XLIB_SURFACE_EXTENSION_NAME;
        #elif defined(VK_USE_PLATFORM_XCB_KHR)
        return VK_KHR_XCB_SURFACE_EXTENSION_NAME;
        #elif defined(VK_USE_PLATFORM_MACOS_MVK)
        return VK_MVK_MACOS_SURFACE_EXTENSION_NAME;
        #endif
    };


    Window::Window() {
        keyboardMap = KeyboardMap::create();
        traits = vsg::WindowTraits::create();
    }

    Window::~Window() {
        renderDeinit(viewer);

        delete [] oldKeyStateSDL;

        SDL_DestroyWindow(sdlWindow);
        SDL_Quit();
        SDL_Vulkan_UnloadLibrary();
    }

    bool Window::process(const bool continuousKey) {
        pollEvents(continuousKey);

        if(viewer->advanceToNextFrame()) {
            render(viewer);
        } else return false;

        if(continuousKey) {
            pollContinuousLast();
        }

        return true;
    }

    bool Window::initInstance(std::string title, uint32_t width, uint32_t height,
                              bool debugLayer, bool apiDumpLayer) {
        vsg::Names instanceExtensions;
        vsg::Names validatedLayers;

        traits = vsg::WindowTraits::create();
        traits->debugLayer = debugLayer;
        traits->apiDumpLayer = apiDumpLayer;
        traits->width = width;
        traits->height = height;
        traits->windowTitle = title;
        traits->windowClass = "vsgSDL";

        instanceExtensions.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
        instanceExtensions.push_back("VK_KHR_surface");
        instanceExtensions.push_back(instanceSurfaceName());

        vsg::Names requestedLayers;
        if(traits->debugLayer || traits->apiDumpLayer) {
            instanceExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
            requestedLayers.push_back("VK_LAYER_KHRONOS_validation");

            if(traits->apiDumpLayer)
                requestedLayers.push_back("VK_LAYER_LUNARG_api_dump");
        }

        validatedLayers = vsg::validateInstancelayerNames(requestedLayers);
        instance = vsg::Instance::create(instanceExtensions, validatedLayers);
        if(instance == nullptr)
            return false;

        return true;
    }

    bool Window::initSDL() {
        SDL_SetMainReady();

        if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
            return false;

        SDL_GetKeyboardState(&oldKeyCountSDL);
        oldKeyStateSDL = new Uint8[oldKeyCountSDL];

        return true;
    }

    bool Window::initSDLVulkan(std::string dynLib) const {
        if (dynLib == "")
            return SDL_Vulkan_LoadLibrary(NULL) != -1;
        else 
            return SDL_Vulkan_LoadLibrary(dynLib.c_str()) == -1;
    }

    bool Window::initSDLVulkanSurface() {
        unsigned int pCount;
        SDL_Vulkan_GetInstanceExtensions(sdlWindow, &pCount, NULL);
        const char **pNames = static_cast<const char**>(malloc(sizeof(const char*)*pCount));
        SDL_Vulkan_GetInstanceExtensions(sdlWindow, &pCount, pNames);
        vsg::Names instanceExtensionsUnused;

        for(size_t i = 0; i < pCount; i++) {
            instanceExtensionsUnused.push_back(pNames[i]);
        }

        SDL_vulkanSurface vulkanSurface;
        SDL_vulkanInstance vulkanInstance = *instance;
        if(SDL_Vulkan_CreateSurface(sdlWindow, vulkanInstance, &vulkanSurface) == SDL_FALSE)
            return false;

        surface = vsg::Surface::create(vulkanSurface, instance);
        adapter = vsg::WindowAdapter::create(surface, traits);
        if(auto wa = adapter.cast<vsg::WindowAdapter>(); wa) {
            wa->windowValid = true;
            wa->windowVisible = true;

            int dx, dy;
            SDL_Vulkan_GetDrawableSize(sdlWindow, &dx, &dy);
            wa->updateExtents(dx, dy);

            int px, py;
            SDL_GetWindowPosition(sdlWindow, &px, &py);

            vsg::clock::time_point event_time = vsg::clock::now();
            wa->bufferedEvents.emplace_back(vsg::ConfigureWindowEvent::create(
                                                wa, event_time, px, py, static_cast<uint32_t>(dx), static_cast<uint32_t>(dy)));
        } else return false;

        return true;
    }

    bool Window::create(std::string title, int x, int y, uint32_t width, uint32_t height, Uint32 sdlWinFlags,
                        bool vulkanDebugLayer, bool vulkanAPIDumpLayer, std::string vulkanDynLib) {
        if(!initInstance(title, width, height, vulkanDebugLayer, vulkanAPIDumpLayer))
            return false;

        if(!initSDL())
            return false;

        if(!initSDLVulkan(vulkanDynLib))
            return false;

        traits->x = x;
        traits->y = y;
        sdlWindow = SDL_CreateWindow(
                        traits->windowTitle.c_str(), traits->x, traits->y, traits->width, traits->height,
                        sdlWinFlags);
        if(sdlWindow == nullptr)
            return false;

        if(!initSDLVulkanSurface())
            return false;

        viewer = vsg::Viewer::create();
        viewer->addWindow(adapter);

        renderInit(adapter, viewer, traits);

        return true;
    }

    void Window::pollContinuousLast() {
        const auto lastFrameKeys = SDL_GetKeyboardState(&oldKeyCountSDL);
        for(auto i = 0; i < oldKeyCountSDL; i++) {
            oldKeyStateSDL[i] = lastFrameKeys[i];
        }
    }

    void Window::pollContinuous() {
        SDL_PumpEvents();

        int keyCount;
        auto keyState = SDL_GetKeyboardState(&keyCount);

        for(auto it : keyboardMap->keycodeContinuous) {
            const auto key = it.first;
            const bool pressedSLF = (!oldKeyStateSDL[key] && keyState[key]);
            const bool releasedSLF = (oldKeyStateSDL[key] && !keyState[key]);
            const bool heldSLF = (oldKeyStateSDL[key] && keyState[key]);

            if(pressedSLF) {
                vsg::KeySymbol keySymbol = vsg::KEY_Undefined, modifiedKeySymbol = vsg::KEY_Undefined;
                vsg::KeyModifier keyModifier = vsg::KeyModifier::MODKEY_Control;

                if(keyboardMap->getKeyContinuously(key, keySymbol, modifiedKeySymbol, keyModifier)) {
                    vsg::clock::time_point event_time = vsg::clock::now();
                    adapter->bufferedEvents.emplace_back(vsg::KeyPressEvent::create(
                            adapter, event_time, keySymbol, modifiedKeySymbol, keyModifier));
                }

            } else if(releasedSLF) {
                vsg::KeySymbol keySymbol = vsg::KEY_Undefined, modifiedKeySymbol = vsg::KEY_Undefined;
                vsg::KeyModifier keyModifier = vsg::KeyModifier::MODKEY_Control;

                if(keyboardMap->getKeyContinuously(key, keySymbol, modifiedKeySymbol, keyModifier)) {
                    vsg::clock::time_point event_time = vsg::clock::now();
                    adapter->bufferedEvents.emplace_back(vsg::KeyReleaseEvent::create(
                            adapter, event_time, keySymbol, modifiedKeySymbol, keyModifier));
                }

            } else if(heldSLF) {
                ;
            }
        }
    }

    void Window::pollEvents(const bool continuousKey) {
        if(continuousKey) pollContinuous();

        SDL_Event event;
        while(SDL_PollEvent(&event) != 0) {
            switch(event.type) {
            case SDL_WINDOWEVENT: {
                switch(event.window.event) {
                case SDL_WINDOWEVENT_MOVED: {
                    moveEvent(&event.window);
                } break;

                case SDL_WINDOWEVENT_RESIZED: {
                    resizeEvent(&event.window);
                } break;

                case SDL_WINDOWEVENT_FOCUS_GAINED: {
                    focusGained(adapter);
                } break;

                case SDL_WINDOWEVENT_FOCUS_LOST: {
                    focusLost(adapter);
                } break;

                case SDL_WINDOWEVENT_CLOSE: {
                    if(!adapter) return;

                    vsg::clock::time_point eventTime = vsg::clock::now();
                    adapter->bufferedEvents.emplace_back(vsg::CloseWindowEvent::create(
                            adapter, eventTime));
                } break;

                default:
                    break;
                }
            }

            case SDL_TEXTINPUT: {
                textInput(event.text.text);
            }
            break;

            case SDL_KEYDOWN: {
                if(!continuousKey)
                    keyPressEvent(&event.key);
            }
            break;

            case SDL_KEYUP: {
                if(!continuousKey)
                    keyReleaseEvent(&event.key);
            }
            break;

            case SDL_MOUSEWHEEL: {
                switch(event.wheel.type) {
                case SDL_MOUSEWHEEL:
                    wheelEvent(&event.wheel);
                    break;
                }
            }
            break;

            case SDL_MOUSEMOTION: {
                switch(event.motion.type) {
                case SDL_MOUSEMOTION: {
                    mouseMoveEvent(&event.motion);
                } break;
                }
            }
            break;

            case SDL_MOUSEBUTTONDOWN: {
                mousePressEvent(&event.button);
            }
            break;

            case SDL_MOUSEBUTTONUP: {
                mouseReleaseEvent(&event.button);
            }
            break;

            case SDL_QUIT: {
                if(!adapter) return;

                vsg::clock::time_point eventTime = vsg::clock::now();
                adapter->bufferedEvents.emplace_back(vsg::TerminateEvent::create(eventTime));
            }
            break;

            default:
                break;
            }
        }
    }

    void Window::keyPressEvent(const SDL_KeyboardEvent *e) const {
        if(!adapter) return;

        const auto keyRepeat = e->repeat;
        vsg::KeySymbol keySymbol = vsg::KEY_Undefined, modifiedKeySymbol = vsg::KEY_Undefined;
        vsg::KeyModifier keyModifier = vsg::KeyModifier::MODKEY_Control;

        if(keyboardMap->getKeySingularly(e, keySymbol, modifiedKeySymbol, keyModifier)) {
            vsg::clock::time_point eventTime = vsg::clock::now();
            adapter->bufferedEvents.emplace_back(vsg::KeyPressEvent::create(
                    adapter, eventTime, keySymbol, modifiedKeySymbol,
                    keyModifier, keyRepeat));
        }
    }

    void Window::keyReleaseEvent(const SDL_KeyboardEvent *e) const {
        if(!adapter) return;

        const auto keyRepeat = e->repeat;
        vsg::KeySymbol keySymbol = vsg::KEY_Undefined, modifiedKeySymbol = vsg::KEY_Undefined;
        vsg::KeyModifier keyModifier = vsg::KeyModifier::MODKEY_Control;

        if(keyboardMap->getKeySingularly(e, keySymbol, modifiedKeySymbol, keyModifier)) {
            vsg::clock::time_point eventTime = vsg::clock::now();
            adapter->bufferedEvents.emplace_back(vsg::KeyReleaseEvent::create(
                    adapter, eventTime, keySymbol, modifiedKeySymbol,
                    keyModifier, keyRepeat));
        }
    }

    void Window::mouseMoveEvent(const SDL_MouseMotionEvent *e) const {
        if(!adapter) return;

        int mouseX = e->x;
        int mouseY = e->y;
        int buttonState = e->state;

        vsg::clock::time_point eventTime = vsg::clock::now();

        uint16_t mask{0};
        if(buttonState & SDL_BUTTON(1)) mask |= vsg::BUTTON_MASK_1;
        if(buttonState & SDL_BUTTON(2)) mask |= vsg::BUTTON_MASK_2;
        if(buttonState & SDL_BUTTON(3)) mask |= vsg::BUTTON_MASK_3;

        adapter->bufferedEvents.emplace_back(
            vsg::MoveEvent::create(adapter, eventTime, mouseX, mouseY, vsg::ButtonMask(mask)));
    }

    void Window::mousePressEvent(const SDL_MouseButtonEvent *e) const {
        if(!adapter) return;

        int mouseX = e->x;
        int mouseY = e->y;
        int mouseState = e->state;

        vsg::clock::time_point eventTime = vsg::clock::now();
        auto [mask, button] = convertMouseSDL(e->button, mouseState);
        adapter->bufferedEvents.emplace_back(
            vsg::ButtonPressEvent::create(adapter, eventTime, mouseX, mouseY, mask, button));
    }

    void Window::mouseReleaseEvent(const SDL_MouseButtonEvent *e) const {
        if(!adapter) return;

        int mouseX = e->x;
        int mouseY = e->y;
        int mouseState = e->state;

        vsg::clock::time_point eventTime = vsg::clock::now();
        auto [mask, button] = convertMouseSDL(e->button, mouseState);
        adapter->bufferedEvents.emplace_back(
            vsg::ButtonReleaseEvent::create(adapter, eventTime, mouseX, mouseY, mask, button));
    }

    void Window::wheelEvent(const SDL_MouseWheelEvent *e) const {
        if(!adapter) return;

        vsg::clock::time_point eventTime = vsg::clock::now();
        adapter->bufferedEvents.emplace_back(
            vsg::ScrollWheelEvent::create(adapter, eventTime, e->preciseY < 0 ?
                                          vsg::vec3(0.0f, -1.0f, 0.0f) : vsg::vec3(0.0f, 1.0f, 0.0f)));
    }

    void Window::moveEvent(const SDL_WindowEvent *e) const {
        if(!adapter) return;

        int wx, wy;
        SDL_GetWindowPosition(sdlWindow, &wx, &wy);

        vsg::clock::time_point eventTime = vsg::clock::now();
        adapter->bufferedEvents.emplace_back(
            vsg::ConfigureWindowEvent::create(adapter, eventTime, wx, wy, static_cast<uint32_t>(traits->width),
                                              static_cast<uint32_t>(traits->height)));
    }

    void Window::resizeEvent(const SDL_WindowEvent *e) const {
        if(!adapter) return;

        int px, py, sx, sy;
        SDL_Vulkan_GetDrawableSize(sdlWindow, &sx, &sy);
        SDL_GetWindowPosition(sdlWindow, &px, &py);

        vsg::clock::time_point eventTime = vsg::clock::now();
        adapter->bufferedEvents.emplace_back(vsg::ConfigureWindowEvent::create(
                adapter, eventTime, px, py, static_cast<uint32_t>(sx), static_cast<uint32_t>(sy)));
    }

    vsg::clock::time_point Window::sdlTimeToVSG(Uint32 timestamp) const {
        const std::chrono::milliseconds sdlToChrono(timestamp);
        const vsg::clock::time_point eventTime(sdlToChrono);
        return eventTime;
    }
}
