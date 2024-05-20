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
            new GC_Interaction(),
            new GC_WorldButton()
        }
    }),
    new Scene({
        {
            new GC_DemoManager(),
        },
        {
            new GC_Transform(),
            new GC_DemoAttractor(10000.0f, 100.0f, {0,0}, true)
        },
        {
            new GC_Transform(900.0f, 0.0f),
            new GC_DemoAttractor(100.0f, 10.0f, {0, -10}),
            new GC_DemoAttractorAction(),
            new GC_Interaction(),
        },
        {
            new GC_Transform(500.0f, 0.0f, 10,10),
            new GC_DemoAttractor(50.0f, 7.07f, {0, -12})
        },
    })

    };
}
