#include "sysAreaLimite.hpp"
#include <cstdlib>
#include "Components/Grafico.hpp"
#include "Components/Jugador.hpp"
#include "Components/Posicion.hpp"
#include "entt/entt.hpp"
void fjv::sysAreaLimite(entt::registry& regis, ax::Rect& area)
{
    auto view = regis.view<fjv::Jugador, fjv::Posicion, fjv::Grafico>();
    for (auto entidad : view)
    {
        auto sprite = view.get<fjv::Grafico>(entidad);

        auto& pos = view.get<fjv::Posicion>(entidad);
        if ((pos.X - sprite.grafic->getContentSize().width / 2 * sprite.grafic->getScaleX()) < area.origin.x)
            pos.X = area.origin.x + sprite.grafic->getContentSize().width / 2 * sprite.grafic->getScaleY();
        if ((pos.Y - sprite.grafic->getContentSize().height / 2 * sprite.grafic->getScaleY()) < area.origin.y)
            pos.Y = area.origin.y + sprite.grafic->getContentSize().height / 2 * sprite.grafic->getScaleY();
        if ((pos.X + sprite.grafic->getContentSize().width / 2 * sprite.grafic->getScaleX()) > area.size.width)
            pos.X = area.size.width - sprite.grafic->getContentSize().width / 2 * sprite.grafic->getScaleX();
        if ((pos.Y + sprite.grafic->getContentSize().height / 2 * sprite.grafic->getScaleY()) > area.size.height)
            pos.Y = area.size.height - sprite.grafic->getContentSize().height / 2 * sprite.grafic->getScaleY();
    }
}
