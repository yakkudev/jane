#pragma once

#include "component.h"
#include "transform.h"
#include "types.h"
#include <map>
#include <functional>
#include <vector>

class GC_Interaction : public Component {
    REGISTER_GC(GC_Interaction)
public:
    f32 scale;

    enum class Type {
        MOUSE_ENTER, // Not implemented
        MOUSE_EXIT, // Not implemented
        MOUSE_DOWN,
        MOUSE_UP,
    };

    GC_Interaction(f32 scale);

    void update() override;

    void init() override;

    void registerListener(std::function<void()> listener, Type type); // {

private:
    GC_Transform* transform;

    std::vector<std::pair<std::function<void()>, Type>> listeners;
};