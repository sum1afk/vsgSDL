#include <vsgSDL/keyboard.hpp>

namespace vsgSDL {
    KeyboardMap::KeyboardMap() :
        keycodeContinuous {
        {SDL_SCANCODE_UNKNOWN, vsg::KeySymbol::KEY_Undefined},
        {SDL_SCANCODE_SPACE, vsg::KeySymbol::KEY_Space},

        {SDL_SCANCODE_0, vsg::KeySymbol::KEY_0}, {SDL_SCANCODE_1, vsg::KeySymbol::KEY_1},
        {SDL_SCANCODE_2, vsg::KeySymbol::KEY_2}, {SDL_SCANCODE_3, vsg::KeySymbol::KEY_3},
        {SDL_SCANCODE_4, vsg::KeySymbol::KEY_4}, {SDL_SCANCODE_5, vsg::KeySymbol::KEY_5},
        {SDL_SCANCODE_6, vsg::KeySymbol::KEY_6}, {SDL_SCANCODE_7, vsg::KeySymbol::KEY_7},
        {SDL_SCANCODE_8, vsg::KeySymbol::KEY_8}, {SDL_SCANCODE_9, vsg::KeySymbol::KEY_9},

        {SDL_SCANCODE_A, vsg::KEY_A}, {SDL_SCANCODE_B, vsg::KEY_B},
        {SDL_SCANCODE_C, vsg::KEY_C}, {SDL_SCANCODE_D, vsg::KEY_D},
        {SDL_SCANCODE_E, vsg::KEY_E}, {SDL_SCANCODE_F, vsg::KEY_F},
        {SDL_SCANCODE_G, vsg::KEY_G}, {SDL_SCANCODE_H, vsg::KEY_H},
        {SDL_SCANCODE_I, vsg::KEY_I}, {SDL_SCANCODE_J, vsg::KEY_J},
        {SDL_SCANCODE_K, vsg::KEY_K}, {SDL_SCANCODE_L, vsg::KEY_L},
        {SDL_SCANCODE_M, vsg::KEY_M}, {SDL_SCANCODE_N, vsg::KEY_N},
        {SDL_SCANCODE_O, vsg::KEY_O}, {SDL_SCANCODE_P, vsg::KEY_P},
        {SDL_SCANCODE_Q, vsg::KEY_Q}, {SDL_SCANCODE_R, vsg::KEY_R},
        {SDL_SCANCODE_S, vsg::KEY_S}, {SDL_SCANCODE_T, vsg::KEY_T},
        {SDL_SCANCODE_U, vsg::KEY_U}, {SDL_SCANCODE_V, vsg::KEY_V},
        {SDL_SCANCODE_W, vsg::KEY_W}, {SDL_SCANCODE_X, vsg::KEY_X},
        {SDL_SCANCODE_Y, vsg::KEY_Y}, {SDL_SCANCODE_Z, vsg::KEY_Z},

        {SDL_SCANCODE_HOME, vsg::KeySymbol::KEY_Home},
        {SDL_SCANCODE_UP, vsg::KeySymbol::KEY_Up}, {SDL_SCANCODE_DOWN, vsg::KeySymbol::KEY_Down},
        {SDL_SCANCODE_LEFT, vsg::KeySymbol::KEY_Left}, {SDL_SCANCODE_RIGHT, vsg::KeySymbol::KEY_Right},
        {SDL_SCANCODE_HOME, vsg::KeySymbol::KEY_Next}, {SDL_SCANCODE_END, vsg::KeySymbol::KEY_End},
        {SDL_SCANCODE_COMMA, vsg::KeySymbol::KEY_Comma}, {SDL_SCANCODE_MINUS, vsg::KeySymbol::KEY_Minus},
        {SDL_SCANCODE_PERIOD, vsg::KeySymbol::KEY_Period}, {SDL_SCANCODE_SLASH, vsg::KeySymbol::KEY_Slash},
        {SDL_SCANCODE_SEMICOLON, vsg::KeySymbol::KEY_Semicolon}, {SDL_SCANCODE_EQUALS, vsg::KeySymbol::KEY_Equals},
        {SDL_SCANCODE_LEFTBRACKET, vsg::KeySymbol::KEY_Leftbracket}, {SDL_SCANCODE_BACKSLASH, vsg::KeySymbol::KEY_Backslash},
        {SDL_SCANCODE_RIGHTBRACKET, vsg::KeySymbol::KEY_Rightbracket}, {SDL_SCANCODE_BACKSPACE, vsg::KeySymbol::KEY_BackSpace},
        {SDL_SCANCODE_TAB, vsg::KeySymbol::KEY_Tab}, {SDL_SCANCODE_CLEAR, vsg::KeySymbol::KEY_Clear},
        {SDL_SCANCODE_RETURN, vsg::KeySymbol::KEY_Return}, {SDL_SCANCODE_PAUSE, vsg::KeySymbol::KEY_Pause},
        {SDL_SCANCODE_SCROLLLOCK, vsg::KeySymbol::KEY_Scroll_Lock}, {SDL_SCANCODE_ESCAPE, vsg::KeySymbol::KEY_Escape},
        {SDL_SCANCODE_DELETE, vsg::KeySymbol::KEY_Delete}, {SDL_SCANCODE_SELECT, vsg::KeySymbol::KEY_Select},
        {SDL_SCANCODE_PRINTSCREEN, vsg::KeySymbol::KEY_Print}, {SDL_SCANCODE_EXECUTE, vsg::KeySymbol::KEY_Execute},
        {SDL_SCANCODE_INSERT, vsg::KeySymbol::KEY_Insert}, {SDL_SCANCODE_MENU, vsg::KeySymbol::KEY_Menu},
        {SDL_SCANCODE_CANCEL, vsg::KeySymbol::KEY_Cancel}, {SDL_SCANCODE_HELP, vsg::KeySymbol::KEY_Help},
        {SDL_SCANCODE_NUMLOCKCLEAR, vsg::KeySymbol::KEY_Num_Lock},

        {SDL_SCANCODE_LSHIFT, vsg::KeySymbol::KEY_Shift_L}, {SDL_SCANCODE_RSHIFT, vsg::KeySymbol::KEY_Shift_R},
        {SDL_SCANCODE_LCTRL, vsg::KeySymbol::KEY_Control_L}, {SDL_SCANCODE_RCTRL, vsg::KeySymbol::KEY_Control_R},
        {SDL_SCANCODE_CAPSLOCK, vsg::KeySymbol::KEY_Caps_Lock},

        {SDL_SCANCODE_F1, vsg::KeySymbol::KEY_F1}, {SDL_SCANCODE_F2, vsg::KeySymbol::KEY_F2},
        {SDL_SCANCODE_F3, vsg::KeySymbol::KEY_F3}, {SDL_SCANCODE_F4, vsg::KeySymbol::KEY_F4},
        {SDL_SCANCODE_F5, vsg::KeySymbol::KEY_F5}, {SDL_SCANCODE_F6, vsg::KeySymbol::KEY_F6},
        {SDL_SCANCODE_F7, vsg::KeySymbol::KEY_F7}, {SDL_SCANCODE_F8, vsg::KeySymbol::KEY_F8},
        {SDL_SCANCODE_F9, vsg::KeySymbol::KEY_F9}, {SDL_SCANCODE_F10, vsg::KeySymbol::KEY_F10},
        {SDL_SCANCODE_F11, vsg::KeySymbol::KEY_F11}, {SDL_SCANCODE_F12, vsg::KeySymbol::KEY_F12},
        {SDL_SCANCODE_F13, vsg::KeySymbol::KEY_F13}, {SDL_SCANCODE_F14, vsg::KeySymbol::KEY_F14},
        {SDL_SCANCODE_F15, vsg::KeySymbol::KEY_F15}, {SDL_SCANCODE_F16, vsg::KeySymbol::KEY_F16},
        {SDL_SCANCODE_F17, vsg::KeySymbol::KEY_F17}, {SDL_SCANCODE_F18, vsg::KeySymbol::KEY_F18},
        {SDL_SCANCODE_F19, vsg::KeySymbol::KEY_F19}, {SDL_SCANCODE_F20, vsg::KeySymbol::KEY_F20},
        {SDL_SCANCODE_F21, vsg::KeySymbol::KEY_F21}, {SDL_SCANCODE_F22, vsg::KeySymbol::KEY_F22},
        {SDL_SCANCODE_F23, vsg::KeySymbol::KEY_F23}, {SDL_SCANCODE_F24, vsg::KeySymbol::KEY_F24}
    },
    keycodeSingular {
        {SDLK_UNKNOWN, vsg::KeySymbol::KEY_Undefined},
        {SDLK_SPACE, vsg::KeySymbol::KEY_Space},

        {SDLK_0, vsg::KeySymbol::KEY_0}, {SDLK_1, vsg::KeySymbol::KEY_1},
        {SDLK_2, vsg::KeySymbol::KEY_2}, {SDLK_3, vsg::KeySymbol::KEY_3},
        {SDLK_4, vsg::KeySymbol::KEY_4}, {SDLK_5, vsg::KeySymbol::KEY_5},
        {SDLK_6, vsg::KeySymbol::KEY_6}, {SDLK_7, vsg::KeySymbol::KEY_7},
        {SDLK_8, vsg::KeySymbol::KEY_8}, {SDLK_9, vsg::KeySymbol::KEY_9},

        {SDLK_a, vsg::KeySymbol::KEY_a}, {SDLK_b, vsg::KeySymbol::KEY_b},
        {SDLK_c, vsg::KeySymbol::KEY_c}, {SDLK_d, vsg::KeySymbol::KEY_d},
        {SDLK_e, vsg::KeySymbol::KEY_e}, {SDLK_f, vsg::KeySymbol::KEY_f},
        {SDLK_g, vsg::KeySymbol::KEY_g}, {SDLK_h, vsg::KeySymbol::KEY_h},
        {SDLK_i, vsg::KeySymbol::KEY_i}, {SDLK_j, vsg::KeySymbol::KEY_j},
        {SDLK_k, vsg::KeySymbol::KEY_k}, {SDLK_l, vsg::KeySymbol::KEY_l},
        {SDLK_m, vsg::KeySymbol::KEY_m}, {SDLK_n, vsg::KeySymbol::KEY_n},
        {SDLK_o, vsg::KeySymbol::KEY_o}, {SDLK_p, vsg::KeySymbol::KEY_p},
        {SDLK_q, vsg::KeySymbol::KEY_q}, {SDLK_r, vsg::KeySymbol::KEY_r},
        {SDLK_s, vsg::KeySymbol::KEY_s}, {SDLK_t, vsg::KeySymbol::KEY_t},
        {SDLK_u, vsg::KeySymbol::KEY_u}, {SDLK_v, vsg::KeySymbol::KEY_v},
        {SDLK_w, vsg::KeySymbol::KEY_w}, {SDLK_x, vsg::KeySymbol::KEY_x},
        {SDLK_y, vsg::KeySymbol::KEY_y}, {SDLK_z, vsg::KeySymbol::KEY_z},

        {SDLK_HOME, vsg::KeySymbol::KEY_Home},
        {SDLK_UP, vsg::KeySymbol::KEY_Up}, {SDLK_DOWN, vsg::KeySymbol::KEY_Down},
        {SDLK_LEFT, vsg::KeySymbol::KEY_Left}, {SDLK_RIGHT, vsg::KeySymbol::KEY_Right},
        {SDLK_HOME, vsg::KeySymbol::KEY_Next}, {SDLK_END, vsg::KeySymbol::KEY_End},
        {SDLK_COMMA, vsg::KeySymbol::KEY_Comma}, {SDLK_MINUS, vsg::KeySymbol::KEY_Minus},
        {SDLK_PERIOD, vsg::KeySymbol::KEY_Period}, {SDLK_SLASH, vsg::KeySymbol::KEY_Slash},
        {SDLK_SEMICOLON, vsg::KeySymbol::KEY_Semicolon}, {SDLK_EQUALS, vsg::KeySymbol::KEY_Equals},
        {SDLK_LEFTBRACKET, vsg::KeySymbol::KEY_Leftbracket}, {SDLK_BACKSLASH, vsg::KeySymbol::KEY_Backslash},
        {SDLK_RIGHTBRACKET, vsg::KeySymbol::KEY_Rightbracket}, {SDLK_BACKSPACE, vsg::KeySymbol::KEY_BackSpace},
        {SDLK_TAB, vsg::KeySymbol::KEY_Tab}, {SDLK_CLEAR, vsg::KeySymbol::KEY_Clear},
        {SDLK_RETURN, vsg::KeySymbol::KEY_Return}, {SDLK_PAUSE, vsg::KeySymbol::KEY_Pause},
        {SDLK_SCROLLLOCK, vsg::KeySymbol::KEY_Scroll_Lock}, {SDLK_ESCAPE, vsg::KeySymbol::KEY_Escape},
        {SDLK_DELETE, vsg::KeySymbol::KEY_Delete}, {SDLK_SELECT, vsg::KeySymbol::KEY_Select},
        {SDLK_PRINTSCREEN, vsg::KeySymbol::KEY_Print}, {SDLK_EXECUTE, vsg::KeySymbol::KEY_Execute},
        {SDLK_INSERT, vsg::KeySymbol::KEY_Insert}, {SDLK_MENU, vsg::KeySymbol::KEY_Menu},
        {SDLK_CANCEL, vsg::KeySymbol::KEY_Cancel}, {SDLK_HELP, vsg::KeySymbol::KEY_Help},
        {SDLK_NUMLOCKCLEAR, vsg::KeySymbol::KEY_Num_Lock},

        {SDLK_EXCLAIM, vsg::KeySymbol::KEY_Exclaim}, {SDLK_QUOTEDBL, vsg::KeySymbol::KEY_Quotedbl},
        {SDLK_HASH, vsg::KeySymbol::KEY_Hash}, {SDLK_DOLLAR, vsg::KeySymbol::KEY_Dollar},
        {SDLK_AMPERSAND, vsg::KeySymbol::KEY_Ampersand}, {SDLK_QUOTE, vsg::KeySymbol::KEY_Quote},
        {SDLK_LEFTPAREN, vsg::KeySymbol::KEY_Leftparen}, {SDLK_RIGHTPAREN, vsg::KeySymbol::KEY_Rightparen},
        {SDLK_ASTERISK, vsg::KeySymbol::KEY_Asterisk}, {SDLK_PLUS, vsg::KeySymbol::KEY_Plus},
        {SDLK_COLON, vsg::KeySymbol::KEY_Colon}, {SDLK_LESS, vsg::KeySymbol::KEY_Less},
        {SDLK_GREATER, vsg::KeySymbol::KEY_Greater}, {SDLK_QUESTION, vsg::KeySymbol::KEY_Question},
        {SDLK_AT, vsg::KeySymbol::KEY_At}, {SDLK_CARET, vsg::KeySymbol::KEY_Caret},
        {SDLK_UNDERSCORE, vsg::KeySymbol::KEY_Underscore},
        {SDLK_BACKQUOTE, vsg::KeySymbol::KEY_Backquote},

        {SDLK_LSHIFT, vsg::KeySymbol::KEY_Shift_L}, {SDLK_RSHIFT, vsg::KeySymbol::KEY_Shift_R},
        {SDLK_LCTRL, vsg::KeySymbol::KEY_Control_L}, {SDLK_RCTRL, vsg::KeySymbol::KEY_Control_R},
        {SDLK_CAPSLOCK, vsg::KeySymbol::KEY_Caps_Lock},

        {SDLK_F1, vsg::KeySymbol::KEY_F1}, {SDLK_F2, vsg::KeySymbol::KEY_F2},
        {SDLK_F3, vsg::KeySymbol::KEY_F3}, {SDLK_F4, vsg::KeySymbol::KEY_F4},
        {SDLK_F5, vsg::KeySymbol::KEY_F5}, {SDLK_F6, vsg::KeySymbol::KEY_F6},
        {SDLK_F7, vsg::KeySymbol::KEY_F7}, {SDLK_F8, vsg::KeySymbol::KEY_F8},
        {SDLK_F9, vsg::KeySymbol::KEY_F9}, {SDLK_F10, vsg::KeySymbol::KEY_F10},
        {SDLK_F11, vsg::KeySymbol::KEY_F11}, {SDLK_F12, vsg::KeySymbol::KEY_F12},
        {SDLK_F13, vsg::KeySymbol::KEY_F13}, {SDLK_F14, vsg::KeySymbol::KEY_F14},
        {SDLK_F15, vsg::KeySymbol::KEY_F15}, {SDLK_F16, vsg::KeySymbol::KEY_F16},
        {SDLK_F17, vsg::KeySymbol::KEY_F17}, {SDLK_F18, vsg::KeySymbol::KEY_F18},
        {SDLK_F19, vsg::KeySymbol::KEY_F19}, {SDLK_F20, vsg::KeySymbol::KEY_F20},
        {SDLK_F21, vsg::KeySymbol::KEY_F21}, {SDLK_F22, vsg::KeySymbol::KEY_F22},
        {SDLK_F23, vsg::KeySymbol::KEY_F23}, {SDLK_F24, vsg::KeySymbol::KEY_F24}
    }

