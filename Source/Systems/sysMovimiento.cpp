#include "sysMovimiento.hpp"
#include "Components/Posicion.hpp"
#include "Components/Velicidad.hpp"
#include "entt/entt.hpp"

///
///@brief: Asigna las nuevas posiciones .Aplicando una Velicidad
///

void fjv::sysMovimiento(entt::registry& regis, float dt)
{
    auto view = regis.view<fjv::Posicion, fjv::Velocidad>();
    for (auto entity : view)
    {
        auto& pos = view.get<fjv::Posicion>(entity);
        auto& vel = view.get<fjv::Velocidad>(entity);
        pos.X += vel.vX * dt;
        pos.Y += vel.vY * dt;
    }
};
