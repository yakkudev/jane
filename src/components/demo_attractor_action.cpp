#include "demo_attractor_action.h"
#include "demo_attractor.h"
#include "transform.h"
#include "game.h"
#include "sprite.h"
#include "interaction.h"

void GC_DemoAttractorAction::onClick() {
    if (UIPanel) { return; }
    UIPanel = new Entity(Game::getGame()->getUITexture());
    UIPanel->addComponent(new GC_Transform(0, 0, 100, 100));
    UIPanel->addComponent(new GC_Sprite("sheldon"));
    UIPanel->isUI = true;
    UIPanel->init();
    Game::getGame()->addEntity(UIPanel);
}

void GC_DemoAttractorAction::init() {
    require<GC_DemoAttractor, GC_Interaction>();
    interaction = entity->getComponent<GC_Interaction>();

    interaction->registerListener(std::bind(&GC_DemoAttractorAction::onClick, this), GC_Interaction::Type::MOUSE_DOWN);
}

void GC_DemoAttractorAction::update() {
}