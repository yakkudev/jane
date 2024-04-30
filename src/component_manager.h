#pragma once

#include "types.h"
#include <unordered_map>
#include <typeindex>
#include <typeinfo>

class ComponentManager {
private:
    static std::unordered_map <std::type_index, u32>& components();

public:
    template <typename T>
    static u32 registerComponent() {
        return components()[typeid(T)] = nextID();
    }

    template <typename T>
    static u32 getComponentID() {
        return components()[typeid(T)];
    }

    static u32 nextID();
};