#include "World.hpp"

#include "Modules/Renderer/Entities/Light.hpp"
#include "World/Scenes/FirstScene.hpp"

void World::Start()
{
   auto& scene = CreateScene<FirstScene>("First Scene");
   ActiveScene = &scene;
}

void World::Update(double dt)
{
   ActiveScene->Update(dt);
}

void World::Render()
{
   ActiveScene->Render();
}

void World::Stop()
{
   ActiveScene->Stop();
}

void World::BeginFrame(double dt)
{
   ActiveScene->BeginFrame(dt);
}

void World::EndFrame(double dt)
{
   ActiveScene->EndFrame(dt);
}
