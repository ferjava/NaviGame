#pragma once
#include "axmol/2d/Sprite.h"
#include "axmol/math/Rect.h"
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

}  // namespace fjv
