//
// TestScene.cpp
//
// 2018-05-23
//

#include "TestScene.h"
#include <iostream>

#include "Quad.h"

Quad q;

void TestScene::LoadResources()
{
    shader.LoadShader();

    //Initialize clear color
    glClearColor(0.5f, 0.f, 0.f, 1.f);

    q.LoadResources();
}

void TestScene::Render()
{
    shader.Activate();

    q.Render(shader.GetAttrib());

    shader.Deactivate();
}