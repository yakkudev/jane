#include "component_manager.h"

std::unordered_map<std::type_index, u32>& ComponentManager::components() {
    static std::unordered_map<std::type_index, u32> componentMap;
    return componentMap;
}

u32 ComponentManager::nextID() {
    static u32 id = 0;
    return id++;
}

u32 ComponentManager::getComponentID(std::type_index type) {
    return components()[type];
}