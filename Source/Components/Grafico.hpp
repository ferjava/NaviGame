#pragma once
#include "axmol/2d/Sprite.h"
#include "axmol/math/Rect.h"
#include "entt/entt.hpp"
namespace fjv
{
///
///@brief: Componente contiene un ax::Sprite* que es la direccion donde esta
/// el sprite creado en axmol (debe existir )  y el rectangulo que mostraremos
///
struct Grafico
{
    ax::Sprite* grafic;
    ax::Rect rect;
};
// Funcion para eliminar los graficos de forma segura
//
inline void onGraficoDestroy(entt::registry& reg, entt::entity entidad)
{
    auto sc = reg.get<Grafico>(entidad);
    if (sc.grafic)
    {
        sc.grafic->removeFromParent();
    }
};

}  // namespace fjv
