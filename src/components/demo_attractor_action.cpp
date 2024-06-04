#include "demo_attractor_action.h"
#include "demo_attractor.h"
#include "transform.h"
#include "game.h"
#include "sprite.h"
#include "camera.h"
#include "interaction.h"

GC_DemoAttractorAction::GC_DemoAttractorAction() {
}

void GC_DemoAttractorAction::onClick() {
    Game::getGame()->entities[0]->getComponent<GC_Camera>()->setLock(transform);

}

void GC_DemoAttractorAction::init() {
    require<GC_DemoAttractor, GC_Interaction>();
    interaction = entity->getComponent<GC_Interaction>();
    transform = entity->getComponent<GC_Transform>();

    interaction->registerListener(std::bind(&GC_DemoAttractorAction::onClick, this), GC_Interaction::Type::MOUSE_DOWN);
}

void GC_DemoAttractorAction::update() {
}