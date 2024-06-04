#include "scene.h"

#include "components/transform.h"
#include "components/sprite.h"
#include "components/text.h"
#include "components/camera.h"
#include "components/world_button.h"
#include "components/interaction.h"
#include "components/demo_attractor.h"
#include "components/demo_attractor_action.h"
#include "components/demo_manager.h"

Scene::Scene(std::vector<std::vector<Component*>> entities) : entities(entities) {}

std::vector<Scene*> SceneManager::scenes = std::vector<Scene*>();
void SceneManager::init() {
    scenes.clear();
    scenes = {
    new Scene({}),
    new Scene({
        {
            new GC_Transform(),
            new GC_Sprite("sheldon")
        },
        {
            new GC_Transform(),
            new GC_Text("ProggyClean", "Hello, World!")
        },
        {
            new GC_Transform(100.0f, 100.0f),
            new GC_Sprite("sheldon"),
            new GC_Interaction(1),
            new GC_WorldButton()
        }
    }),
    new Scene({
        {
            new GC_Transform(),
            new GC_Camera()
        },
        {
            new GC_DemoManager(),
        },
        {
            // "sun"
            new GC_Transform(),
            new GC_DemoAttractor(100000.0f, 100.0f, {0,0}, true),
            new GC_Text("ProggyClean", "Sun"),
            new GC_DemoAttractorAction(),
            new GC_Interaction(1.5),
        },
        {
            // "mercury"
            new GC_Transform(579.0f, 0.0f),
            new GC_DemoAttractor(10.0f, 10.0, {0, -33}),
            new GC_Text("ProggyClean", "Mercury"),
            new GC_DemoAttractorAction(),
            new GC_Interaction(3),
        },
        {
            // "venus"
            new GC_Transform(1080.0f, 0.0f, 10,10),
            new GC_DemoAttractor(30.0f, 0, {0, -24}),
            new GC_Text("ProggyClean", "Venus"),
            new GC_DemoAttractorAction(),
            new GC_Interaction(3),
        },
        {
            // "earth"
            new GC_Transform(1496.0f, 0.0f, 10,10),
            new GC_DemoAttractor(30.0f, 150.0, {0, -21}),
            new GC_Text("ProggyClean", "Earth"),
            new GC_DemoAttractorAction(),
            new GC_Interaction(3),
        },
        {
            // "mars"
            new GC_Transform(2279.0f, 0.0f, 10,10),
            new GC_DemoAttractor(15.0f, 0.0f, {0, -17}),
            new GC_Text("ProggyClean", "Mars"),
            new GC_DemoAttractorAction(),
            new GC_Interaction(3),
        },
        {
            // "jupiter"
            new GC_Transform(7785.0f, 0.0f, 10,10),
            new GC_DemoAttractor(64.0f, -25.0f, {0, -9.0}),
            new GC_Text("ProggyClean", "Jupiter"),
            new GC_DemoAttractorAction(),
            new GC_Interaction(3),
        },
        {
            // "saturn"
            new GC_Transform(14340.0f, 0.0f, 10,10),
            new GC_DemoAttractor(53.0f, 10.0f, {0, -6.6}),
            new GC_Text("ProggyClean", "Saturn"),
            new GC_DemoAttractorAction(),
            new GC_Interaction(3),
        },
        {
            // "uranus"
            new GC_Transform(28710.0f, 0.0f, 10,10),
            new GC_DemoAttractor(22.8f, 180.0f, {0, -4.6}),
            new GC_Text("ProggyClean", "Uranus"),
            new GC_DemoAttractorAction(),
            new GC_Interaction(3),
        },
        {
            // "neptune"
            new GC_Transform(44950.0f, 0.0f, 10,10),
            new GC_DemoAttractor(22.0f, 210.0f, {0, -3.8}),
            new GC_Text("ProggyClean", "Neptune"),
            new GC_DemoAttractorAction(),
            new GC_Interaction(3),
        }

    })

    };
}
