#include <vsg/ui/KeyEvent.h>

#include <SDL_keycode.h>
#include <SDL_events.h>

namespace vsgSDL {
    class KeyboardMap : public vsg::Inherit<vsg::Object, KeyboardMap> {
    public:
        KeyboardMap();

        bool getKeySingularly(const SDL_KeyboardEvent*, vsg::KeySymbol&, vsg::KeySymbol&, vsg::KeyModifier&) const;
        bool getKeyContinuously(const SDL_Scancode, vsg::KeySymbol&, vsg::KeySymbol&, vsg::KeyModifier&) const;

        std::unordered_map<SDL_Scancode, vsg::KeySymbol> keycodeContinuous;
    private:
        constexpr vsg::KeyModifier getModifier(Uint16) const;
    protected:
        std::unordered_map<SDL_Keycode, vsg::KeySymbol> keycodeSingular;
    };
}
