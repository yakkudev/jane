A very bad 2D game engine built on top of SFML.
Supports basic rendering, input handling, scenes and asset loading.

Contains a demo - a non realistic gravity simulation.

Supports engine game separation (kind of)

WARNING: Custom components don't use C++ destructors, they use a clean() method inherited from Component that is called whenever the component is removed from an entity.