#include "EntitiesFactory.hpp"
#include "entt/entt.hpp"
#include "Components/Components.hpp"
entt::entity entiFactory::createPlayer(entt::registry& reg, ax::Node& parent)
{
    // Datos de la nave
    auto nave = ax::Sprite::create("images/Naveplayer1.png", ax::Rect{300, 0, 100, 90});
    nave->setScale(0.5, 0.5);
    float posX = parent.getContentSize().width / 2;
    float posY = parent.getContentSize().height / 4;
    parent.addChild(nave, 0);

    auto mynave = reg.create();
    reg.emplace<fjv::Posicion>(mynave, posX, posY);
    reg.emplace<fjv::Velocidad>(mynave, 0.0f, 0.0f);
    reg.emplace<fjv::Grafico>(mynave, nave, ax::Rect{0, 0, 0, 0});
    reg.emplace<fjv::tagPlayer>(mynave);

    return mynave;
}
