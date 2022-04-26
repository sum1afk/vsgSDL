#include <vsg/ui/PointerEvent.h>
#include <SDL_events.h>

namespace vsgSDL {
    std::pair<vsg::ButtonMask, uint32_t> convertMouseSDL(Uint32, Uint8);
}
