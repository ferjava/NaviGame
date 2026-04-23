/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 Copyright (c) 2019-present Axmol Engine contributors (see AUTHORS.md).

 https://axmol.dev/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "Core/MainScene.h"
#include "Components/Grafico.hpp"
#include "Components/Jugador.hpp"
#include "Components/Posicion.hpp"
#include "Components/Velicidad.hpp"
#include "Systems/sysAreaLimite.hpp"
#include "Systems/sysGrafico.hpp"
#include "Systems/sysMovimiento.hpp"
#include "Systems/sysTeclasJugador.hpp"
#include "Version.h"
#include "axmol/2d/Sprite.h"
#include "axmol/base/EventKeyboard.h"
#include "axmol/math/Rect.h"
#include "axmol/math/Vec2.h"
using namespace ax;

static int s_sceneID = 1000;

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf(
        "Depending on how you compiled you might have to add 'Content/' in front of filenames in "
        "MainScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = _director->getVisibleSize();
    auto origin      = _director->getVisibleOrigin();
    auto safeArea    = _director->getSafeAreaRect();
    auto safeOrigin  = safeArea.origin;

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    //
    /////////////////////////////
    auto nave = ax::Sprite::create("images/Naveplayer1.png", ax::Rect{300, 0, 100, 90});
    if (nave == nullptr)
    {
        problemLoading("Content/images/Naveplayer1");
    }
    else
    {
        nave->setScale(0.5, 0.5);
        AXLOGD("La nave se cargo ");
    }
    addChild(nave);
    /// Creamos la entidad para la nave
    auto mynave = _registro.create();
    _registro.emplace<fjv::Posicion>(mynave, 300.0f, 300.0f);
    _registro.emplace<fjv::Velocidad>(mynave, 0.0f, 0.0f);
    _registro.emplace<fjv::Grafico>(mynave, nave, ax::Rect{0, 0, 0, 0});
    _registro.emplace<fjv::Jugador>(mynave);
    AXLOGD("Hemos creado el entt de  la nave ");
    //

    // 3. add your codes below...

    _keyboardListener               = EventListenerKeyboard::create();
    _keyboardListener->onKeyPressed = [this](ax::EventKeyboard::KeyCode code, ax::Event* event) { _keys[code] = true; };
    _keyboardListener->onKeyReleased = [this](ax::EventKeyboard::KeyCode code, ax::Event* event) {
        _keys[code] = false;
    };

    _eventDispatcher->addEventListenerWithFixedPriority(_keyboardListener, 11);

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("version:" VERSION_STRING, "fonts/Marker Felt.ttf", 12);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width - (label->getStringLength() + 20),
                                origin.y + label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, -10);
    }

    // scheduleUpdate() is required to ensure update(float) is called on every loop
    scheduleUpdate();

    return true;
}

void MainScene::update(float delta)
{
    switch (_gameState)
    {
    case GameState::init:
    {
        _gameState = GameState::update;
        break;
    }

    case GameState::update:
    {
        if (_keys[ax::EventKeyboard::KeyCode::KEY_ESCAPE])
        {
            _gameState = GameState::end;
        }
        /////////////////////////////
        // Add your codes below...like....
        // 1.Inputs
        fjv::sysTeclasJugador(_registro, _keys);
        // 2.IA
        // 3.Fisica
        fjv::sysMovimiento(_registro, delta);
        // 4.Colision
        ax::Vec2 origin = _director->getVisibleOrigin();
        ax::Vec2 size   = _director->getVisibleSize();
        ax::Rect area   = ax::Rect(origin, size);
        fjv::sysAreaLimite(_registro, area);
        // 5.Camara
        // 6.Graficos
        fjv::sysGrafico(_registro);

        break;
    }

    case GameState::pause:
    {
        /////////////////////////////
        // Add your codes below...like....
        //
        // anyPauseStuff()

        break;
    }

    case GameState::menu1:
    {  /////////////////////////////
        // Add your codes below...like....
        //
        // UpdateMenu1();
        break;
    }

    case GameState::menu2:
    {  /////////////////////////////
        // Add your codes below...like....
        //
        // UpdateMenu2();
        break;
    }

    case GameState::end:
    {  /////////////////////////////
        // Add your codes below...like....
        //
        // CleanUpMyCrap();
        _director->end();
        break;
    }

    }  // switch
}

MainScene::MainScene()
{
    _sceneID = ++s_sceneID;
    AXLOGD("Scene: ctor: #{}", _sceneID);
}

MainScene::~MainScene()
{
    AXLOGD("~Scene: dtor: #{}", _sceneID);

    if (_keyboardListener)
        _eventDispatcher->removeEventListener(_keyboardListener);
    _registro.clear();  // Limpiamos el registro
    _sceneID = -1;
}
