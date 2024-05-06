#pragma once

#include "types.h"
#include <unordered_map>
#include <iostream>
#include <typeindex>
#include <typeinfo>

class ComponentManager {
private:
    static std::unordered_map <std::type_index, u32>& components();

public:
    template <typename T>
    static u32 registerComponent() {
        u32 id = nextID();
        std::cout << "Registering component #" << id << ": " << typeid(T).name() << std::endl;
        components()[typeid(T)] = id;
        return components()[typeid(T)];
    }

    template <typename T>
    static u32 getComponentID() {
        if (components().find(typeid(T)) == components().end()) {
            std::cerr << "[WARN] Component not registered: " << typeid(T).name() << std::endl;
            return -1;
        }
        return components()[typeid(T)];
    }

    static u32 getComponentID(std::type_index type);
    static u32 nextID();
};