    /*
        unimplemented:
            SDLK_KP_~x
            SDL_SCANCODE_KP_~x
            vsg::KEY_KP_~x
    */

    { ; }


    constexpr vsg::KeyModifier KeyboardMap::getModifier(Uint16 keyMod) const {
        uint16_t modifierMask = 0;
        if(keyMod & KMOD_SHIFT) modifierMask |= vsg::KeyModifier::MODKEY_Shift;
        if(keyMod & KMOD_CTRL) modifierMask |= vsg::KeyModifier::MODKEY_Control;
        if(keyMod & KMOD_ALT) modifierMask |= vsg::KeyModifier::MODKEY_Alt;
        return vsg::KeyModifier(modifierMask);
    }

    bool KeyboardMap::getKeySingularly(const SDL_KeyboardEvent *e, vsg::KeySymbol &keySymbol, vsg::KeySymbol &modifiedKeySymbol, vsg::KeyModifier &keyModifier) const {
        const auto key = e->keysym.sym;

        auto it = keycodeSingular.find(key);
        if(it == keycodeSingular.end())
            return false;

        const auto keyMod = e->keysym.mod;
        keySymbol = it->second;
        modifiedKeySymbol = keySymbol;
        keyModifier = getModifier(keyMod);

        return true;
    }

    bool KeyboardMap::getKeyContinuously(const SDL_Scancode key, vsg::KeySymbol &keySymbol, vsg::KeySymbol &modifiedKeySymbol, vsg::KeyModifier &keyModifier) const {
        auto it = keycodeContinuous.find(key);
        if(it == keycodeContinuous.end())
            return false;

        const auto keyMod = SDL_GetModState();
        keySymbol = it->second;
        modifiedKeySymbol = keySymbol;
        keyModifier = getModifier(keyMod);

        return true;
    }
}
