#pragma once

#include "types.h"
#include "component.h"
#include "demo_attractor.h"
#include "transform.h"
#include "interaction.h"

class GC_DemoAttractorAction : public Component {
    REGISTER_GC(GC_DemoAttractorAction)
private:
    GC_DemoAttractor* attractor;
    GC_Transform* transform;
    GC_Interaction* interaction;

    Entity* UIPanel;
public:
    void init() override;
    void update() override;
    void onClick();
};