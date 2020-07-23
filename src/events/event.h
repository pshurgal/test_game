#pragma once

#include <input/keyboard_key.h>
#include <input/mouse_button.h>
#include <math/vec2.h>

#include <cstddef>
#include <cstdint>
#include <functional>

namespace tg
{
    struct Event
    {};

    struct MouseButton: public Event
    {
        EMouseButton button;
        Vec2i        clickPoint;

        MouseButton(EMouseButton p_button, Vec2i p_clickPoint)
            : button(p_button)
            , clickPoint(p_clickPoint)
        {}
    };

    struct KeyboardKey: public Event
    {
        EKeyboardKey key;

        KeyboardKey(EKeyboardKey p_key)
            : key(p_key)
        {}
    };
}
