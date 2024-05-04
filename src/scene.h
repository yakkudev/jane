#pragma once

#include <vector>
#include "component.h"


class Scene {
public:
    Scene(std::vector<std::vector<Component*>> entities);
    std::vector<std::vector<Component*>> entities;
};

class SceneManager {
public:
    static std::vector<Scene*> scenes;
    static void init();
};