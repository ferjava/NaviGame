#pragma once
#include "axmol/base/EventListenerKeyboard.h"
#include "entt/entity/fwd.hpp"
#include <map>
namespace fjv
{
void sysTeclasJugador(entt::registry& regis, std::map<ax::EventKeyboard::KeyCode, bool>& key);
}
