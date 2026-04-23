#include "sysGrafico.hpp"
#include "Components/Grafico.hpp"
#include "Components/Posicion.hpp"
#include "entt/entt.hpp"
void fjv::sysGrafico(entt::registry& regis)
{
    // Cojemos la poscion y el sprite que dibujaremos
    auto view = regis.view<fjv::Posicion, fjv::Grafico>();
    for (auto entidad : view)
    {
        auto& pos = view.get<fjv::Posicion>(entidad);
        auto& spr = view.get<fjv::Grafico>(entidad);
        /// Dibujamos el Sprite en la posicion
        spr.grafic->setPosition(pos.X, pos.Y);
    }
};
