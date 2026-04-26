#include "sysTeclasJugador.hpp"
#include "Components/TagComponents.hpp"
#include "Components/Velicidad.hpp"
#include "entt/entt.hpp"
void fjv::sysTeclasJugador(entt::registry& regis, std::map<ax::EventKeyboard::KeyCode, bool>& key)
{
    auto view = regis.view<fjv::tagPlayer, fjv::Velocidad>();
    for (auto entidad : view)
    {
        auto& vel   = view.get<fjv::Velocidad>(entidad);
        float speed = 400.0f;
        vel.vY      = 0.0f;
        vel.vX      = 0.0f;
        if (key[ax::EventKeyboard::KeyCode::KEY_W])
            vel.vY += speed;
        if (key[ax::EventKeyboard::KeyCode::KEY_S])
            vel.vY -= speed;
        if (key[ax::EventKeyboard::KeyCode::KEY_A])
            vel.vX -= speed;
        if (key[ax::EventKeyboard::KeyCode::KEY_D])
            vel.vX += speed;
    }
}
