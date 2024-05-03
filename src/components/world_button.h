#pragma once

#include "component.h"
#include "interaction.h"
#include "sprite.h"

class GC_WorldButton : public Component {
private:
    GC_Interaction* interaction;
    GC_Sprite* sprite;

public:
    GC_WorldButton();
    void init() override;

    void onClick();
};