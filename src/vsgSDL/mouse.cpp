#include <vsgSDL/mouse.hpp>

namespace vsgSDL {
    std::pair<vsg::ButtonMask, uint32_t> convertMouseSDL(Uint32 inButton, Uint8 state) {
        uint16_t mask{0};
        uint32_t button{0};

        if(state & SDL_BUTTON(1)) mask |= vsg::BUTTON_MASK_1;
        if(state & SDL_BUTTON(2)) mask |= vsg::BUTTON_MASK_2;
        if(state & SDL_BUTTON(3)) mask |= vsg::BUTTON_MASK_3;

        switch(inButton) {
        case SDL_BUTTON_LEFT:
            button = 1;
            break;
        case SDL_BUTTON_MIDDLE:
            button = 2;
            break;
        case SDL_BUTTON_RIGHT:
            button = 3;
            break;
        default:
            break;
        }

        return {static_cast<vsg::ButtonMask>(mask), button};
    }
}
